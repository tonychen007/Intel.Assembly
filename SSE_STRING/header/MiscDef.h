#pragma once

#include <wchar.h>

// for main cc
extern void sseStringCalcLengthTest();
extern void sseStringReplaceTest();

// defined in asm
extern "C" int sseStringCalcLength(const char* str);
extern "C" int sseStringReplace(const char* str, const char oldChar, const char newChar);