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


// for main cc
void ssePackedFundamentalTest();
void sseHistogramTest();

// defined in asm
extern "C" void ssePackedAdd16(const XmmVal * a, const XmmVal * b, XmmVal c[2]);
extern "C" void ssePackedSub32(const XmmVal * a, const XmmVal * b, XmmVal* c);
extern "C" void ssePackedSub16(const XmmVal* a, const XmmVal* b, XmmVal c[3]);
extern "C" void ssePackedMul32(const XmmVal * a, const XmmVal * b, XmmVal c[2]);
extern "C" void sseHistogram(Uint32 * histo, Uint8 * buff, int num_pixel);
