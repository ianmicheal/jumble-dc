#include "scene.h"
#include "engine.h"
#include <stdlib.h>
#include <string.h>

static struct scene_t* sceneInstance;
static struct engine_t* engineInstance;

void scene_init(struct scene_t* sc, struct engine_t* engine)
{
	sc->headNode = NULL;

	sceneInstance = sc;
	engineInstance = engine;
}

void scene_doFrame()
{
	// Update the model matrices of the scene graph
	struct transform_t* next = sceneInstance->headNode;

	while (next != NULL)
	{
		mat44_scale(&next->modelMatrix, next->scale.m[0], next->scale.m[1], next->scale.m[2]);
		mat44_rotateX(&next->modelMatrix, next->rotation.m[0]);
		mat44_rotateY(&next->modelMatrix, next->rotation.m[1]);
		mat44_rotateZ(&next->modelMatrix, next->rotation.m[2]);
		mat44_translate(&next->modelMatrix, next->position.m[0], next->position.m[1], next->position.m[2]);

		next = next->next;
	}
}

struct transform_t* scene_gameObject_instantiate()
{
	struct transform_t* tr = NULL, *tail = NULL;

	tr = malloc(sizeof(struct transform_t));
	
	#ifdef PC_BUILD
	strcpy_s(tr->name, 32, "Game Object");
	#else
	strcpy(tr->name, "Game Object");
	#endif

	tr->parent = NULL;
	tr->next = NULL;
	tr->mesh = NULL;

	tr->position = VEC4_ZERO;
	tr->rotation = VEC4_ZERO;
	tr->scale = VEC4_ONE;
	tr->modelMatrix = IDENTITY_MATRIX;

	if (sceneInstance->headNode == NULL)
	{
		sceneInstance->headNode = tr;
	}
	else
	{
		tail = sceneInstance->headNode;

		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = tr;
	}

	return tr;
}

void scene_gameObject_destroy(struct transform_t* go)
{
	struct transform_t* head = sceneInstance->headNode;
	int found = 0;

	if (head != NULL)
	{
		if (head == go)
		{
			if (head->next != NULL)
			{
				sceneInstance->headNode = head->next;
			}

			free(head);
		}
		else
		{
			while (head != NULL && !found)
			{
				if (head->next == go)
				{
					head->next = go->next;
					free(go);
					found = 1;
				}

				head = head->next;
			}
		}
	}
}
