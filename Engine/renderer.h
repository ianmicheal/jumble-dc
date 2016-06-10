#ifndef _RENDERER_H_
#define _RENDERER_H_

#ifdef _WIN64
#pragma once
#endif

#include "vector.h"

enum primitiveType
{
	PRIMITIVE_TYPE_PLANE
};

struct mesh_t
{
	float* vertices;
	float* normals;
	float* uvCoords;
	unsigned int* indices;

	struct mesh_t* next;
	unsigned int vertexCount;
	unsigned int triangleCount;
	unsigned int indexCount;
};

struct renderer_t
{
	struct vec4_t backColor;

	int renderResolutionX;
	int renderResolutionY;

	float aspect;
	float fov;
	unsigned char wireframe;

	struct mesh_t *headMesh;

	struct mat44_t cameraMatrix;
	struct mat44_t projectionMatrix;	
};

void renderer_init(struct renderer_t* rend, struct engine_t* engine);
void renderer_doFrame();
void renderer_endFrame();
void renderer_destroy();

struct mesh_t* renderer_mesh_getPrimitive(enum primitiveType type);
void renderer_mesh_destroy(struct mesh_t* mesh);

#endif // _RENDERER_H_