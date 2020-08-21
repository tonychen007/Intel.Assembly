#include <stdio.h>
#include <string.h>

#include "../header/MiscDef.h"
#include "../header/MmxVal.h"

enum MmxAddOps : unsigned int{
	EPADDB,		// wraparound
	EPADDSB,		// saturated
	EPADDUSB,	// unsigned-saturated
	EPADDW,		// wraparound WORD
	EPADDSW,		// saturated WORD
	EPADDUSW,	// unsigned-saturated WORD
	EPADDD,		// DWORD

	EMAX_ADDOPS
};

extern "C" MmxVal MmxValAdd(MmxVal a, MmxVal b, MmxAddOps ops);

void MmxValAddByteTest() {
	MmxVal a, b, c;
	char buf[256] = { '\0' };

	// Signed
	a.i8[0] = 50; a.i8[1] = 80; a.i8[2] = -27; a.i8[3] = -70;
	a.i8[4] = -42; a.i8[5] = 60; a.i8[6] = 64; a.i8[7] = 100;
	b.i8[0] = 30; b.i8[1] = 64; b.i8[2] = -32; b.i8[3] = -80;
	b.i8[4] = 90; b.i8[5] = -85; b.i8[6] = 90; b.i8[7] = -30;

	printf("packed byte addition - singed integer:\n");
	printf("a: %s\n", a.ToString_i8(buf, sizeof(buf)));
	printf("b: %s\n\n", b.ToString_i8(buf, sizeof(buf)));

	c = MmxValAdd(a, b, MmxAddOps::EPADDB);
	printf("PADDB wraparound reuslt:\n");
	printf("c: %s\n\n", c.ToString_i8(buf, sizeof(buf)));
	c = MmxValAdd(a, b, MmxAddOps::EPADDSB);
	printf("PADDUSB saturated reuslt:\n");
	printf("c: %s\n", c.ToString_i8(buf, sizeof(buf)));

	// Unsigned
	printf("\n");
	memset(buf, 0, sizeof buf);
	a.u8[0] = 50; a.u8[1] = 80; a.u8[2] = 132; a.u8[3] = 200;
	a.u8[4] = 42; a.u8[5] = 60; a.u8[6] = 140; a.u8[7] = 10;
	b.u8[0] = 30; b.u8[1] = 64; b.u8[2] = 130; b.u8[3] = 180;
	b.u8[4] = 90; b.u8[5] = 85; b.u8[6] = 160; b.u8[7] = 14;

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
	a.i16[0] = 550; a.i16[1] = 30000; a.i16[2] = -270; a.i16[3] = -7000;
	b.i16[0] = 830; b.i16[1] = 5000; b.i16[2] = -320; b.i16[3] = -32000;

	printf("packed word addition - singed integer:\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n\n", b.ToString_i16(buf, sizeof(buf)));

	c = MmxValAdd(a, b, MmxAddOps::EPADDW);
	printf("PADDW wraparound reuslt:\n");
	printf("c: %s\n\n", c.ToString_i16(buf, sizeof(buf)));
	c = MmxValAdd(a, b, MmxAddOps::EPADDSW);
	printf("PADDSW saturated reuslt:\n");
	printf("c: %s\n", c.ToString_i16(buf, sizeof(buf)));

	// Unsigned
	printf("\n");
	memset(buf, 0, sizeof buf);
	a.u16[0] = 50; a.u16[1] = 48000; a.u16[2] = 132; a.u16[3] = 10000;
	b.u16[0] = 30; b.u16[1] = 20000; b.u16[2] = 130; b.u16[3] = 60000;

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