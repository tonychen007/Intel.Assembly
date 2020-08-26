#include <stdio.h>
#include <string.h>
#include <chrono>

#include "../header/MiscDef.h"
#include "../header/MmxVal.h"
using namespace std;

extern "C" int NMIN = 16;

void MmxValAddByteTest() {
	MmxVal a, b, c;
	char buf[256] = { '\0' };

	// Signed
	FILL_MMXVAL_8(a.i8, 50, 80, -27, -70, -42, 60, 64, 100);
	FILL_MMXVAL_8(b.i8, 30, 64, -32, -80, 90, -85, 90, -30);

	printf("packed byte addition - singed integer:\n");
	printf("a: %s\n", a.ToString_i8(buf, sizeof(buf)));
	printf("b: %s\n\n", b.ToString_i8(buf, sizeof(buf)));

	c = MmxValAdd(a, b, MmxAddOps::EPADDB);
	printf("PADDB wraparound reuslt:\n");
	printf("c: %s\n\n", c.ToString_i8(buf, sizeof(buf)));
	c = MmxValAdd(a, b, MmxAddOps::EPADDSB);
	printf("PADDUSB saturated reuslt:\n");
	printf("c: %s\n", c.ToString_i8(buf, sizeof(buf)));
	printf("\n");

	// Unsigned
	FILL_MMXVAL_8(a.u8, 50, 80, 132, 200, 42, 60, 140, 10);
	FILL_MMXVAL_8(b.u8, 30, 64, 130, 180, 90, 85, 160, 14);

	printf("packed byte addition - unsinged integer:\n");
	printf("a: %s\n", a.ToString_u8(buf, sizeof(buf)));
	printf("b: %s\n\n", b.ToString_u8(buf, sizeof(buf)));

	c = MmxValAdd(a, b, MmxAddOps::EPADDB);
	printf("PADDB wraparound reuslt:\n");
	printf("c: %s\n\n", c.ToString_u8(buf, sizeof(buf)));
	c = MmxValAdd(a, b, MmxAddOps::EPADDUSB);
	printf("PADDSB saturated reuslt:\n");
	printf("c: %s\n", c.ToString_u8(buf, sizeof(buf)));
	printf("*******************************************\n");
}

void MmxValAddWordTest() {
	MmxVal a, b, c;
	char buf[256] = { '\0' };

	// Signed
	FILL_MMXVAL_16(a.i16, 550, 30000, -270, -7000);
	FILL_MMXVAL_16(b.i16, 830, 5000, -320, -32000);

	printf("packed word addition - singed integer:\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n\n", b.ToString_i16(buf, sizeof(buf)));

	c = MmxValAdd(a, b, MmxAddOps::EPADDW);
	printf("PADDW wraparound reuslt:\n");
	printf("c: %s\n\n", c.ToString_i16(buf, sizeof(buf)));
	c = MmxValAdd(a, b, MmxAddOps::EPADDSW);
	printf("PADDSW saturated reuslt:\n");
	printf("c: %s\n", c.ToString_i16(buf, sizeof(buf)));
	printf("\n");

	// Unsigned
	FILL_MMXVAL_16(a.u16, 50, 48000, 132, 10000);
	FILL_MMXVAL_16(b.u16, 30, 20000, 130, 60000);

	printf("packed word addition - unsinged integer:\n");
	printf("a: %s\n", a.ToString_u16(buf, sizeof(buf)));
	printf("b: %s\n\n", b.ToString_u16(buf, sizeof(buf)));

	c = MmxValAdd(a, b, MmxAddOps::EPADDW);
	printf("PADDW wraparound reuslt:\n");
	printf("c: %s\n\n", c.ToString_u16(buf, sizeof(buf)));
	c = MmxValAdd(a, b, MmxAddOps::EPADDUSW);
	printf("PADDUSW saturated reuslt:\n");
	printf("c: %s\n", c.ToString_u16(buf, sizeof(buf)));
	printf("*******************************************\n");
}


void MmxShiftWord() {
	MmxVal a, b;
	int count;
	char buf[256] = { '\0' };

	FILL_MMXVAL_16(a.u16, 0x1234, 0xFF00, 0x00CC, 0x8080);
	count = 2;

	MmxValShift(a, MmxShiftOps::EPSLLW, count, &b);
	printf("shift left logical word - count %d\n", count);
	printf("a: %s\n", a.ToString_x16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_x16(buf, sizeof(buf)));
	printf("\n");

	MmxValShift(a, MmxShiftOps::EPSRLW, count, &b);
	printf("shift right logical word - count %d\n", count);
	printf("a: %s\n", a.ToString_x16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_x16(buf, sizeof(buf)));
	printf("\n");

	MmxValShift(a, MmxShiftOps::EPSRAW, count, &b);
	printf("shift right arithmetic word - count %d\n", count);
	printf("a: %s\n", a.ToString_x16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_x16(buf, sizeof(buf)));
	printf("*******************************************\n");
}

void MmxShiftDword() {
	MmxVal a, b;
	int count;
	char buf[256] = { '\0' };

	FILL_MMXVAL_32(a.u32, 0x00010001, 0x80008000);
	count = 2;

	MmxValShift(a, MmxShiftOps::EPSLLD, count, &b);
	printf("shift left logical dword - count %d\n", count);
	printf("a: %s\n", a.ToString_x32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_x32(buf, sizeof(buf)));
	printf("\n");

	MmxValShift(a, MmxShiftOps::EPSRLD, count, &b);
	printf("shift right logical dword - count %d\n", count);
	printf("a: %s\n", a.ToString_x32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_x32(buf, sizeof(buf)));
	printf("\n");

	MmxValShift(a, MmxShiftOps::EPSRAD, count, &b);
	printf("shift right arithmetic dword - count %d\n", count);
	printf("a: %s\n", a.ToString_x32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_x32(buf, sizeof(buf)));
}

void MmxValAddTest() {
	MmxValAddByteTest();
	MmxValAddWordTest();
}

void MmxValShiftTest() {
	MmxShiftWord();
	MmxShiftDword();
}

void MmxValMulTest1() {
	MmxVal a, b, lo, hi;
	char buf[256] = { '\0' };

	FILL_MMXVAL_8(a.u8, 1, 2, 3, 4, 5, 6, 7, 200);
	FILL_MMXVAL_8(b.i8, -100, 2, 2, 2, 2, 2, 2, -2);
	MmxValMulSigned(a, b, MmxMulOps::EPMADDUBSW, &lo, &hi);
	printf("mul signed byte by unsigned byte, and add: EPMADDUBSW\n");
	printf("a: %s\n", a.ToString_u8(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i8(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i16(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i16(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_8(a.u8, 1, 2, 3, 4, 5, 6, 7, 200);
	FILL_MMXVAL_8(b.i8, 5, 2, 2, 2, 2, 2, 2, 5);
	MmxValMulSigned(a, b, MmxMulOps::EPMADDUBSW, &lo, &hi);
	printf("mul signed byte by unsigned byte, and add: EPMADDUBSW\n");
	printf("a: %s\n", a.ToString_u8(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i8(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i16(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i16(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, -2, 32000, 3000, 4000);
	FILL_MMXVAL_16(b.i16, -2000, -20, 2, -2);
	MmxValMulSigned(a, b, MmxMulOps::EPMADDWD, &lo, &hi);
	printf("mul signed word by signed word, and add: EPMADDWD\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, 2, 200, 3, 40);
	FILL_MMXVAL_16(b.i16, 20, 10, 2, 8);
	MmxValMulSigned(a, b, MmxMulOps::EPMADDWD, &lo, &hi);
	printf("mul signed word by signed word, and add: EPMADDWD\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, 0, 0, 32769, 1);
	FILL_MMXVAL_16(b.i16, 1, 1, 1, 1);
	MmxValMulSigned(a, b, MmxMulOps::EPMADDWD, &lo, &hi);
	printf("mul signed word by signed word, and add: EPMADDWD\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");
}

void MmxValMulTest2() {
	MmxVal a, b, lo, hi;
	char buf[256] = { '\0' };
	char xbuf[256] = { '\0' };
	int tmp, low, hiw;

	FILL_MMXVAL_16(a.i16, 1, 2, 3, 4);
	FILL_MMXVAL_16(b.i16, 2, 2, 2, 2);
	MmxValMulSigned(a, b, MmxMulOps::EPMUL, &lo, &hi);
	printf("mul signed word by signed word: EPMUL(pmullw, pmulhw)\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, 1, 2, 3, 4);
	FILL_MMXVAL_16(b.i16, -2, -2, -2, -2);
	MmxValMulSigned(a, b, MmxMulOps::EPMUL, &lo, &hi);
	printf("mul signed word by signed word: EPMUL(pmullw, pmulhw)\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, 10, 30, -50, -70);
	FILL_MMXVAL_16(b.i16, 2000, -4000, 6000, -8000);
	// 0x000A * 0x007D = 0x00004E20, so low bit is 4E20, high bit is 0000
	// 0x001E * 0xF060 = 0xFFFE2B40, so low bit is 2B40, high bit is FFFE
	// 0xFFCE * 0x1770 = 0xFFFB6C20, so low bit is 6C20, high bit is FFFB
	// 0xFFBA * 0xE0C0 = 0x00088B80, so low bit is 8B80, high bit is 0008

	MmxValMulSigned(a, b, MmxMulOps::EPMUL, &lo, &hi);
	printf("mul signed word by signed word: EPMUL(pmullw, pmulhw)\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("\n");

	tmp = a.i16[0] * b.i16[0];
	low = tmp & 0x0000FFFF;
	hiw = (tmp & 0xFFFF0000) >> 16;
	printf("%08x * %08x, low bit word is: %04x, high bit word is %04x\n", a.i16[0], b.i16[0], low, hiw);

	tmp = a.i16[1] * b.i16[1];
	low = tmp & 0x0000FFFF;
	hiw = (tmp & 0xFFFF0000) >> 16;
	printf("%08x * %08x, low bit word is: %04x, high bit word is %04x\n", a.i16[1], b.i16[1], low, hiw);

	tmp = a.i16[2] * b.i16[2];
	low = tmp & 0x0000FFFF;
	hiw = (tmp & 0xFFFF0000) >> 16;
	printf("%08x * %08x, low bit word is: %04x, high bit word is %04x\n", a.i16[2], b.i16[2], low, hiw);

	tmp = a.i16[3] * b.i16[3];
	low = tmp & 0x0000FFFF;
	hiw = (tmp & 0xFFFF0000) >> 16;
	printf("%08x * %08x, low bit word is: %04x, high bit word is %04x\n", a.i16[3], b.i16[3], low, hiw);
	printf("\n");

	printf("prod_lo: %s\t(%s)\n", lo.ToString_i32(buf, sizeof(buf)), lo.ToString_x32(xbuf, sizeof(xbuf)));
	printf("prod_hi: %s\t(%s)\n", hi.ToString_i32(buf, sizeof(buf)), hi.ToString_x32(xbuf, sizeof(xbuf)));
	printf("\n");
}

int MmxCalcMinMaxCppTest(Uint8* x, int n, Uint8* umin, Uint8* umax) {
	Uint8 x_min = 0xff;
	Uint8 x_max = 0;

	if (n < NMIN || (n & 0xf) != 0) return -1;

	for (int i = 0; i < n; i++) {
		if (x[i] < x_min) {
			x_min = x[i];
		}
		else if (x[i] > x_max) {
			x_max = x[i];
		}
	}

	*umin = x_min;
	*umax = x_max;

	return 0;
}

int MmxCalcMinMaxTest() {
	int num = ELEMENT_NUM;
	int it = 100;
	bool ret;
	Uint8* arr = new Uint8[num];
	Uint8 umin = 0, umax = 0;

	srand(SRAND);
	for (int i = 0; i < num; i++) {
		arr[i] = (Uint8)(rand() % 240 + 10);
	}

	arr[num / 4] = 4;
	arr[num / 2] = 252;

	// cpp version
	{
		auto st = chrono::system_clock::now();
		for (int i = 0; i < it; i++) {
			ret = MmxCalcMinMaxCppTest(arr, num, &umin, &umax);
		}
		auto ed = chrono::system_clock::now();
		chrono::duration<double, std::milli> ep = ed - st;
		printf("time for cpp version 100 itr: %g ms\n", ep.count());
		printf("min is :%u, max is: %u\n", umin, umax);
	}

	// asm version
	{
		auto st = chrono::system_clock::now();
		for (int i = 0; i < it; i++) {
			ret = MmxCalcMinMax(arr, num, &umin, &umax);
		}
		auto ed = chrono::system_clock::now();
		chrono::duration<double, std::milli> ep = ed - st;
		printf("time for asm version 100 itr: %g ms\n", ep.count());
		printf("min is :%u, max is: %u\n", umin, umax);
	}

	delete[] arr;
	return 0;
}

