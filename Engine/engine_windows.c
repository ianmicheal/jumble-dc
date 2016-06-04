#include "engine.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdlib.h>

static struct engine_t* engineInstance = NULL;

int engine_init_windows(struct engine_t* hndl)
{
	int result = -1;

	// Attempt to start GLFW
	if (glfwInit())
	{
		glewExperimental = 1;
		glewInit();

		// If succeeded, create the window with
		// the Dreamcast's default parameters
		hndl->window = glfwCreateWindow(640, 480, "Dreamgame", NULL, NULL);

		if (hndl->window != NULL)
		{
			glfwMakeContextCurrent(hndl->window);
			glfwSwapInterval(1);
			glfwSetWindowSizeCallback(hndl->window, engine_windowResized);

			engineInstance = hndl;
			result = 0;
		}
		else
		{
			glfwTerminate();
		}
	}

	return result;
}

void engine_windowResized(GLFWwindow* window, int width, int height)
{
	if (engineInstance != NULL)
	{
		engineInstance->internalResolutionX = width;
		engineInstance->internalResolutionY = height;

		engineInstance->renderer.renderResolutionX = width;
		engineInstance->renderer.renderResolutionY = height;
	}
}

int engine_doFrame_windows()
{
	// Init delta time
	engineInstance->lastTime = glfwGetTime();

	// Poll UI events
	return glfwWindowShouldClose(engineInstance->window);
}

void engine_endFrame_windows()
{
	// Get last frame's delta time
	engineInstance->deltaTime = glfwGetTime() - engineInstance->lastTime;
	glfwSetTime(0.0);

	// Swap buffers
	glfwSwapBuffers(engineInstance->window);
	glfwPollEvents();
}

void engine_destroy_windows()
{
	// Destroy the renderer
	renderer_destroy(&engineInstance->renderer);

	glfwDestroyWindow(engineInstance->window);
	glfwTerminate();
}