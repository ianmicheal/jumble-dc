#include "engine.h"

#ifdef PC_BUILD
#include <Windows.h>
#endif

#include <stdio.h>

#ifdef PC_BUILD
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
#else
int main()
#endif
{
	// Start the game engine
	struct engine_t engine;

	if (engine_init(&engine) < 0)
	{
		debug_error("Couldn't start game engine.");
	}
	else
	{
		engine.renderer.backColor.m[0] = 0.0f;
		engine.renderer.backColor.m[1] = 0.0f;
		engine.renderer.backColor.m[2] = 0.0f;

		engine.renderer.wireframe = 1;

		// Create a simple plane
		struct transform_t* go = scene_gameObject_instantiate();
		go->mesh = renderer_mesh_getPrimitive(PRIMITIVE_TYPE_PLANE);

		// Set the camera and projection matrices
		struct vec4_t pos = { {1.0f, 1.0f, 1.0f, 0.0f} }, dir = { {-1.0f,-1.0f,-1.0f,0.0f} };
		engine.renderer.cameraMatrix = mat44_lookAt(pos, dir);
		engine.renderer.fov = 45.0f;

		while (!engine_doFrame())
		{
			engine_endFrame();
		}

		engine_destroy();
	}

	return 0;
}