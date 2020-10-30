#pragma once

#include "xmmVal.h"

// the struct must match the structure of that
// declared in IntegerOperand.asm
typedef struct {
	Uint8	a8;
	Uint16	a16;
	Uint32	a32;
	Uint64	a64;
	Uint8	b8;
	Uint16	b16;
	Uint32	b32;
	Uint64	b64;
} ClVal;

// for main cc
extern void IntegerArithmeticTest();
extern void MemoryAddressTest();
extern void IntegerOperandTest();
extern void FloatPointArithmeticTest();
extern void CallConventionTest();
extern void CallConventionNonVolatileTest();
extern void CallConventionNonVolatileXMMTest();
extern void CallConventionAutomateTest();

// defined in asm
extern "C" Int64 IntegerAdd(Int64 a, Int64 b, Int64 c, Int64 d, Int64 e, Int64 f);
extern "C" Int64 IntegerMul(Int8 a, Int16 b, Int32 c, Int64 d, Int8 e, Int16 f, Int32 g, Int64 h);
extern "C" Int64 IntegerDiv(Int64 a, Int64 b, Int64 quo_rem_ab[2], Int64 c, Int64 d, Int64 quo_rem_cd[2]);

extern "C" int FibValsNum, FibValsSum;
extern "C" int MemoryAddress(int i, int* v1, int* v2, int* v3, int* v4);
extern "C" void CalcLogical(ClVal * cl, Uint8 c8[3], Uint16 c16[3], Uint32 c32[3], Uint64 c64[3]);
extern "C" double CalcSum(float a, double b, float c, double d, float e, double f);
extern "C" double CalcDist(int x1, double x2, long long y1, double y2, float z1, short z2);
extern "C" Int64 CallConvention(Int8 a, Int16 b, Int32 c, Int64 d, Int8 e, Int16 f, Int32 g, Int64 h);
extern "C" bool CallConventionNonVolatile(const Int64 * a, const Int64 * b, Int32 n, Int64 * sum_a, Int64 * sum_b, Int64 * prod_a, Int64 * prod_b);
extern "C" void CallConventionNonVolatileXMM(double* a, double* b, double* sum, double* prod);
extern "C" void CallConventionAutomate(float * a, float * b, float * sum, float * prod);