#ifndef _ENGINE_H_
#define _ENGINE_H

#ifdef _WIN64
	#pragma once
	#include <GL\glew.h>
	#include <GLFW\glfw3.h>
	#define PC_BUILD
#else
	#define DREAM_BUILD
#endif

#include "renderer.h"
#include "scene.h"
#include "debug.h"

struct engine_t
{
	#ifdef PC_BUILD
	GLFWwindow* window;
	#endif

	struct renderer_t renderer;
	struct scene_t scene;

	int internalResolutionX;
	int internalResolutionY;
	double lastTime;
	double deltaTime;
};

// Public functions
int engine_init(struct engine_t* hndl);
void engine_destroy();
int engine_doFrame();
void engine_endFrame();

// Private functions: Do not use these.
// Use the public functions instead
int engine_init_windows(struct engine_t* hndl);
void engine_destroy_windows();
int engine_doFrame_windows();
void engine_endFrame_windows();

//int engine_init_dreamcast(struct engine_t* hndl);
//void engine_destroy_dreamcast();
//int engine_doFrame_dreamcast();
//void engine_endFrame_dreamcast();

#ifdef PC_BUILD
void engine_windowResized(GLFWwindow* window, int width, int height);
#endif

#endif // _ENGINE_H_