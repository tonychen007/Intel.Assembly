#pragma once

#include "ymmVal.h"

// for main cc
extern void avxFloatPointArithemticTest();
extern void avxFloatPointCompareTest();
extern void avxPackedFloatPointArithemticTest();
extern void avxPackedFloatPointCompareTest();

// defined in asm
extern "C" void avxScalarFloatPoint(double a, double b, double c[8]);
extern "C" void avxFloatPointCompare(double a, double b, bool r[8]);
extern "C" void avxPackedFloatPointFloat(const YmmVal * a, const YmmVal * b, YmmVal c[6]);
extern "C" void avxPackedFloatPointDouble(const YmmVal * a, const YmmVal * b, YmmVal c[5]);
