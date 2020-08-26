#pragma once

#define CHAR_FUN(x) char*##x (char* buf, size_t sz)

typedef __int8  Int8;
typedef __int16 Int16;
typedef __int32 Int32;
typedef __int64 Int64;

typedef unsigned __int8  Uint8;
typedef unsigned __int16 Uint16;
typedef unsigned __int32 Uint32;
typedef unsigned __int64 Uint64;

union MmxVal {
	Int8	i8[8];
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
	CHAR_FUN(ToString_x16);
	CHAR_FUN(ToString_x32);
	CHAR_FUN(ToString_x64);
};


#define FILL_MMXVAL_8(arr,v1,v2,v3,v4,v5,v6,v7,v8) { \
	arr[0] = v1;arr[1] = v2;arr[2] = v3;arr[3] = v4; \
	arr[4] = v5;arr[5] = v6;arr[6] = v7;arr[7] = v8; \
}

#define FILL_MMXVAL_16(arr,v1,v2,v3,v4) { \
	arr[0] = v1;arr[1] = v2;arr[2] = v3;arr[3] = v4; \
}

#define FILL_MMXVAL_32(arr,v1,v2) { \
	arr[0] = v1;arr[1] = v2; \
}

#define FILL_MMXVAL_64(arr,v1) { arr = v1; }
