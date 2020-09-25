#pragma once

// for main cc
extern void avxFloatPointArithemticTest();
extern void avxFloatPointCompareTest();

// defined in asm
extern "C" void avxScalarFloatPoint(double a, double b, double c[8]);
extern "C" void avxFloatPointCompare(double a, double b, bool r[8]);
