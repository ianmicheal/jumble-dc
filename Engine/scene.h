#ifndef _SCENE_H_
#define _SCENE_H_

#ifdef _WIN64
#pragma once
#endif

#include "vector.h"

struct transform_t
{
	unsigned char id;
	char name[32];

	struct vec4_t position;
	struct vec4_t scale;
	struct vec4_t rotation;

	struct mat44_t modelMatrix;
	
	struct transform_t* parent;
	struct transform_t* next;

	struct mesh_t* mesh;
};

struct scene_t
{
	struct transform_t* headNode;
};

void scene_init(struct scene_t* sc, struct engine_t* engine);
void scene_doFrame();

struct transform_t* scene_gameObject_instantiate();
void scene_gameObject_destroy(struct transform_t* go);

#endif // _SCENE_H_