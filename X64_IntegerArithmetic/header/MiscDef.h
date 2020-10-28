#pragma once

#include "xmmVal.h"

// for main cc
extern void IntegerArithmeticTest();
extern void MemoryAddressTest();

// defined in asm
extern "C" Int64 IntegerAdd(Int64 a, Int64 b, Int64 c, Int64 d, Int64 e, Int64 f);
extern "C" Int64 IntegerMul(Int8 a, Int16 b, Int32 c, Int64 d, Int8 e, Int16 f, Int32 g, Int64 h);
extern "C" Int64 IntegerDiv(Int64 a, Int64 b, Int64 quo_rem_ab[2], Int64 c, Int64 d, Int64 quo_rem_cd[2]);

extern "C" int FibValsNum, FibValsSum;
extern "C" int MemoryAddress(int i, int* v1, int* v2, int* v3, int* v4);