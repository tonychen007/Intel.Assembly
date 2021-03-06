#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

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

void FloatPointArithmeticCalcSumTest() {
	float a = 10.0f;
	double b = 20.0;
	float c = 0.5f;
	double d = 0.0625;
	float e = 15.0f;
	double f = 0.125;

	double sum = CalcSum(a, b, c, d, e, f);

	printf("Result for FloatPointArithmeticCalcSum\n");
	printf("a: %10.4f\tb: %10.4lf\tc: %10.4f\n", a, b, c);
	printf("d: %10.4lf\te: %10.4f\tf: %10.4f\n", d, e, f);
	printf("\nsum: %10.4lf\n", sum);
}

void FloatPointArithmeticCalcDistTest() {
	int x1 = 5;
	double x2 = 12.875;
	long long y1 = 17;
	double y2 = 23.1875;
	float z1 = -2.0625;
	short z2 = -6;

	double dist = CalcDist(x1, x2, y1, y2, z1, z2);

	printf("Result for FloatPointArithmeticCalcDist\n");
	printf("x1: %10d\tx2: %10.4lf\n", x1, x2);
	printf("y1: %10lld\ty2: %10.4lf\n", y1, y2);
	printf("z1: %10.4f\tz2: %10d\n", z1, z2);
	printf("\ndist: %10.8lf\n", dist);
}

void FloatPointArithmeticTest() {
	FloatPointArithmeticCalcSumTest();
	printf("\n");
	FloatPointArithmeticCalcDistTest();
}

void CallConventionTest() {
	Int8 a = 10, e = -20;
	Int16 b = -200, f = 400;
	Int32 c = 300, g = -600;
	Int64 d = 4000, h = -8000;
	Int64 sum = CallConvention(a, b, c, d, e, f, g, h);

	printf("Result for CallConvention (Stack Frame)\n");
	printf("a,b,c,d: %8d %8d %8d %8lld\n", a, b, c, d);
	printf("e,f,g,h: %8d %8d %8d %8lld\n", e, f, g, h);
	printf("sum: %8lld\n", sum);
}

void CallConventionNonVolatileTest() {
	const int n = 6;
	const Int64 a[n] = { 2,-2,-6,7,12,5 };
	const Int64 b[n] = { 3,5,-7,8,4,9 };
	Int64 sum_a, sum_b, prod_a, prod_b;
	memset(&sum_a, 0, sizeof(sum_a));
	memset(&sum_b, 0, sizeof(sum_b));
	memset(&prod_a, 0, sizeof(prod_a));
	memset(&prod_b, 0, sizeof(prod_b));

	printf("Result for CallConvention (Non-volatile register)\n");
	bool rc = CallConventionNonVolatile(a, b, n, &sum_a, &sum_b, &prod_a, &prod_b);

	if (!rc) {
		printf("Invalid code returned from CallConventionNonVolatile\n");
	}
	else {
		for (int i = 0; i < n; i++) {
			printf("%7lld %7lld\n", a[i], b[i]);
		}
		printf("sum_a: %7lld sum_b: %7lld\n", sum_a, sum_b);
		printf("prod_a: %7lld prod_b: %7lld\n", prod_a, prod_b);
	}
}

void CallConventionNonVolatileXMMTest() {
	double a = M_PI;
	double b = 2.0;
	double sum = 0, prod = 0;

	CallConventionNonVolatileXMM(&a, &b, &sum, &prod);

	printf("Result for CallConventionNonVolatileXMM\n");
	printf("a: %.8lf, b: %.8lf\n", a, b);
	printf("sum: %.8lf, prod: %.8lf\n", sum, prod);
}

void CallConventionAutomateTest() {
	float a = 5.0f;
	float b = 2.0f;
	float sum;
	float prod;
	CallConventionAutomate(&a, &b, &sum, &prod);

	printf("Result for CallConventionAutomate\n");
	printf("a = %lf\tb = %lf\n", a, b);
	printf("sum = %lf, prod = %lf\n", sum, prod);
}