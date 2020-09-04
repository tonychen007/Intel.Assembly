#include <stdio.h>
#include <string.h>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../header/MiscDef.h"
#include "../header/xmmVal.h"
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
	printf("addss:\t\t%.6f\n", c[0]);
	printf("subss:\t\t%.6f\n", c[1]);
	printf("mulss:\t\t%.6f\n", c[2]);
	printf("divss:\t\t%.6f\n", c[3]);
	printf("minss:\t\t%.6f\n", c[4]);
	printf("maxss:\t\t%.6f\n", c[5]);
	printf("fabss(b):\t%.6f\n", c[6]);
	printf("sqrtss(fabs(b)):\t%.6f\n", c[7]);
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
	printf("addsd:\t\t%.14f\n", c[0]);
	printf("subsd:\t\t%.14f\n", c[1]);
	printf("mulsd:\t\t%.14f\n", c[2]);
	printf("divsd:\t\t%.14f\n", c[3]);
	printf("minsd:\t\t%.14f\n", c[4]);
	printf("maxsd:\t\t%.14f\n", c[5]);
	printf("fabsd(b):\t%.14f\n", c[6]);
	printf("sqrtsd(fabsd(b)):\t%.14f\n", c[7]);
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

void sseConvertTest() {
	const SseRoundMode sseRM[] = { SseRoundMode::EROUND, SseRoundMode::EFLOOR, SseRoundMode::ECEILING, SseRoundMode::ETRUNC };
	const char* sseRMStr[] = { "Round", "Floor", "Ceiling", "Trunc" };
	const int num_rm = sizeof(sseRM) / sizeof(SseRoundMode);

	XmmScalar src1, src2, dst1, dst2;
	memset(&src1, 0, sizeof(src1));
	memset(&src2, 0, sizeof(src1));
	memset(&dst1, 0, sizeof(src1));
	memset(&dst2, 0, sizeof(src1));


	auto old_mxcsr = sseGetMxcsr();

	// try each round mode
	for (int i = 0; i < num_rm; i++) {
		auto new_rm = sseRM[i];
		sseSetMxcsrRM(new_rm);
		auto old_rm = sseGetMxcsrRM();

		if (new_rm != old_rm) {
			printf("set mxcsr round mode failed!\n");
			printf("new_rm : %d, old_rm :%d\n", new_rm, old_rm);
			return;
		}
		else {
			printf("sse round mode is : %s\n", sseRMStr[old_rm]);

			src1.f32 = (float)M_PI;
			src2.d64 = -M_E;
			sseScalarConvert(&dst1, &src1, CvtOps::ECVTSS2SI);
			printf("cvtss2si : %12f   -> %5d\n", src1.f32, dst1.i32);
			sseScalarConvert(&dst2, &src2, CvtOps::ECVTSD2SI);
			printf("cvtsd2si : %12lf   -> %5d\n", src2.d64, dst2.i32);

			src1.i32 = 3;
			src2.i32 = (1U << 10) - 2;
			// long long not support on x86
			sseScalarConvert(&dst1, &src1, CvtOps::ECVTSI2SS);
			printf("cvtsi2ss :  %12d  -> %12f\n", src1.i32, dst1.f32);
			sseScalarConvert(&dst2, &src2, CvtOps::ECVTSI2SD);
			printf("cvtsi2sd :  %12d  -> %12lf\n", src2.i32, dst2.d64);

			src1.f32 = 3.14f;
			src2.d64 = -M_E;
			sseScalarConvert(&dst1, &src1, CvtOps::ECVTSS2SD);
			printf("cvtss2sd : %12f   -> %12lf\n", src1.f32, dst1.d64);
			sseScalarConvert(&dst2, &src2, CvtOps::ECVTSD2SS);
			printf("cvtsd2ss : %12lf   -> %12f\n", src2.d64, dst2.f32);
		}
	}

	// test for unable convert ss to si
	// mxcsr IE flag (bit 0) is set, 0x80000000 is copied to dst
	printf("\n");
	printf("conver very large float-point value to int32:\n");
	src1.f32 = 23299999999.121212122f;
	sseScalarConvert(&dst1, &src1, CvtOps::ECVTSS2SI);
	auto err_mxcsr_ie = sseGetMxcsr() & 0x1;
	printf("mxcsr Invalid Error Value :%d\n", err_mxcsr_ie);
	printf("cvtss2si : %12f   -> %d(%0x)\n", src1.f32, dst1.i32, dst1.i32);

	sseSetMxcsr(old_mxcsr);
}

void sseCalcSphereVolumeTest() {
	double r[] = { -1.0, 0.0, 3.0, 5.0 };
	double sa, v;

	for (int i = 0; i < sizeof(r) / sizeof(double); i++) {
		sseCalcSphereVolume(r[i], &sa, &v);
		printf("Radius : %lf, Surface Area : %lf, Volume : %lf\n", r[i], sa, v);
	}
}


void ssePackedFloatPointArithemtic() {
	// xmmVal must be 16 byte align
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[8];
	char buf[256] = { '\0' };
	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c, 0, sizeof(c));

	FILL_XMMVAL_32(a.r32, 36.0f, 1.0f / 32.0f, 2.0f, 42.0f);
	FILL_XMMVAL_32(b.r32, -1.0f / 9.0f, 64.0f, -0.0625f, 8.66667f);
	ssePackedMathFloat32(&a, &b, c);

	printf("result for ssePackedMathFloat()\n");
	printf("a:\t\t\t%s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b:\t\t\t%s\n", b.ToString_r32(buf, sizeof(buf)));
	printf("\n");
	printf("addps:\t\t\t%s\n", c[0].ToString_r32(buf, sizeof(buf)));
	printf("subps:\t\t\t%s\n", c[1].ToString_r32(buf, sizeof(buf)));
	printf("mulps:\t\t\t%s\n", c[2].ToString_r32(buf, sizeof(buf)));
	printf("divps:\t\t\t%s\n", c[3].ToString_r32(buf, sizeof(buf)));
	printf("minps:\t\t\t%s\n", c[4].ToString_r32(buf, sizeof(buf)));
	printf("maxps:\t\t\t%s\n", c[5].ToString_r32(buf, sizeof(buf)));
	printf("fabps(b):\t\t%s\n", c[6].ToString_r32(buf, sizeof(buf)));
	printf("sqrtps(fabps(b)):\t%s\n", c[7].ToString_r32(buf, sizeof(buf)));
}

void ssePackedDoublePointArithemtic() {
	// xmmVal must be 16 byte align
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[8];
	char buf[256] = { '\0' };
	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c, 0, sizeof(c));

	FILL_XMMVAL_64(a.r64, M_PI, -M_E);
	FILL_XMMVAL_64(b.r64, 2.0, M_1_PI);
	ssePackedMathDouble64(&a, &b, c);

	printf("result for ssePackedMathDouble()\n");
	printf("a:\t\t\t%s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b:\t\t\t%s\n", b.ToString_r64(buf, sizeof(buf)));
	printf("\n");
	printf("addpd:\t\t\t%s\n", c[0].ToString_r64(buf, sizeof(buf)));
	printf("subpd:\t\t\t%s\n", c[1].ToString_r64(buf, sizeof(buf)));
	printf("mulpd:\t\t\t%s\n", c[2].ToString_r64(buf, sizeof(buf)));
	printf("divpd:\t\t\t%s\n", c[3].ToString_r64(buf, sizeof(buf)));
	printf("minpd:\t\t\t%s\n", c[4].ToString_r64(buf, sizeof(buf)));
	printf("maxpd:\t\t\t%s\n", c[5].ToString_r64(buf, sizeof(buf)));
	printf("fabpd(b):\t\t%s\n", c[6].ToString_r64(buf, sizeof(buf)));
	printf("sqrtpd(fabpd(b)):\t%s\n", c[7].ToString_r64(buf, sizeof(buf)));
}

void sseFloatPointPackedArithemticTest() {
	ssePackedFloatPointArithemtic();
	printf("\n");
	ssePackedDoublePointArithemtic();
}