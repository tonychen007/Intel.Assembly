#include <stdio.h>
#include <string.h>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../header/MiscDef.h"
#include "../header/ymmVal.h"
using namespace std;

void avxFloatPointArithemticTest() {
	const char* ops[] = {
		"VADDSD",
		"VSUBSD",
		"VMULSD",
		"VDIVSD",
		"VMINSD",
		"VMAXSD",
		"VSERTSD(a)",
		"VFABSSD(b)"
	};
	const int num_ops = sizeof(ops) / sizeof(char*);

	double a = M_PI;
	double b = -M_LN2;
	double c[num_ops];
	memset(c, 0, sizeof(c));

	avxScalarFloatPoint(a, b, c);

	printf("Result for avxFloatPointArithemticTest\n");
	printf("a = %.6f\n", a);
	printf("b = %.6f\n", b);
	printf("\n");

	for (int i = 0; i < num_ops; i++) {
		printf("%-12s, %.6f\n", ops[i], c[i]);
	}
}

void avxFloatPointCompareTest() {
	const char* ops[] = {
		"VCMPEQSD",
		"VCMPNEQSD",
		"VCMPLTSD",
		"VCMPLESD",
		"VCMPGTSD",
		"VCMPGESD",
		"VCMPORDSD",
		"VCMPUNORDSD"
	};
	const int num_ops = sizeof(ops) / sizeof(char*);
	const int dz = 4;

	YmmVal a;
	YmmVal b;
	bool res[dz][num_ops];

	FILL_YmmVal_64(a.r64, 30.0, 50.4959271, 75.121289438943, 40.454857865);
	FILL_YmmVal_64(b.r64, 30.0, 40.0, 75.0, 0.0);
	b.r64[3] = numeric_limits<double>::quiet_NaN();
	memset(res, 0, sizeof(res));

	for (int i = 0; i < dz; i++) {
		avxFloatPointCompare(a.r64[i], b.r64[i], res[i]);
		printf("a:%8lf, b:%8lf\n", a.r64[i], b.r64[i]);

		for (int j = 0; j < num_ops; j++) {
			printf("%12s = %d\n", ops[j], res[i][j]);
		}
		printf("\n");
	}
}

void avxPackedFloatPointFloat() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[6];
	memset(&c, 0, sizeof(c));

	FILL_YmmVal_32(a.r32, 2.0f, 3.5f, -10.75f, 15.0, -12.125f, 3.875f, 2.0f, -6.35f);
	FILL_YmmVal_32(b.r32, 12.5f, 52.125f, 17.5f, 13.982f, -4.75, 3.0625f, 7.875f, -48.1875f);

	avxPackedFloatPointFloat(&a, &b, c);
	printf("Result for avxPackedFloatPointFloat()\n");
	printf("i\ta\tb\tAdd\tSub\t  Mul\t      Div\tAbs\tNeg\n");
	printf("---------------------------------------------------------------------------\n");

	const char* fs = "%9.3f";
	for (int i = 0; i < 8; i++) {
		printf("%2d ", i);
		printf(fs, a.r32[i]);
		printf(fs, b.r32[i]);
		printf(fs, c[0].r32[i]);
		printf(fs, c[1].r32[i]);
		printf(fs, c[2].r32[i]);
		printf(fs, c[3].r32[i]);
		printf(fs, c[4].r32[i]);
		printf(fs, c[5].r32[i]);
		printf("\n");
	}
}

void avxPackedFloatPointDouble() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[5];
	memset(&c, 0, sizeof(c));

	FILL_YmmVal_64(a.r64, 12.0, 13.5, 18.75, 5.0);
	FILL_YmmVal_64(b.r64, 0.8751223, -125.25, 75.59384394, -98.129813923);

	avxPackedFloatPointDouble(&a, &b, c);
	printf("Result for avxPackedFloatPointDouble()\n");
	printf("i\ta\t\tb\t\tMin\t\tMax\t\tSqrt a\t\tHorizonAdd\tHorizonSub\n");
	printf("--------------------------------------------------------------------");
	printf("----------------------------------------------\n");

	const char* fs = "%17.6lf";
	for (int i = 0; i < 4; i++) {
		printf("%2d ", i);
		printf("%10.6lf", a.r64[i]);
		printf(fs, b.r64[i]);
		printf(fs, c[0].r64[i]);
		printf(fs, c[1].r64[i]);
		printf(fs, c[2].r64[i]);
		printf(fs, c[3].r64[i]);
		printf(fs, c[4].r64[i]);
		printf("\n");
	}
}

void avxPackedFloatPointArithemticTest() {
	avxPackedFloatPointFloat();
	printf("\n");
	avxPackedFloatPointDouble();
}

void avxPackedFloatPointCompareTest() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[8];
	char buf[256] = { '\0' };
	memset(&c, 0, sizeof(c));

	const char* ops[] = {
		"VCMPEQPD",
		"VCMPNEQPD",
		"VCMPLTPD",
		"VCMPLEPD",
		"VCMPGTPD",
		"VCMPGEPD",
		"VCMPORDPD",
		"VCMPUNORDPD"
	};
	const int num_ops = sizeof(ops) / sizeof(char*);

	FILL_YmmVal_64(a.r64, 42.125, -36.875, 22.95, 3.75);
	FILL_YmmVal_64(b.r64, -0.0625, -67.375, 22.95, numeric_limits < double>::quiet_NaN());
	avcPackedFloatPointCompare(&a, &b, c);

	printf("Result for avxPackedFloatPointCompareTest\n");
	printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
	printf("\n");

	for (int i = 0; i < num_ops; i++) {
		printf("%s result\n", ops[i]);
		printf("   %s\n", c[i].ToString_x64(buf, sizeof(buf)));
	}
}

void avxPackedIntegerArithmeticTest16() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[6];
	memset(&c, 0, sizeof(c));

	FILL_YmmVal_16(a.i16,
		10, 20, 3000, 4000, 30000, 6000, 2000, 4000, 4000, -3600, 6000, -20000, -25000, 8000, 3, -15000);

	FILL_YmmVal_16(b.i16,
		1000, 2000, 30, 40, 3000, 32000, -31000, -30000, -2500, -1200, 9000, -20000, -27000, 28700, -32766, 24000);

	avxPackedInteger16(&a, &b, c);
	printf("Result for avxPackedIntegerArithmeticTest16\n");
	printf("[4][5][12][13]- add overflow\n");
	printf("[6][7][14][15]- sub underflow\n");
	printf("\n");
	printf("i\ta\tb\tvpaddw\t\tvpaddsw\t\tvpsubw\t\tvpsubsw\t\tvpminsw\t\tvpmaxsw\n");

	for (int i = 0; i < 16; i++) {
		const char* fs = "%8d";
		const char* fs1 = "%12d\t";

		printf("%2d", i);
		printf(fs, a.i16[i]);
		printf(fs, b.i16[i]);
		printf(fs1, c[0].i16[i]);
		printf(fs1, c[1].i16[i]);
		printf(fs1, c[2].i16[i]);
		printf(fs1, c[3].i16[i]);
		printf(fs1, c[4].i16[i]);
		printf(fs1, c[5].i16[i]);
		printf("\n");
	}
}

void avxPackedIntegerArithmeticTest32() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[5];
	memset(&c, 0, sizeof(c));

	FILL_YmmVal_32(a.i32, 64, 1024, -2048, 8192, -256, 4096, 16, 512);
	FILL_YmmVal_32(b.i32, 4, 5, 2, 5, 8, 7, 3, 6);

	avxPackedInteger32(&a, &b, c);
	printf("Result for avxPackedIntegerArithmeticTest32\n");
	printf("vphaddd - horizon add, vphsubd - horizon sub\n");
	printf("vpsllvd - left shift logical, vpsravd - right shift arithmetic\n");
	printf("\n");
	printf("i\ta\tb\tvphaddd\t\tvphsubd\t\tvpmulld\t\tvpsllvd\t\tvpsravd\n");

	for (int i = 0; i < 8; i++) {
		const char* fs = "%8d";
		const char* fs1 = "%12d\t";

		printf("%2d", i);
		printf(fs, a.i32[i]);
		printf(fs, b.i32[i]);
		printf(fs1, c[0].i32[i]);
		printf(fs1, c[1].i32[i]);
		printf(fs1, c[2].i32[i]);
		printf(fs1, c[3].i32[i]);
		printf(fs1, c[4].i32[i]);
		printf("\n");
	}
}

void avxPackedIntegerArithmeticTest() {
	avxPackedIntegerArithmeticTest16();
	printf("\n");
	avxPackedIntegerArithmeticTest32();
}