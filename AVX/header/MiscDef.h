#pragma once

#include "ymmVal.h"
#include "xmmVal.h"

struct CpuidRegs;

enum Brop : unsigned int {
	EOP_BYTE = 0,
	EOP_WORD,
	EOP_DWORD,
	EOP_QWORD,

	EOP_MAX
};

// for main cc
extern void avxFloatPointArithemticTest();
extern void avxFloatPointCompareTest();
extern void avxPackedFloatPointArithemticTest();
extern void avxPackedFloatPointCompareTest();
extern void avxPackedFloatPointCompareTest();
extern void avxPackedIntegerArithmeticTest();
extern void avxPackedIntegerPackUnpackTest();

extern void avxCpuIdTest();
extern void avxDataBroadcastTest();
extern void avxDataBlendTest();
extern void avxDataPermuteTest();
extern void avxDataGatherTest();

extern void avxFMATest();

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

extern "C" void avxCpuId(Uint32 eax, Uint32 ecx, CpuidRegs * out);
extern "C" void avxXgetbv(Uint32 ecx, Uint32* eax, Uint32* edx);

extern "C" void avxDataBroadcastInt(YmmVal * dst, const XmmVal * src, Brop op);
extern "C" void avxDataBroadcastFloat(YmmVal * dst, float val);
extern "C" void avxDataBroadcastDouble(YmmVal * dst, double val);

extern "C" void avxDataBlendFloat(YmmVal * dst, YmmVal * src1, YmmVal * src2, YmmVal * src3);
extern "C" void avxDataBlendByte(YmmVal * dst, YmmVal * src1, YmmVal * src2, YmmVal * src3);

extern "C" void avxDataPermuteInt(YmmVal * dst, YmmVal * src, YmmVal * ind);
extern "C" void avxDataPermuteFloat(YmmVal * dst, YmmVal * src, YmmVal * ind);
extern "C" void avxDataPermuteFloatInLane(YmmVal * dst, YmmVal * src, YmmVal * ind);

extern "C" void avxDataGatherFloat(YmmVal * dst, YmmVal * index, YmmVal * mask, float* f);
extern "C" void avxDataGatherInt64(YmmVal * dst, YmmVal * index, YmmVal * mask, Int64* f);

extern "C" void avxFMA132SS(float * dst, float * src1, float * src2);
extern "C" void avxFMA132PS(XmmVal * dst, XmmVal * src1, XmmVal * src2);
extern "C" void avxFMA231SS(float* dst, float* src1, float* src2);
extern "C" void avxFMA231PS(XmmVal * dst, XmmVal * src1, XmmVal * src2);