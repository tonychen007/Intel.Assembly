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

// 256 bit
union YmmVal {
	Int8	i8[32];
	Int16	i16[16];
	Int32	i32[8];
	Int64	i64[4];

	Uint8	u8[32];
	Uint16	u16[16];
	Uint32	u32[8];
	Uint64	u64[4];

	float   r32[8];
	double  r64[4];

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

	CHAR_FUN(ToString_r32);
	CHAR_FUN(ToString_r64);
};


#define FILL_YmmVal_8(arr,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20,v21,v22,v23,v24,v25,v26,v27,v28,v29,v30,v31,v32) { \
	arr[0] = v1;   arr[1] = v2;   arr[2] = v3;   arr[3] = v4; \
	arr[4] = v5;   arr[5] = v6;   arr[6] = v7;   arr[7] = v8; \
	arr[8] = v9;   arr[9] = v10;  arr[10] = v11; arr[11] = v12; \
	arr[12] = v13; arr[13] = v14; arr[14] = v15; arr[15] = v16; \
	arr[16] = v17; arr[17] = v18; arr[18] = v19; arr[19] = v20; \
	arr[20] = v21; arr[21] = v22; arr[22] = v23; arr[23] = v24; \
	arr[24] = v25; arr[25] = v26; arr[26] = v27; arr[27] = v28; \
	arr[28] = v29; arr[29] = v30; arr[30] = v31; arr[31] = v32; \
}

#define FILL_YmmVal_16(arr,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) { \
	arr[0] = v1;   arr[1] = v2;   arr[2] = v3;   arr[3] = v4; \
	arr[4] = v5;   arr[5] = v6;   arr[6] = v7;   arr[7] = v8; \
	arr[8] = v9;   arr[9] = v10;  arr[10] = v11; arr[11] = v12; \
	arr[12] = v13; arr[13] = v14; arr[14] = v15; arr[15] = v16; \
}

#define FILL_YmmVal_32(arr,v1,v2,v3,v4,v5,v6,v7,v8) { \
	arr[0] = v1; arr[1] = v2; arr[2] = v3; arr[3] = v4; \
	arr[4] = v5; arr[5] = v6; arr[6] = v7; arr[7] = v8; \
}

#define FILL_YmmVal_64(arr,v1,v2,v3,v4) { arr[0] = v1; arr[1] = v2; arr[2] = v3; arr[3] = v4;}