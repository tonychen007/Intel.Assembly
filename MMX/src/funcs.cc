#include <stdio.h>
#include <string.h>

#include "../header/MiscDef.h"
#include "../header/MmxVal.h"

enum MmxAddOps : unsigned int {
	EPADDB,		// wraparound
	EPADDSB,		// saturated
	EPADDUSB,	// unsigned-saturated
	EPADDW,		// wraparound WORD
	EPADDSW,		// saturated WORD
	EPADDUSW,	// unsigned-saturated WORD
	EPADDD,		// DWORD

	EMAX_ADDOPS
};

enum MmxShiftOps : unsigned int {
	EPSLLW,		// shift left logical word
	EPSRLW,		// shift right logical word
	EPSRAW,		// shift right arithmetic word
	EPSLLD,		// shift left logical dword
	EPSRLD,		// shift right logical dword
	EPSRAD,		// shift right arithmetic dword

	EMAX_SHIFTOPS
};

enum MmxMulOps : unsigned int {
	EPMADDUBSW,	//	Multiply signed(2nd operand) and unsigned(1st operand) bytes, 
				//  add horizontal pair of signed words, pack saturated signed-words to mm1.

	EPMADDWD,	//	Multiply the packed words in mm by the packed words in mm/m64, 
				//  add adjacent doubleword results, and store in mm.

	EPMUL,		//  Normal signed word mul
	
	EMAX_MULOPS
};

extern "C" MmxVal MmxValAdd(MmxVal a, MmxVal b, MmxAddOps ops);
extern "C" int MmxValShift(MmxVal a, MmxShiftOps ops, int count, MmxVal * b);
extern "C" int MmxValMulSigned(MmxVal a, MmxVal b, MmxMulOps ops, MmxVal * lo, MmxVal * hi);

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

	FILL_MMXVAL_16(a.i16, 1, 2, 3, 4);
	FILL_MMXVAL_16(b.i16, 2, 2, 2, 2);
	MmxValMulSigned(a, b, MmxMulOps::EPMUL, &lo, &hi);
	printf("mul signed word by signed word: EPMUL\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, 1, 2, 3, 4);
	FILL_MMXVAL_16(b.i16, -2, -2, -2, -2);
	MmxValMulSigned(a, b, MmxMulOps::EPMUL, &lo, &hi);
	printf("mul signed word by signed word: EPMUL\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_MMXVAL_16(a.i16, 10, 30, -50, -70);
	FILL_MMXVAL_16(b.i16, 2000, -4000, 6000, -8000);
	MmxValMulSigned(a, b, MmxMulOps::EPMUL, &lo, &hi);
	printf("mul signed word by signed word: EPMUL\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("prod_lo: %s\n", lo.ToString_i32(buf, sizeof(buf)));
	printf("prod_hi: %s\n", hi.ToString_i32(buf, sizeof(buf)));
	printf("\n");
}