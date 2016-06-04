#include "engine.h"
#include <GL/GL.h>
#include <stdlib.h>

#ifdef DREAM_BUILD

int engine_init_dreamcast(struct engine_t* hndl)
{

}

void engine_destroy_dreamcast()
{

}

int engine_doFrame_dreamcast()
{

}

void engine_endFrame_dreamcast()
{

}

// PC method stubs: only implemented
// to avoid compilation problems
inline int engine_init_windows(struct engine_t* hndl)
{
	return 0;
}

inline void engine_destroy_windows()
{
	return;
}

inline int engine_doFrame_windows()
{
	return 0;
}

inline void engine_endFrame_windows()
{
	return;
}

#endif // DREAM_BUILD