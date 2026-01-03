#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#undef THIS

#include <cstdarg>
#include <cstdio>

inline void DEBUG_LOG(const char* fmt, ...)
{
    char buffer[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, args);
    va_end(args);

    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");
}