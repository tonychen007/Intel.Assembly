#pragma once

#include "xmmVal.h"

union XmmScalar {
	float				f32;
	double				d64;
	unsigned __int32		i32;
	unsigned __int64		i64;
};

enum CvtOps : unsigned int {
	// si = scalar integer
	// ss = scalar single float-point
	// sd = scalar single double-point

	ECVTSI2SS,	
	ECVTSS2SI,
	ECVTSI2SD,
	ECVTSD2SI,
	ECVTSS2SD,
	ECVTSD2SS,

	EMAX_CVT
};

enum SseRoundMode : unsigned int {
	EROUND,
	EFLOOR,
	ECEILING,
	ETRUNC,

	EMAX_ROUNDMODE
};

// for main cc
extern void sseFloatPointArithemticTest();
extern void sseFloatPointCompareTest();
extern void sseConvertTest();
extern void sseCalcSphereVolumeTest();
extern void sseFloatPointPackedArithemticTest();
extern void sseFloatPointPackedCompareTest();


// defined in asm
extern "C" void sseMathFloat(float a, float b, float c[8]);
extern "C" void sseMathDouble(double a, double b, double c[8]);

extern "C" void sseCompareFloat(float a, float b, bool* result);
extern "C" void sseCompareDouble(double a, double b, bool* result);

extern "C" int sseGetMxcsr();
extern "C" int sseSetMxcsr(int v);
extern "C" SseRoundMode sseGetMxcsrRM();
extern "C" void sseSetMxcsrRM(SseRoundMode rm);
extern "C" void sseScalarConvert(XmmScalar * dst, XmmScalar * src, CvtOps ops);

extern "C" void sseCalcSphereVolume(double r, double* sa, double* v);

/* packed float-point*/
extern "C" void ssePackedMathFloat32(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
extern "C" void ssePackedMathDouble64(const XmmVal * a, const XmmVal * b, XmmVal c[8]);

extern "C" void sseComparePackedFloat32(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
extern "C" void sseComparePackedDouble64(const XmmVal * a, const XmmVal * b, XmmVal c[8]);