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