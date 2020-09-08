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

const int cmp_packed_ops = 8;
// pseudo Ops
// https://www.felixcloutier.com/x86/cmpps
const char* cmp_packed_ops_Str[cmp_packed_ops]{
	"EQ", "LT", "LE", "UNORD",
	"NEQ", "GE", "GT", "ORD" };


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

void ssePackedFloatPointArithemticTest() {
	ssePackedFloatPointArithemtic();
	printf("\n");
	ssePackedDoublePointArithemtic();
}

void ssePackedFloatPointCompare() {
	// xmmVal must be 16 byte align
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[8];
	char buf[256] = { '\0' };
	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c, 0, sizeof(c));

	FILL_XMMVAL_32(a.r32, 2.0f, 7.0f, -6.0f, 3.0f);
	FILL_XMMVAL_32(b.r32, 1.0f, 12.0f, -6.0f, 8.0f);

	for (int k = 0; k < 2; k++) {
		if (k == 1)
			a.r32[0] = numeric_limits<float>::quiet_NaN();

		ssePackedCompareFloat32(&a, &b, c);
		if ( k != 1)
			printf("Result for ssePackedFloatPointCompare()\n");
		else
			printf("Result for ssePackedFloatPointCompare() - NaN\n");

		printf("0 for False, 0xFFFFFFFF for True. \n");
		printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
		printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
		printf("\n");

		for (int i = 0; i < cmp_packed_ops; i++) {
			char* s = c[i].ToString_x32(buf, sizeof(buf));
			printf("%10s:%s\n", cmp_packed_ops_Str[i], s);
		}
		printf("\n");
	}
}

void ssePackedDoublePointCompare() {
	// xmmVal must be 16 byte align
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[8];
	char buf[256] = { '\0' };
	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));
	memset(&c, 0, sizeof(c));

	FILL_XMMVAL_64(a.r64, M_PI, M_E);
	FILL_XMMVAL_64(b.r64, -M_PI, M_LN10);

	for (int k = 0; k < 2; k++) {
		if (k == 1)
			a.r64[0] = numeric_limits<double>::quiet_NaN();

		ssePackedCompareDouble64(&a, &b, c);
		if (k != 1)
			printf("Result for ssePackedDoublePointCompare()\n");
		else
			printf("Result for ssePackedDoublePointCompare() - NaN\n");

		printf("0 for False, 0xFFFFFFFF for True. \n");
		printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
		printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
		printf("\n");

		for (int i = 0; i < cmp_packed_ops; i++) {
			char* s = c[i].ToString_x64(buf, sizeof(buf));
			printf("%10s:%s\n", cmp_packed_ops_Str[i], s);
		}
		printf("\n");
	}
}

void ssePackedFloatPointCompareTest() {
	ssePackedFloatPointCompare();
	printf("\n");
	ssePackedDoublePointCompare();
}

void seePackedConvertFloat32() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	char buf[256] = { '\0' };

	FILL_XMMVAL_32(a.i32, 10, -500, 600, -1024);
	ssePackedConvert(&b, &a, CvtPackedOps::ECVTDQ2PS);
	printf("Result for converting four doublrword to float-point.\n");
	printf("a: %s\n", a.ToString_i32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_32(a.r32, 1.0f / 3.0f, 2.0f / 3.0f, -a.r32[0] * 2.0f, -a.r32[1] * 2.0f);
	ssePackedConvert(&b, &a, CvtPackedOps::ECVTPS2DQ);
	printf("Result for converting float-point to four doubleword.\n");
	printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_32(a.r32, 1.0f / 3.0f, 2.0f / 3.0f, 0.0, 0.0);
	ssePackedConvert(&b, &a, CvtPackedOps::ECVTPS2PD);
	printf("Result for converting float-point to double-point.\n");
	printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
}

void ssepackedConvertDouble64() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	char buf[256] = { '\0' };


	FILL_XMMVAL_32(a.i32, 10, -500, 0, 0);
	ssePackedConvert(&b, &a, CvtPackedOps::ECVTDQ2PD);
	printf("Result for converting two doublrword to double-point.\n");
	printf("a: %s\n", a.ToString_i32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_64(a.r64, M_PI, M_E);
	ssePackedConvert(&b, &a, CvtPackedOps::ECVTPD2DQ);
	printf("Result for converting double-point to two doubleword.\n");
	printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i32(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_64(a.r64, M_SQRT2, M_SQRT1_2);
	ssePackedConvert(&b, &a, CvtPackedOps::ECVTPD2PS);
	printf("Result for converting double-point to float-point.\n");
	printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
}

void ssePackedConvertTest() {
	seePackedConvertFloat32();
	printf("\n");
	ssepackedConvertDouble64();
}

void sseDotUnPackInstrTest() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	char buf[256] = { '\0' };

	// packed float-point
	FILL_XMMVAL_32(a.r32, 1.0f, 3.1f, 10.0f, 100.0f);
	FILL_XMMVAL_32(b.r32, 2.0f, 5.2f, 201.f, 64.0f);
	
	printf("Result for unpcklps - unpack low bit float-point: a -> b\n");
	printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EUNPACKFP);
	printf("c: %s\n", b.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	printf("Result for movlhps - move packed low bit to high bit float-point: b -> a\n");
	printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EMOVLHPS);
	printf("c: %s\n", b.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_32(a.r32, 1.0f, 2.0f, 3.0f, 4.0f);
	FILL_XMMVAL_32(b.r32, 1.0f, 2.0f, 1.0f, 1.0f);
	printf("Result for dpps - dot product and store in b: b = a * b, 10110011b\n");
	printf("Multiply all the elements with bit 1[4:7] and store in pos [0:3]\n");
	printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EDOTFP);
	printf("c: %s\n", b.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_32(a.r32, 5.0f, 6.0f, 7.0f, 8.0f);
	FILL_XMMVAL_32(b.r32, 1.0f, 2.0f, 3.0f, 4.0f);
	printf("Result for insertps - insert b to a at specific pos 10110101b: a -> b\n");
	printf("src to copy[6:7], dst to be overwritten[4:5], zero-mask[0:3] specifies which dst to zero.\n");
	printf("dst[96:127] = src[64:95] with dst[0:31] and dst[64:95] = 0\n");
	printf("a: %s\n", a.ToString_r32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r32(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EINSERTFP);
	printf("c: %s\n", b.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	// packed double-point
	FILL_XMMVAL_64(a.r64, M_PI, M_E);
	FILL_XMMVAL_64(b.r64, M_1_PI, M_SQRT2);

	printf("Result for unpckhpd - unpack high bit of double-point: a -> b\n");
	printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EUNPACKDP);
	printf("c: %s\n", b.ToString_r64(buf, sizeof(buf)));
	printf("\n");

	printf("Result for movhpd - move mm64(high part of b) to high bit of double-point: b -> a\n");
	printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EMOVHPD);
	printf("c: %s\n", b.ToString_r64(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_64(a.r64, M_PI, M_E);
	FILL_XMMVAL_64(b.r64, 2.0, 1.0);
	printf("Result for dppd - dot product and store in b: b = a * b, 00110001b\n");
	printf("Multiply all the elements with bit 1[4:5] and store in pos [0:1]\n");
	printf("a: %s\n", a.ToString_r64(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_r64(buf, sizeof(buf)));
	sseDotUnpack(&b, &a, DotUnpackMov::EDOTDP);
	printf("c: %s\n", b.ToString_r64(buf, sizeof(buf)));
	printf("\n");
}

void sseMatrixTransTest() {
	Mat4x4 src;
	Mat4x4 dst;
	char buf[256] = {'\0'};
	memset(&dst, 0, sizeof(dst));

	FILL_XMMVAL_32(src.row1.r32, 1.0, 2.0, 3.0, 4.0);
	FILL_XMMVAL_32(src.row2.r32, 5.0, 6.0, 7.0, 8.0);
	FILL_XMMVAL_32(src.row3.r32, 9.0, 10.0, 11.0, 12.0);
	FILL_XMMVAL_32(src.row4.r32, 13.0, 14.0, 15.0, 16.0);

	printf("Result for matrix transpose:\n");
	printf("src matrix is:\n");
	printf("%s\n", src.row1.ToString_r32(buf,sizeof(buf)));
	printf("%s\n", src.row2.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", src.row3.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", src.row4.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	sseMatrixTrans(&dst, &src);

	printf("dst matrix is:\n");
	printf("%s\n", dst.row1.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", dst.row2.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", dst.row3.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", dst.row4.ToString_r32(buf, sizeof(buf)));

	printf("\n");
	FILL_XMMVAL_32(src.row1.r32, 1.0, 0.0, 0.0, 0.0);
	FILL_XMMVAL_32(src.row2.r32, 0.0, 1.0, 0.0, 0.0);
	FILL_XMMVAL_32(src.row3.r32, 0.0, 0.0, 1.0, 0.0);
	FILL_XMMVAL_32(src.row4.r32, 0.0, 0.0, 0.0, 1.0);

	printf("Result for matrix transpose:\n");
	printf("src matrix is:\n");
	printf("%s\n", src.row1.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", src.row2.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", src.row3.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", src.row4.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	sseMatrixTrans(&dst, &src);

	printf("dst matrix is:\n");
	printf("%s\n", dst.row1.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", dst.row2.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", dst.row3.ToString_r32(buf, sizeof(buf)));
	printf("%s\n", dst.row4.ToString_r32(buf, sizeof(buf)));
}