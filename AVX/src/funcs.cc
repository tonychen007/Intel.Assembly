#include <stdio.h>
#include <string.h>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../header/MiscDef.h"
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