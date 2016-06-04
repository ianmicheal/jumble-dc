#include "debug.h"
#include <Windows.h>

void debug_log(const char* str)
{
	MessageBox(GetActiveWindow(), str, "Info", MB_OK | MB_ICONINFORMATION);
}

void debug_warn(const char* str)
{
	MessageBox(GetActiveWindow(), str, "Info", MB_OK | MB_ICONWARNING);
}

void debug_error(const char* str)
{
	MessageBox(GetActiveWindow(), str, "Fatal error", MB_OK | MB_ICONERROR);
}