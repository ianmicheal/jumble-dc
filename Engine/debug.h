#ifndef _DEBUG_H_
#define _DEBUG_H

#ifdef _WIN64
#pragma once
#endif

void debug_log(const char* str);
void debug_warn(const char* str);
void debug_error(const char* str);

#endif // _DEBUG_H_