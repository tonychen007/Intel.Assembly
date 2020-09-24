#pragma once

// for main cc
extern void avxFloatPointArithemticTest();

// defined in asm
extern "C" void avxScalarFloatPoint(double a, double b, double c[8]);
