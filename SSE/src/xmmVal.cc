#pragma once

#include <stdio.h>
#include <string.h>
#include "../header/MiscDef.h"
#include "../header/xmmVal.h"

#define IMPLE_CHAR_FUN(x) T##x(char* buf, size_t sz)

char* XmmVal::IMPLE_CHAR_FUN(oString_i8) {
	snprintf(buf, sz, "%8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d %8d", 
		i8[0], i8[1], i8[2], i8[3], i8[4], i8[5], i8[6], i8[7],
		i8[8], i8[9], i8[10], i8[11], i8[12], i8[13], i8[14], i8[15]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_i16) {
	snprintf(buf, sz, "%8d %8d %8d %8d %8d %8d %8d %8d", 
		i16[0], i16[1], i16[2], i16[3], i16[4], i16[5], i16[6], i16[7]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_i32) {
	snprintf(buf, sz, "%8d %8d %8d %8d", i32[0], i32[1], i32[2], i32[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_i64) {
	snprintf(buf, sz, "%8lld %8lld", i64[0], i64[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_u8) {
	snprintf(buf, sz, "%8u %8u %8u %8u %8u %8u %8u %8u %8u %8u %8u %8u %8u %8u %8u %8u", 
		u8[0], u8[1], u8[2], u8[3], u8[4], u8[5], u8[6], u8[7],
		u8[8], u8[9], u8[10], u8[11], u8[12], u8[13], u8[14], u8[15]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_u16) {
	snprintf(buf, sz, "%8u %8u %8u %8u %8u %8u %8u %8u", 
		u16[0], u16[1], u16[2], u16[3], u16[4], u16[5], u16[6], u16[7]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_u32) {
	snprintf(buf, sz, "%8u %8u %8u %8u", u32[0], u32[1], u32[2], u32[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_u64) {
	snprintf(buf, sz, "%8llu %8llu", u64[0], u64[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_x8) {
	snprintf(buf, sz, "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x", 
		u8[0], u8[1], u8[2], u8[3], u8[4], u8[5], u8[6], u8[7],
		u8[8], u8[9], u8[10], u8[11], u8[12], u8[13], u8[14], u8[15]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_x16) {
	snprintf(buf, sz, "%04x %04x %04x %04x %04x %04x %04x %04x", 
		u16[0], u16[1], u16[2], u16[3], u16[4], u16[5], u16[6], u16[7]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_x32) {
	snprintf(buf, sz, "%08x %08x %08x %08x", u32[0], u32[1], u32[2], u32[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_x64) {
	snprintf(buf, sz, "%16llx %16llx", u64[0], u64[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_r32) {
	snprintf(buf, sz, "%.6f %.6f %.6f %.6f", r32[0], r32[1], r32[2], r32[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* XmmVal::IMPLE_CHAR_FUN(oString_r64) {
	snprintf(buf, sz, "%.12lf %.12lf", r64[0], r64[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}