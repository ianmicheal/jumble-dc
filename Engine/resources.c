#include "resources.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static struct engine_t *engineInstance;

void resources_init(struct engine_t *eng)
{
	engineInstance = eng;
}

void resources_get_list(char* path, struct resource_list_t *resources)
{
	FILE *rc;
	const char *rcMagic = "RCLIST";
	char rcHead[7];
	uint8_t index = 0;
	struct resource_t *previous = NULL;

	// Open the resources index file
	#ifdef PC_BUILD
	fopen_s(&rc, path, "r");
	#else
	rc = fopen(path, "r");
	#endif

	// Read the resource list
	// First, check if the file is a correct
	// resource list file
	#ifdef PC_BUILD
	fread_s(rcHead, 6 * sizeof(char), sizeof(char), 6, rc);
	#else
	fread(rcHead, sizeof(char), 6, rc);
	#endif
	rcHead[6] = '\0';

	// Check the header
	if (strcmp(rcMagic, rcHead) != 0)
	{
		// Invalid file
		return;
	}

	// Copy the path to the resource struct
	#ifdef PC_BUILD
	strcpy_s(resources->path, strlen(path), path);
	#else
	strcpy(resources->path, path);
	#endif

	// Get the container resource count
	#ifdef PC_BUILD
	fread_s(&resources->resourceCount, sizeof(uint8_t), sizeof(uint8_t), 1, rc);
	#else
	fread(&resources->resourceCount, sizeof(uint8_t), 1, rc);
	#endif

	// Get the container version
	#ifdef PC_BUILD
	fread_s(&resources->version, sizeof(uint8_t), sizeof(uint8_t), 1, rc);
	#else
	fread(&resources->version, sizeof(uint8_t), 1, rc);
	#endif

	resources->head = NULL;

	// Get the information for all the resources
	while (index < resources->resourceCount)
	{
		// Allocate a new resource
		struct resource_t *tempRc = malloc(sizeof(struct resource_t));
		tempRc->next = NULL;
		
		// Read the resource name, type, size and offset
		#ifdef PC_BUILD
		fread_s(&tempRc->type, sizeof(uint8_t), sizeof(uint8_t), 1, rc);
		#else
		fread(&rc->type, sizeof(uint8_t), 1, rc);
		#endif

		#ifdef PC_BUILD
		fread_s(&tempRc->name, sizeof(char), sizeof(char), 32, rc);
		#else
		fread(&rc->name, sizeof(char), 1, rc);
		#endif

		#ifdef PC_BUILD
		fread_s(&tempRc->length, sizeof(uint32_t), sizeof(uint32_t), 1, rc);
		#else
		fread(&rc->length, sizeof(uint32_t), 1, rc);
		#endif

		#ifdef PC_BUILD
		fread_s(&tempRc->offset, sizeof(uint32_t), sizeof(uint32_t), 1, rc);
		#else
		fread(&rc->offset, sizeof(uint32_t), 1, rc);
		#endif

		if (resources->head == NULL)
		{
			resources->head = tempRc;
		}

		if (previous == NULL)
		{
			previous = tempRc;
		}
		else
		{
			previous->next = tempRc;
		}

		index++;
	}

	// Close the file
	fclose(rc);
}

void resources_delete_list(struct resource_list_t *resources)
{
	struct resource_t *current = resources->head, *next;

	if (resources->head != NULL)
	{
		if (resources->head->next == NULL)
		{
			free(resources->head);
		}
		else
		{
			while (current != NULL)
			{
				next = current->next;
				free(current);
				current = next;
			}
		}
	}
}

void resources_load(struct resource_t *rc)
{

}

void resources_unload(struct resource_t *rc)
{

}