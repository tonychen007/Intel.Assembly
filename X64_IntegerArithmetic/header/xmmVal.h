#pragma once

#define CHAR_FUN_XMM(x) char*##x (char* buf, size_t sz)

typedef __int8  Int8;
typedef __int16 Int16;
typedef __int32 Int32;
typedef __int64 Int64;

typedef unsigned __int8  Uint8;
typedef unsigned __int16 Uint16;
typedef unsigned __int32 Uint32;
typedef unsigned __int64 Uint64;

// 128 bit
union XmmVal {
	Int8	i8[16];
	Int16	i16[8];
	Int32	i32[4];
	Int64	i64[2];

	Uint8	u8[16];
	Uint16	u16[8];
	Uint32	u32[4];
	Uint64	u64[2];

	float   r32[4];
	double  r64[2];

	CHAR_FUN_XMM(ToString_i8);
	CHAR_FUN_XMM(ToString_i16);
	CHAR_FUN_XMM(ToString_i32);
	CHAR_FUN_XMM(ToString_i64);

	CHAR_FUN_XMM(ToString_u8);
	CHAR_FUN_XMM(ToString_u16);
	CHAR_FUN_XMM(ToString_u32);
	CHAR_FUN_XMM(ToString_u64);

	CHAR_FUN_XMM(ToString_x8);
	CHAR_FUN_XMM(ToString_x16);
	CHAR_FUN_XMM(ToString_x32);
	CHAR_FUN_XMM(ToString_x64);

	CHAR_FUN_XMM(ToString_r32);
	CHAR_FUN_XMM(ToString_r64);
};


#define FILL_XMMVAL_8(arr,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) { \
	arr[0] = v1;   arr[1] = v2;   arr[2] = v3;   arr[3] = v4; \
	arr[4] = v5;   arr[5] = v6;   arr[6] = v7;   arr[7] = v8; \
	arr[8] = v9;   arr[9] = v10;  arr[10] = v11; arr[11] = v12; \
	arr[12] = v13; arr[13] = v14; arr[14] = v15; arr[15] = v16; \
}

#define FILL_XMMVAL_16(arr,v1,v2,v3,v4,v5,v6,v7,v8) { \
	arr[0] = v1; arr[1] = v2; arr[2] = v3; arr[3] = v4; \
	arr[4] = v5; arr[5] = v6; arr[6] = v7; arr[7] = v8; \
}

#define FILL_XMMVAL_32(arr,v1,v2,v3,v4) { \
	arr[0] = v1; arr[1] = v2; \
	arr[2] = v3; arr[3] = v4; \
}

#define FILL_XMMVAL_64(arr,v1,v2) { arr[0] = v1; arr[1] = v2;}
