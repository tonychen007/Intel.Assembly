#pragma once

#include <wchar.h>

// for main cc
extern void sseStringCalcLengthTest();

// defined in asm
extern "C" int sseStringCalcLength(const char* str);