#pragma once

// for main cc
extern void sseFloatPointArithemticTest();

// defined in asm
extern "C" void sseMathFloat(float a, float b, float c[8]);
extern "C" void sseMathDouble(double a, double b, double c[8]);