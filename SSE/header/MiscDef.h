#pragma once

// for main cc
extern void sseFloatPointArithemticTest();
extern void sseFloatPointCompareTest();

// defined in asm
extern "C" void sseMathFloat(float a, float b, float c[8]);
extern "C" void sseMathDouble(double a, double b, double c[8]);

extern "C" void sseCompareFloat(float a, float b, bool* result);
extern "C" void sseCompareDouble(double a, double b, bool* result);