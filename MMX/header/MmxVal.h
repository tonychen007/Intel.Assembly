#pragma once

#include "MiscDef.h"

#define CHAR_FUN(x) char*##x (char* buf, size_t sz)

union MmxVal {
	Int8		i8[8];
	Int16	i16[4];
	Int32	i32[2];
	Int64	i64;

	Uint8	u8[8];
	Uint16	u16[4];
	Uint32	u32[2];
	Uint64	u64;

	CHAR_FUN(ToString_i8);
	CHAR_FUN(ToString_i16);
	CHAR_FUN(ToString_i32);
	CHAR_FUN(ToString_i64);

	CHAR_FUN(ToString_u8);
	CHAR_FUN(ToString_u16);
	CHAR_FUN(ToString_u32);
	CHAR_FUN(ToString_u64);

	CHAR_FUN(ToString_x8);
	CHAR_FUN(ToString_x6);
	CHAR_FUN(ToString_x32);
	CHAR_FUN(ToString_x64);
};
