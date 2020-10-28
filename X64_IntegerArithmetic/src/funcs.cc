#include <stdio.h>
#include <string.h>

#include "../header/MiscDef.h"
using namespace std;

void IntegerAddTest() {
	Int64 a = 100;
	Int64 b = 200;
	Int64 c = -300;
	Int64 d = 400;
	Int64 e = -500;
	Int64 f = 600;

	Int64 sum = IntegerAdd(a, b, c, d, e, f);
	printf("Result for IntegerAdd\n");
	printf("a: %5lld\tb: %5lld\tc: %5lld\n", a, b, c);
	printf("d: %5lld\te: %5lld\tf: %5lld\n", d, e, f);
	printf("sum: %5lld\n", sum);
}

void IntegerMulTest() {
	Int8 a = 2;
	Int16 b = -3;
	Int32 c = 8;
	Int64 d = 4;
	Int8 e = 3;
	Int16 f = -7;
	Int32 g = -5;
	Int64 h = 10;

	Int64 ret = IntegerMul(a, b, c, d, e, f, g, h);
	printf("Result for IntegerMul\n");
	printf("a: %5d\tb: %5d\tc: %5d\td: %5lld\n", a, b, c, d);
	printf("e: %5d\tf: %5d\tg: %5d\th: %5lld\n", e, f, g, h);
	printf("ret: %5lld\n", ret);
}

void IntegerDivTest() {
	Int64 a = 102;
	Int64 b = 7;
	Int64 quo_rem_ab[2];
	Int64 c = 61;
	Int64 d = 9;
	Int64 quo_rem_cd[2];

	IntegerDiv(a, b, quo_rem_ab, c, d, quo_rem_cd);
	printf("Result for IntegerDiv\n");
	printf("a: %5lld\tb: %5lld\n", a, b);
	printf("quo: %5lld\trem: %5lld\n", quo_rem_ab[0], quo_rem_ab[1]);
	printf("c: %5lld\td: %5lld\n", c, d);
	printf("quo: %5lld\trem: %5lld\n", quo_rem_cd[0], quo_rem_cd[1]);
}

void IntegerArithmeticTest() {
	IntegerAddTest();
	printf("\n");
	IntegerMulTest();
	printf("\n");
	IntegerDivTest();
}

void MemoryAddressTest() {
	FibValsSum = 0;

	printf("Result for MemoryAddress\n");
	for (int i = -1; i < FibValsNum + 1; i++) {
		int v1 = -1, v2 = -1, v3 = -1, v4 = -1;
		int rc = MemoryAddress(i, &v1, &v2, &v3, &v4);

		printf("i: %2d\trc: %2d - ", i, rc);
		printf("v1: %5d\tv2: %5d\tv3: %5d\tv4: %5d\n", v1, v2, v3, v4);
	}
	printf("\n");
	printf("FibValsSum : %d\n", FibValsSum);
}

void IntegerOperandTest() {
	ClVal x;
	Uint8 c8[3];
	Uint16 c16[3];
	Uint32 c32[3];
	Uint64 c64[3];

	x.a8 = 0x81;
	x.a16 = 0xF0F0;
	x.a32 = 0x87654321;
	x.a64 = 0x0000FFFF00000000;

	x.b8 = 0x88;
	x.b16 = 0x0FF0;
	x.b32 = 0xF000F000;
	x.b64 = 0x0000FFFF00008888;

	CalcLogical(&x, c8, c16, c32, c64);

	printf("Result for CalcLogical\n");
	printf("8 bit operation\n");
	printf("0x%02X & 0x%02X = 0x%02X\n", x.a8, x.b8, c8[0]);
	printf("0x%02X | 0x%02X = 0x%02X\n", x.a8, x.b8, c8[1]);
	printf("0x%02X ^ 0x%02X = 0x%02X\n", x.a8, x.b8, c8[2]);
	printf("\n");

	printf("16 bit operation\n");
	printf("0x%04X & 0x%04X = 0x%04X\n", x.a16, x.b16, c16[0]);
	printf("0x%04X | 0x%04X = 0x%04X\n", x.a16, x.b16, c16[1]);
	printf("0x%04X ^ 0x%04X = 0x%04X\n", x.a16, x.b16, c16[2]);
	printf("\n");

	printf("32 bit operation\n");
	printf("0x%08X & 0x%08X = 0x%08X\n", x.a32, x.b32, c32[0]);
	printf("0x%08X | 0x%08X = 0x%08X\n", x.a32, x.b32, c32[1]);
	printf("0x%08X ^ 0x%08X = 0x%08X\n", x.a32, x.b32, c32[2]);
	printf("\n");

	printf("64 bit operation\n");
	printf("0x%016llX & 0x%016llX = 0x%016llX\n", x.a64, x.b64, c64[0]);
	printf("0x%016llX | 0x%016llX = 0x%016llX\n", x.a64, x.b64, c64[1]);
	printf("0x%016llX ^ 0x%016llX = 0x%016llX\n", x.a64, x.b64, c64[2]);
}