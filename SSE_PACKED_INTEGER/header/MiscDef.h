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