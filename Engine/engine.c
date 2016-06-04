#include "engine.h"

static struct engine_t* engineInstance = NULL;

int engine_init(struct engine_t* hndl)
{
	int result = -1;

	#ifdef PC_BUILD
	result = engine_init_windows(hndl);
	#else
	engine_init_dreamcast(hndl);
	#endif

	if (result >= 0)
	{
		// Init the renderer and the scene manager
		renderer_init(&hndl->renderer, hndl);
		scene_init(&hndl->scene, hndl);

		hndl->deltaTime = 0.0f;
		hndl->lastTime = 0.0f;

		engineInstance = hndl;
		result = 0;
	}

	return result;
}

void engine_destroy()
{
	#ifdef PC_BUILD
	engine_destroy_windows();
	#endif
}

int engine_doFrame()
{
	// Propagate frame start
	renderer_doFrame();
	scene_doFrame();

	#ifdef PC_BUILD
	return engine_doFrame_windows();
	#else
	engine_doFrame_dreamcast();
	return 0;
	#endif
}

void engine_endFrame()
{
	// Propagate frame finish
	renderer_endFrame();

	#ifdef PC_BUILD
	engine_endFrame_windows();
	#else
	engine_endFrame_dreamcast();
	#endif
}