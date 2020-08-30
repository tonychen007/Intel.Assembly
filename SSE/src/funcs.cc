#include <stdio.h>
#include <string.h>
#include <chrono>

#include "../header/MiscDef.h"
using namespace std;


void sseFloatPointArithemtic() {
	float a = 1.4f;
	float b = -1.384732f;
	float c[8];
	memset(&c, 0, sizeof(c));

	sseMathFloat(a, b, c);
	printf("result for sseMathFloat()\n");
	printf("a:\t\t%.6f\n",a);
	printf("b:\t\t%.6f\n",b);
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