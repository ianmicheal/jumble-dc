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

/*
 * Engine structure: engine_t
 *
 * - Holds the context por the whole game engine.
 * - Public attributes:
 *   · (PC Only) window: OpenGL window context.
 *   · renderer: graphics renderer context.
 *   · scene: scene graph manager context.
 *   · internalResolutionX/Y: real render buffer width and height.
 *         This will be used to be able to render to a constant render
 *         resolution independently of the window size, using a FBO.
 *   · deltaTime: time in seconds needed to process the last frame.
 *
 * - Public methods:
 *   · engine_init: initializes the engine and instances the subsystems owned
 *                  by itself (renderer, scene manager).
 *   · engine_destroy: gracefully clears all data allocated by the engine and
 *                     closes the app.
 *   · engine_doFrame: commands all subsystems to start a new game frame.
 *   · engine_endFrame: commits all changes to all subsystems in order to
 *                      end the game frame.
 *
*/
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

int engine_init_dreamcast(struct engine_t* hndl);
void engine_destroy_dreamcast();
int engine_doFrame_dreamcast();
void engine_endFrame_dreamcast();

#ifdef PC_BUILD
void engine_windowResized(GLFWwindow* window, int width, int height);
#endif

#endif // _ENGINE_H_