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

}