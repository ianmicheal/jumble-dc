#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#ifdef _WIN64
#pragma once
#endif

#define RESOURCE_TYPE_BINARY 0x00
#define RESOURCE_TYPE_TEXTURE_RAW 0x01
#define RESOURCE_TYPE_TEXTURE_PVR 0x02
#define RESOURCE_TYPE_MESH_STATIC 0x03
#define RESOURCE_TYPE_MESH_ANIMATED_SKELETAL 0x04
#define RESOURCE_TYPE_AUDIO_PCM 0x05
#define RESOURCE_TYPE_AUDIO_VORBIS 0x06

#define RESOURCE_VERSION_UNCOMPRESSED 0x00
#define RESOURCE_VERSION_COMPRESSED_ZLIB 0x01

#include "engine.h"

struct resource_t
{
	uint8_t type;
	char name[32];
	uint32_t length;
	uint32_t offset;

	struct resource_t *next;
};

struct resource_list_t
{
	uint8_t resourceCount;
	uint8_t version;
	char path[128];
	struct resource_t *head;
};

// Public methods
void resources_init(struct engine_t *eng);
void resources_get_list(char* path, struct resource_list_t *resources);
void resources_delete_list(struct resource_list_t *resources);

void resources_load(struct resource_t *rc);
void resources_unload(struct resource_t *rc);

#endif // _RESOURCES_H_