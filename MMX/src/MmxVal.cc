#pragma once

#include <stdio.h>
#include <string.h>
#include "../header/MiscDef.h"
#include "../header/MmxVal.h"

#define IMPLE_CHAR_FUN(x) T##x(char* buf, size_t sz)

char* MmxVal::IMPLE_CHAR_FUN(oString_i8) {
	snprintf(buf, sz, "%d %d %d %d %d %d %d %d", i8[0], i8[1], i8[2], i8[3], i8[4], i8[5], i8[6], i8[7]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_i16) {
	snprintf(buf, sz, "%d %d %d %d", i16[0], i16[1], i16[2], i16[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_i32) {
	snprintf(buf, sz, "%d %d", i32[0], i32[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_i64) {
	snprintf(buf, sz, "%lld", i64);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_u8) {
	snprintf(buf, sz, "%u %u %u %u %u %u %u %u", u8[0], u8[1], u8[2], u8[3], u8[4], u8[5], u8[6], u8[7]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_u16) {
	snprintf(buf, sz, "%u %u %u %u", u16[0], u16[1], u16[2], u16[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_u32) {
	snprintf(buf, sz, "%u %u", u32[0], u32[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_u64) {
	snprintf(buf, sz, "%llu", u64);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_x8) {
	snprintf(buf, sz, "%02x %02x %02x %02x %02x %02x %02x %02x", u8[0], u8[1], u8[2], u8[3], u8[4], u8[5], u8[6], u8[7]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_x16) {
	snprintf(buf, sz, "%04x %04x %04x %04x", u16[0], u16[1], u16[2], u16[3]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_x32) {
	snprintf(buf, sz, "%08x %08x", u32[0], u32[1]);
	buf[strlen(buf)] = '\0';

	return buf;
}

char* MmxVal::IMPLE_CHAR_FUN(oString_x64) {
	snprintf(buf, sz, "%016llx", u64);
	buf[strlen(buf)] = '\0';

	return buf;
}