#include "resources.h"
#include <stdio.h>
#include <string.h>

static struct engine_t *engineInstance;

void resources_init(struct engine_t *eng)
{
	engineInstance = eng;
}

void resources_get_list_windows(struct resource_list_t *resources)
{
#ifdef PC_BUILD
	const char *rcPath = "cdrom\\RC.BIN";
	FILE *rc;
	const char *rcMagic = "RCLIST";
	char rcHead[6];

	// Open the resources index file
	fopen_s(&rc, rcPath, "r");

	// Read the resource list
	// First, check if the file is a correct
	// resource list file
	fread_s(rcHead, 6 * sizeof(char), sizeof(char), 6, rc);

	// Check the header
	if (strcmp(rcMagic, rcHead) != 0)
	{
		// Invalid file
		return;
	}

	// Close the file
	fclose(rc);
#endif
}

void resources_get_list_dreamcast(struct resource_list_t *resources)
{
#ifdef DREAM_BUILD
	const char *rcPath = "/cd/RC.BIN";
	FILE *rc;
	const char *rcMagic = "RCLIST";
	char rcHead[6];

	// Open the resources index file
	rc = fopen(rcPath, "r");

	// Read the resource list
	// First, check if the file is a correct
	// resource list file
	fread(rcHead, sizeof(char), 6, rc);

	// Check the header
	if (strcmp(rcMagic, rcHead) != 0)
	{
		// Invalid file
		return;
	}

	// Close the file
	fclose(rc);
#endif
}

void resources_load(struct resource_t *rc)
{

}

void resources_unload(struct resource_t *rc)
{

}