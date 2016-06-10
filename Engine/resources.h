#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#ifdef _WIN64
#pragma once
#endif

#define RESOURCE_TYPE_BINARY
#define RESOURCE_TYPE_TEXTURE_RAW
#define RESOURCE_TYPE_TEXTURE_PVR
#define RESOURCE_TYPE_MESH_STATIC
#define RESOURCE_TYPE_MESH_ANIMATED_SKELETAL
#define RESOURCE_TYPE_AUDIO_PCM
#define RESOURCE_TYPE_AUDIO_VORBIS

struct resource_t
{
	unsigned char resourceType;
	unsigned int length;
	unsigned int offset;
};

struct resource_list_t
{
	unsigned char resourceCount;
	struct resource_t *head;
};

void resources_init(struct engine_t *eng);
void resources_get_list(struct resource_list_t *resources);

void resources_load(struct resource_t *rc);
void resources_unload(struct resource_t *rc);

#endif // _RESOURCES_H_