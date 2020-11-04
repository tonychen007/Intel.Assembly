#pragma once

#include <wchar.h>

// for main cc
extern void BasicOptimizationTest();
extern void NonTemporalTest();

// defined in asm
extern "C" void CalcResultMovaps(float* c, const float* a, const float* b, int n);
extern "C" void CalcResultMovntps(float* c, const float* a, const float* b, int n);