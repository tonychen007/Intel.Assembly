#include <stdio.h>
#include <string.h>
#include <chrono>

#include "../header/MiscDef.h"
using namespace std;

const int cmp_ops = 7;

// Unordered comapre : https://stackoverflow.com/questions/8627331/what-does-ordered-unordered-comparison-mean
// an unordered comparison checks if either operand is a NaN

const char* cmp_ops_Str[cmp_ops] = {
	"UO(unordered compare","Less than", "Less than or equal", "Equal",
	"Not Equal", "Greater than", "Greater than or equal" };

void sseFloatPointArithemtic() {
	float a = 1.4f;
	float b = -1.384732f;
	float c[8];
	memset(&c, 0, sizeof(c));

	sseMathFloat(a, b, c);
	printf("result for sseMathFloat()\n");
	printf("a:\t\t%.6f\n", a);
	printf("b:\t\t%.6f\n", b);
	printf("add:\t\t%.6f\n", c[0]);
	printf("sub:\t\t%.6f\n", c[1]);
	printf("mul:\t\t%.6f\n", c[2]);
	printf("div:\t\t%.6f\n", c[3]);
	printf("min:\t\t%.6f\n", c[4]);
	printf("max:\t\t%.6f\n", c[5]);
	printf("fabs(b):\t%.6f\n", c[6]);
	printf("sqrt(fabs(b)):\t%.6f\n", c[7]);
}

void sseDoublePointArithemtic() {
	double a = 3.14159265358979;
	double b = -2.71828182845905;
	double c[8];
	memset(&c, 0, sizeof(c));

	sseMathDouble(a, b, c);
	printf("result for sseMathDouble()\n");
	printf("a:\t\t%.14f\n", a);
	printf("b:\t\t%.14f\n", b);
	printf("add:\t\t%.14f\n", c[0]);
	printf("sub:\t\t%.14f\n", c[1]);
	printf("mul:\t\t%.14f\n", c[2]);
	printf("div:\t\t%.14f\n", c[3]);
	printf("min:\t\t%.14f\n", c[4]);
	printf("max:\t\t%.14f\n", c[5]);
	printf("fabs(b):\t%.14f\n", c[6]);
	printf("sqrt(fabs(b)):\t%.14f\n", c[7]);
}

void sseFloatPointArithemticTest() {
	sseFloatPointArithemtic();
	printf("\n");
	sseDoublePointArithemtic();
}


void sseFloatPointCompareFloat() {
	const int n = 5;
	float a[n] = { 100.12f, 3.1415926f,-2.71828f,0.0001f, 0.0f };
	float b[n] = { 110.12f, 2.1415926f,-2.71828f,0.0f, 0.0f };

	// set NaN for unordered compare
	b[n - 1] = numeric_limits<float>::quiet_NaN();
	printf("result for sseCompareFloat():\n\n");

	for (int i = 0; i < n; i++) {
		bool ret[cmp_ops];
		
		sseCompareFloat(a[i], b[i], ret);
		printf("a: %8f,\tb: %8f\n", a[i], b[i]);
		for (int j = 0; j < cmp_ops; j++) {
			printf("result of %s = %d\n", cmp_ops_Str[j], ret[j]);
		}
		printf("\n");
	}
}

void sseFloatPointCompareDouble() {
	const int n = 5;
	double a[n] = { 100.12, 3.1415926,-2.71828,0.0001, 0.0 };
	double b[n] = { 110.12, 2.1415926,-2.71828,0.0, 0.0 };

	// set NaN for unordered compare
	b[n - 1] = numeric_limits<double>::quiet_NaN();
	printf("result for sseCompareDouble():\n\n");

	for (int i = 0; i < n; i++) {
		bool ret[cmp_ops];

		sseCompareDouble(a[i], b[i], ret);
		printf("a: %8g,\tb: %8g\n", a[i], b[i]);
		for (int j = 0; j < cmp_ops; j++) {
			printf("result of %s = %d\n", cmp_ops_Str[j], ret[j]);
		}
		printf("\n");
	}
}

void sseFloatPointCompareTest() {
	sseFloatPointCompareFloat();
	printf("\n");
	sseFloatPointCompareDouble();
}