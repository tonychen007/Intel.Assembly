#pragma once

#include "ymmVal.h"

// for main cc
extern void avxFloatPointArithemticTest();
extern void avxFloatPointCompareTest();
extern void avxPackedFloatPointArithemticTest();
extern void avxPackedFloatPointCompareTest();
extern void avxPackedFloatPointCompareTest();
extern void avxPackedIntegerArithmeticTest();
extern void avcPackedIntegerPackUnpackTest();

// defined in asm
extern "C" void avxScalarFloatPoint(double a, double b, double c[8]);
extern "C" void avxFloatPointCompare(double a, double b, bool r[8]);
extern "C" void avxPackedFloatPointFloat(const YmmVal * a, const YmmVal * b, YmmVal c[6]);
extern "C" void avxPackedFloatPointDouble(const YmmVal * a, const YmmVal * b, YmmVal c[5]);
extern "C" void avcPackedFloatPointCompare(const YmmVal* a, const YmmVal* b, YmmVal c[8]);

extern "C" void avxPackedInteger16(const YmmVal * a, const YmmVal * b, YmmVal c[6]);
extern "C" void avxPackedInteger32(const YmmVal * a, const YmmVal * b, YmmVal c[5]);
extern "C" void avxPiUnpackDWord2QuadWord(const YmmVal * a, const YmmVal * b, YmmVal c[2]);
extern "C" void avxPiPackDWord2Word(const YmmVal * a, const YmmVal * b, YmmVal * c);