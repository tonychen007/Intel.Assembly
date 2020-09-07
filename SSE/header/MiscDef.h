#pragma once

#include "xmmVal.h"

union XmmScalar {
	float				f32;
	double				d64;
	unsigned __int32	i32;
	unsigned __int64	i64;
};

__declspec(align(16))
struct Mat4x4 {
	XmmVal row1;
	XmmVal row2;
	XmmVal row3;
	XmmVal row4;
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

enum CvtPackedOps : unsigned int {
	// DQ = doubleword quad, XMM is 128 bit, doubleword is 32 bit, so four doublrword, that is quad.
	// PS = packed single-precision
	// PD = packed double-precision

	ECVTDQ2PS,
	ECVTDQ2PD,
	ECVTPS2DQ,
	ECVTPD2DQ,
	ECVTPS2PD,
	ECVTPD2PS,	

	EMAX_CVTPACKED
};

enum SseRoundMode : unsigned int {
	EROUND,
	EFLOOR,
	ECEILING,
	ETRUNC,

	EMAX_ROUNDMODE
};

enum DotUnpackMov : unsigned int {
	EDOTFP,		// ddps - dot product
	EUNPACKFP,	// unpcklps
	EMOVLHPS,	// movlhps
	EINSERTFP,	// insertps

	EDOTDP,		// ddpd - dot product
	EUNPACKDP,	// unpckhpd
	EMOVHPD,	// movhpd

	EMAX_DOTUNPACK
};

// for main cc
extern void sseFloatPointArithemticTest();
extern void sseFloatPointCompareTest();
extern void sseConvertTest();
extern void sseCalcSphereVolumeTest();
extern void ssePackedFloatPointArithemticTest();
extern void ssePackedFloatPointCompareTest();
extern void ssePackedConvertTest();
extern void sseDotUnPackInstrTest();
extern void sseMatrixTransTest();


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
extern "C" void ssePackedCompareFloat32(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
extern "C" void ssePackedCompareDouble64(const XmmVal * a, const XmmVal * b, XmmVal c[8]);
extern "C" void ssePackedConvert(XmmVal * dst, XmmVal * src, CvtPackedOps ops);

extern "C" void sseDotUnpack(XmmVal * dst, XmmVal * src, DotUnpackMov ops);

extern "C" void sseMatrixTrans(Mat4x4 * dst, Mat4x4 * src);