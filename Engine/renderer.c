#include "renderer.h"
#include "engine.h"
#include <malloc.h>
#include <gl/glu.h>

#ifdef PC_BUILD
#include <GL\glew.h>
#else
#include <GL/gl.h>
#endif

static struct renderer_t* rendererInstance;
static struct engine_t* engineInstance;

void renderer_init(struct renderer_t* rend, struct engine_t* engine)
{
	rend->renderResolutionX = 640;
	rend->renderResolutionY = 480;
	rend->aspect = (float)rend->renderResolutionX / (float)rend->renderResolutionY;

	rend->cameraMatrix = IDENTITY_MATRIX;
	rend->projectionMatrix = IDENTITY_MATRIX;

	rend->wireframe = 0;

	rendererInstance = rend;
	engineInstance = engine;

	// Create the primitive meshes
	struct mesh_t* plane = malloc(sizeof(struct mesh_t));
	plane->next = NULL;

	plane->vertices = malloc(12 * sizeof(float));

	//0
	plane->vertices[0] = -0.5f;
	plane->vertices[1] = 0.0f;
	plane->vertices[2] = 0.5f;

	//1
	plane->vertices[3] = -0.5f;
	plane->vertices[4] = 0.0f;
	plane->vertices[5] = -0.5f;

	//2
	plane->vertices[6] = 0.5f;
	plane->vertices[7] = 0.0f;
	plane->vertices[8] = -0.5f;

	//3
	plane->vertices[9] = 0.5f;
	plane->vertices[10] = 0.0f;
	plane->vertices[11] = 0.5f;

	plane->normals = malloc(12 * sizeof(float));

	plane->normals[0] = 0.0f;
	plane->normals[1] = 1.0f;
	plane->normals[2] = 0.0f;

	plane->normals[3] = 0.0f;
	plane->normals[4] = 1.0f;
	plane->normals[5] = 0.0f;

	plane->normals[6] = 0.0f;
	plane->normals[7] = 1.0f;
	plane->normals[8] = 0.0f;

	plane->normals[9] = 0.0f;
	plane->normals[10] = 1.0f;
	plane->normals[11] = 0.0f;

	plane->uvCoords = malloc(8 * sizeof(float));

	plane->uvCoords[0] = 0.0f;
	plane->uvCoords[1] = 1.0f;

	plane->uvCoords[2] = 0.0f;
	plane->uvCoords[3] = 0.0f;

	plane->uvCoords[4] = 1.0f;
	plane->uvCoords[5] = 0.0f;

	plane->uvCoords[6] = 1.0f;
	plane->uvCoords[7] = 1.0f;

	plane->indices = malloc(6 * sizeof(GLuint));

	plane->indices[0] = 0;
	plane->indices[1] = 1;
	plane->indices[2] = 2;

	plane->indices[3] = 2;
	plane->indices[4] = 3;
	plane->indices[5] = 0;

	plane->next = NULL;
	plane->vertexCount = 4;
	plane->triangleCount = 2;
	plane->indexCount = 6;

	rendererInstance->headMesh = plane;
}

void renderer_doFrame()
{
	struct scene_t* scene = &engineInstance->scene;
	struct transform_t* next = scene->headNode, *parent = NULL;
	struct mat44_t currentModelView = IDENTITY_MATRIX;

	glClearColor(rendererInstance->backColor.m[0], rendererInstance->backColor.m[1], rendererInstance->backColor.m[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glFrontFace(GL_CCW);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glViewport(0, 0, rendererInstance->renderResolutionX, rendererInstance->renderResolutionY);

	if (rendererInstance->wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	#ifdef DREAM_BUILD
	glEnable(GL_KOS_NEARZ_CLIPPING);
	#endif

	// Upload projection matrix
	glMatrixMode(GL_PROJECTION);
	rendererInstance->aspect = (float)rendererInstance->renderResolutionX / (float)rendererInstance->renderResolutionY;
	rendererInstance->projectionMatrix = mat44_perspective(rendererInstance->fov, rendererInstance->aspect, 0.01f, 1000.0f);
	glLoadMatrixf(&rendererInstance->projectionMatrix.m[0]);

	// Loop through the scene tree and draw
	while (next != NULL)
	{
		parent = scene->headNode->parent;

		// Apply self transformation
		currentModelView = mat44_multiply(&next->modelMatrix, &currentModelView);

		// Cummulate parent transformations
		while (parent != NULL)
		{
			currentModelView = mat44_multiply(&parent->modelMatrix, &currentModelView);
			parent = parent->parent;
		}

		// Apply camera matrix
		currentModelView = mat44_multiply(&rendererInstance->cameraMatrix, &currentModelView);

		// Upload model-view matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&currentModelView.m[0]);

		// Draw mesh
		if (next->mesh != NULL)
		{
			#ifdef PC_BUILD
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			#endif	

			glNormalPointer(GL_FLOAT, 0, &next->mesh->normals[0]);
			glVertexPointer(3, GL_FLOAT, 0, &next->mesh->vertices[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &next->mesh->uvCoords[0]);

			glDrawElements(GL_TRIANGLES, next->mesh->indexCount, GL_UNSIGNED_INT, &next->mesh->indices[0]);

			#ifdef PC_BUILD
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			#endif
		}

		next = next->next;
	}

	#ifdef DREAM_BUILD
	glDisable(GL_KOS_NEARZ_CLIPPING);
	#endif
}

void renderer_endFrame()
{
}

void renderer_destroy()
{
	// Clean up the allocated meshes
	struct mesh_t* mesh = rendererInstance->headMesh;

	while (rendererInstance->headMesh != NULL)
	{
		while (mesh->next != NULL)
		{
			mesh = mesh->next;
		}

		renderer_mesh_destroy(mesh);
	}
}

struct mesh_t* renderer_mesh_getPrimitive(enum primitiveType type)
{
	struct mesh_t* result = NULL;

	if (type == PRIMITIVE_TYPE_PLANE)
	{
		result = rendererInstance->headMesh;
	}

	return result;
}

void renderer_mesh_destroy(struct mesh_t* mesh)
{
	struct mesh_t* head = rendererInstance->headMesh;
	int found = 0;

	if (head != NULL)
	{
		if (head == mesh)
		{
			if (head->next != NULL)
			{
				rendererInstance->headMesh = head->next;
			}

			free(head->vertices);
			free(head->normals);
			free(head->uvCoords);
			free(head->indices);
			free(head);

			rendererInstance->headMesh = NULL;
		}
		else
		{
			while (head != NULL && !found)
			{
				if (head->next == mesh)
				{
					head->next = mesh->next;

					free(head->vertices);
					free(head->normals);
					free(head->uvCoords);
					free(head->indices);
					free(mesh);

					found = 1;
				}

				head = head->next;
			}
		}
	}
}