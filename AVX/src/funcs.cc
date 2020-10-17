#include <stdio.h>
#include <string.h>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../header/MiscDef.h"
#include "../header/ymmVal.h"
#include "../header/cpuid.h"
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

	FILL_YMMVAL_64(a.r64, 30.0, 50.4959271, 75.121289438943, 40.454857865);
	FILL_YMMVAL_64(b.r64, 30.0, 40.0, 75.0, 0.0);
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

	FILL_YMMVAL_32(a.r32, 2.0f, 3.5f, -10.75f, 15.0, -12.125f, 3.875f, 2.0f, -6.35f);
	FILL_YMMVAL_32(b.r32, 12.5f, 52.125f, 17.5f, 13.982f, -4.75, 3.0625f, 7.875f, -48.1875f);

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

	FILL_YMMVAL_64(a.r64, 12.0, 13.5, 18.75, 5.0);
	FILL_YMMVAL_64(b.r64, 0.8751223, -125.25, 75.59384394, -98.129813923);

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

	FILL_YMMVAL_64(a.r64, 42.125, -36.875, 22.95, 3.75);
	FILL_YMMVAL_64(b.r64, -0.0625, -67.375, 22.95, numeric_limits < double>::quiet_NaN());
	avcPackedFloatPointCompare(&a, &b, c);

	printf("Result for avxPackedFloatPointCompareTest\n");
	printf("a lo: %s\n", a.ToString_r64(buf, sizeof(buf), false));
	printf("a hi: %s\n", a.ToString_r64(buf, sizeof(buf), true));
	printf("b lo: %s\n", b.ToString_r64(buf, sizeof(buf), false));
	printf("b hi: %s\n", b.ToString_r64(buf, sizeof(buf), true));
	printf("\n");

	for (int i = 0; i < num_ops; i++) {
		printf("%s result\n", ops[i]);
		printf("lo:  %s\n", c[i].ToString_x64(buf, sizeof(buf), false));
		printf("hi:  %s\n", c[i].ToString_x64(buf, sizeof(buf), true));
	}
}

void avxPackedIntegerArithmeticTest16() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[6];
	memset(&c, 0, sizeof(c));

	FILL_YMMVAL_16(a.i16,
		10, 20, 3000, 4000, 30000, 6000, 2000, 4000, 4000, -3600, 6000, -20000, -25000, 8000, 3, -15000);

	FILL_YMMVAL_16(b.i16,
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

	FILL_YMMVAL_32(a.i32, 64, 1024, -2048, 8192, -256, 4096, 16, 512);
	FILL_YMMVAL_32(b.i32, 4, 5, 2, 5, 8, 7, 3, 6);

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

void avxPiUnpackTest() {
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c[2];
	memset(&c, 0, sizeof(c));

	FILL_YMMVAL_32(a.i32, 0x00000000, 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777);
	FILL_YMMVAL_32(b.i32, 0x88888888, 0x99999999, 0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc, 0xdddddddd, 0xeeeeeeee, 0xffffffff);

	avxPiUnpackDWord2QuadWord(&a, &b, c);

	printf("Result for avxPiUnpackDWord2QuadWord\n");
	printf("Unpack dword to quad word\n\n");
	printf("i\ta\t\tb\t\t\tvpunpckldq\t\tvpunpckhdq\n");

	for (int i = 0; i < 8; i++) {
		const char* fs = "0x%08X\t\t";
		printf("%-2d  ", i);
		printf(fs, a.u32[i]);
		printf(fs, b.u32[i]);
		printf(fs, c[0].u32[i]);
		printf(fs, c[1].u32[i]);
		printf("\n");
	}
}

void avxPiPackTest() {
	char buf[256] = { '\0' };
	__declspec(align(32)) YmmVal a;
	__declspec(align(32)) YmmVal b;
	__declspec(align(32)) YmmVal c;
	memset(&c, 0, sizeof(c));

	FILL_YMMVAL_32(a.i32, 10, -200000, 300000, -4000, 9000, 800000, 200, -32769);
	FILL_YMMVAL_32(b.i32, 32768, 5000, 42000, -68000, 25000, 500000, -7000, 12500);

	avxPiPackDWord2Word(&a, &b, &c);

	printf("a lo: %s\n", a.ToString_i32(buf, sizeof(buf), false));
	printf("a hi: %s\n", a.ToString_i32(buf, sizeof(buf), true));
	printf("b lo: %s\n", b.ToString_i32(buf, sizeof(buf), false));
	printf("b hi: %s\n", b.ToString_i32(buf, sizeof(buf), true));
	printf("c lo: %s\n", c.ToString_i16(buf, sizeof(buf), false));
	printf("c hi: %s\n", c.ToString_i16(buf, sizeof(buf), true));
}

void avxPackedIntegerPackUnpackTest() {
	avxPiUnpackTest();
	printf("\n");
	avxPiPackTest();
}

void avxCpuIdTest() {
	CpuidFeatures cf;
	char buf[256] = { '\0' };
	memset(&cf, 0, sizeof(cf));

	// EAX 00H
	CpuidRegs cregs;

	avxCpuId(0, 0, &cregs);
	*(Uint32*)(cf.VendorId) = cregs.EBX;
	*(Uint32*)(cf.VendorId + 4) = cregs.EDX;
	*(Uint32*)(cf.VendorId + 8) = cregs.ECX;
	printf("CPU Vendor: %s\n", cf.VendorId);

	// 0x80000002 - 0x80000004 fetch CPU info
	avxCpuId(0x80000002, 0, &cregs);
	*(Uint32*)(cf.VendorId) = cregs.EAX;
	*(Uint32*)(cf.VendorId + 4) = cregs.EBX;
	*(Uint32*)(cf.VendorId + 8) = cregs.ECX;
	*(Uint32*)(cf.VendorId + 12) = cregs.EDX;
	strcat_s(buf, cf.VendorId);

	avxCpuId(0x80000003, 0, &cregs);
	*(Uint32*)(cf.VendorId) = cregs.EAX;
	*(Uint32*)(cf.VendorId + 4) = cregs.EBX;
	*(Uint32*)(cf.VendorId + 8) = cregs.ECX;
	*(Uint32*)(cf.VendorId + 12) = cregs.EDX;
	strcat_s(buf, cf.VendorId);

	avxCpuId(0x80000004, 0, &cregs);
	*(Uint32*)(cf.VendorId) = cregs.EAX;
	*(Uint32*)(cf.VendorId + 4) = cregs.EBX;
	*(Uint32*)(cf.VendorId + 8) = cregs.ECX;
	*(Uint32*)(cf.VendorId + 12) = cregs.EDX;
	strcat_s(buf, cf.VendorId);

	printf("CPU Brand: %s\n", buf);

	// EAX 01H Family
	// EAX: 
	// 27 - 20  : Extended Family
	// 19 - 16  : Extended Model
	// 11 -  8  : Family ID 
	// 7  -  4  : Model ID
	// 3  -  0  : Stepping ID
	avxCpuId(1, 0, &cregs);
	Uint32 cpu01_edx = cregs.EDX;
	Uint32 cpu01_ecx = cregs.ECX;

	int steppingID = fetch_bit(cregs.EAX, 0, 3);
	int modeID = fetch_bit(cregs.EAX, 4, 7);
	int familyID = fetch_bit(cregs.EAX, 8, 11);
	int extModeID = fetch_bit(cregs.EAX, 16, 19);
	int extFamilyID = fetch_bit(cregs.EAX, 20, 27);
	printf("stepping: %d, mode: %d, family %d, extMode: %d, extFamily: %d\n\n", steppingID, modeID, familyID, extModeID, extFamilyID);

	// EAX 07H SSE MMX AVX support check
	avxCpuId(7, 0, &cregs);
	int cpu07_ebx = cregs.EBX;
	cf.SSE = fetch_bit(cpu01_edx, 25, 25) ? true : false;
	cf.SSE2 = fetch_bit(cpu01_edx, 26, 26) ? true : false;
	cf.SSE3 = fetch_bit(cpu01_ecx, 0, 0) ? true : false;
	cf.SSSE3 = fetch_bit(cpu01_ecx, 9, 9) ? true : false;
	cf.SSE4_1 = fetch_bit(cpu01_ecx, 19, 19) ? true : false;
	cf.SSE4_2 = fetch_bit(cpu01_ecx, 20, 20) ? true : false;
	cf.POPCNT = fetch_bit(cpu01_ecx, 23, 23) ? true : false;
	cf.OSXSAVE = fetch_bit(cpu01_ecx, 27, 27) ? true : false;

	if (cf.OSXSAVE) {
		// see xgetbv_result.jpg
		// XCR0[1] SSE state
		// XCR0[2] AVX state

		Uint32 xgetbv_eax, xgetbv_edx;
		avxXgetbv(0, &xgetbv_eax, &xgetbv_edx);
		cf.SSE_STATE = fetch_bit(xgetbv_eax, 1, 1);
		cf.AVX_STATE = fetch_bit(xgetbv_eax, 2, 2);

		// if SSE and AVX supported by OS		
		if (cf.SSE_STATE && cf.AVX_STATE) {
			cf.AVX = fetch_bit(cpu01_ecx, 28, 28) ? true : false;
			cf.F16C = fetch_bit(cpu01_ecx, 29, 29) ? true : false;
			cf.FMA = fetch_bit(cpu01_ecx, 12, 12) ? true : false;
			cf.AVX2 = fetch_bit(cpu07_ebx, 5, 5) ? true : false;
			cf.MOVBE = fetch_bit(cpu01_ecx, 22, 22) ? true : false;
			cf.BMI1 = fetch_bit(cpu07_ebx, 3, 3) ? true : false;
			cf.BMI2 = fetch_bit(cpu07_ebx, 8, 8) ? true : false;

			avxCpuId(0x80000001, 0, &cregs);
			cf.LZCNT = fetch_bit(cregs.ECX, 5, 5) ? true : false;
		}
	}

	printf("SSE:    %d\n", cf.SSE);
	printf("SSE2:   %d\n", cf.SSE2);
	printf("SSE3:   %d\n", cf.SSE3);
	printf("SSSE3:  %d\n", cf.SSSE3);
	printf("SSE4_1: %d\n", cf.SSE4_1);
	printf("SSE4_2: %d\n", cf.SSE4_2);
	printf("POPCNT: %d\n", cf.POPCNT);
	printf("MOVBE:  %d\n", cf.MOVBE);
	printf("AVX:    %d\n", cf.AVX);
	printf("AVX2:   %d\n", cf.AVX2);
	printf("F16C:   %d\n", cf.F16C);
	printf("FMA:    %d\n", cf.FMA);
	printf("BMI1:   %d\n", cf.BMI1);
	printf("BMI2:   %d\n", cf.BMI2);
	printf("LZCNT:  %d\n", cf.LZCNT);
	printf("\n");
	printf("AVX_STATE:   %d\n", cf.AVX_STATE);
	printf("SSE_STATE:   %d\n", cf.SSE_STATE);
	printf("OSXSAVE:     %d\n", cf.OSXSAVE);
}

void avxDataBroadcastIntegerTest() {
	__declspec(align(16)) XmmVal src;
	__declspec(align(32)) YmmVal dst;
	char buf[512] = { '\0' };

	memset(&src, 0, sizeof(src));
	memset(&dst, 0, sizeof(dst));

	// Broadcast byte
	src.i8[0] = 55;
	avxDataBroadcastInt(&dst, &src, Brop::EOP_BYTE);
	printf("Result for avxDataBroadcastInt byte\n");
	printf("src    : %s\n", src.ToString_i8(buf, sizeof(buf)));
	printf("dst lo : %s\n", dst.ToString_i8(buf, sizeof(buf), false));
	printf("dst hi : %s\n", dst.ToString_i8(buf, sizeof(buf), true));
	printf("\n");

	// Broadcast word
	src.i16[0] = 30000;
	avxDataBroadcastInt(&dst, &src, Brop::EOP_WORD);
	printf("Result for avxDataBroadcastInt word\n");
	printf("src    : %s\n", src.ToString_i16(buf, sizeof(buf)));
	printf("dst lo : %s\n", dst.ToString_i16(buf, sizeof(buf), false));
	printf("dst hi : %s\n", dst.ToString_i16(buf, sizeof(buf), true));
	printf("\n");

	// Broadcast dword
	src.i32[0] = -2000000;
	avxDataBroadcastInt(&dst, &src, Brop::EOP_DWORD);
	printf("Result for avxDataBroadcastInt dword\n");
	printf("src    : %s\n", src.ToString_i32(buf, sizeof(buf)));
	printf("dst lo : %s\n", dst.ToString_i32(buf, sizeof(buf), false));
	printf("dst hi : %s\n", dst.ToString_i32(buf, sizeof(buf), true));
	printf("\n");

	// Broadcast qword
	src.i64[0] = 1234567890123456789L;
	avxDataBroadcastInt(&dst, &src, Brop::EOP_QWORD);
	printf("Result for avxDataBroadcastInt qword\n");
	printf("src    : %s\n", src.ToString_i64(buf, sizeof(buf)));
	printf("dst lo : %s\n", dst.ToString_i64(buf, sizeof(buf), false));
	printf("dst hi : %s\n", dst.ToString_i64(buf, sizeof(buf), true));
}

void avxDataBroadcastFloatDoubleTest() {
	__declspec(align(32)) YmmVal dst;
	char buf[512] = { '\0' };
	memset(&dst, 0, sizeof(dst));

	float f = (float)M_SQRT2;
	avxDataBroadcastFloat(&dst, f);
	printf("Result for avxDataBroadcastFloat\n");
	printf("src    : %f\n", f);
	printf("dst lo : %s\n", dst.ToString_r32(buf, sizeof(buf), false));
	printf("dst hi : %s\n", dst.ToString_r32(buf, sizeof(buf), true));
	printf("\n");

	double d = M_PI;
	avxDataBroadcastDouble(&dst, d);
	printf("Result for avxDataBroadcastDouble\n");
	printf("src    : %.12lf\n", d);
	printf("dst lo : %s\n", dst.ToString_r64(buf, sizeof(buf), false));
	printf("dst hi : %s\n", dst.ToString_r64(buf, sizeof(buf), true));
}

// copy one ele to many eles
void avxDataBroadcastTest() {
	avxDataBroadcastIntegerTest();
	printf("\n");
	avxDataBroadcastFloatDoubleTest();
}

void avxDataBlendFloatTest() {
	char buf[256] = { '\0' };
	const Uint32 mask1 = 0x00000000;  // mask[31] = 0 , copy src 1
	const Uint32 mask2 = 0x80000000;  // mask[31] = 1 , copy src 2
	__declspec(align(32)) YmmVal dst, src1, src2, src3;

	memset(&dst, 0, sizeof(dst));
	memset(&src1, 0, sizeof(src1));
	memset(&src2, 0, sizeof(src2));
	memset(&src3, 0, sizeof(src3));

	FILL_YMMVAL_32(src1.r32, 100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f, 800.0f);
	FILL_YMMVAL_32(src2.r32,
		-1000.0f, -2000.0f, -3000.0f, -4000.0f,
		-5000.0f, -6000.0f, -7000.0f, -8000.0f);

	// copy 2,2,1,2,1,1,2,2
	// -1000,-2000,300,-4000,500,600,-7000,-8000
	FILL_YMMVAL_32(src3.u32, mask2, mask2, mask1, mask2, mask1, mask1, mask2, mask2);
	avxDataBlendFloat(&dst, &src1, &src2, &src3);

	printf("Result for avxDataBlendFloat\n");
	printf("mask: ");
	for (int i = 0; i < 8; i++) {
		int bit = fetch_bit(src3.u32[i], 31, 31);
		if (i < 7) {
			printf("%d,", bit);
		}
		else {
			printf("%d", bit);
		}
	}
	printf("\n\n");
	printf("src1 lo : %s\n", src1.ToString_r32(buf, sizeof(buf), false));
	printf("src1 hi : %s\n", src1.ToString_r32(buf, sizeof(buf), true));
	printf("\n");
	printf("src2 lo : %s\n", src2.ToString_r32(buf, sizeof(buf), false));
	printf("src2 hi : %s\n", src2.ToString_r32(buf, sizeof(buf), true));
	printf("\n");
	printf("src3 lo : %s\n", src3.ToString_x32(buf, sizeof(buf), false));
	printf("src3 hi : %s\n", src3.ToString_x32(buf, sizeof(buf), true));
	printf("\n");
	printf("dst lo  : %s\n", dst.ToString_r32(buf, sizeof(buf), false));
	printf("dst hi  : %s\n", dst.ToString_r32(buf, sizeof(buf), true));
}

void avxDataBlendByteTest() {
	char buf[256] = { '\0' };
	const Uint32 mask1 = 0x00000000;  // mask[31] = 0 , copy src 1
	const Uint32 mask2 = 0x80808080;  // mask[31] = 1 , copy src 2
	__declspec(align(32)) YmmVal dst, src1, src2, src3;

	memset(&dst, 0, sizeof(dst));
	memset(&src1, 0, sizeof(src1));
	memset(&src2, 0, sizeof(src2));
	memset(&src3, 0, sizeof(src3));

	FILL_YMMVAL_32(src1.i32, 100, 200, 300, 400, 500, 600, 700, 800);
	FILL_YMMVAL_32(src2.i32, -1000, -2000, -3000, -4000, -5000, -6000, -7000, -8000);

	// copy 2,2,1,2,1,1,2,2
	// -1000,-2000,300,-4000,500,600,-7000,-8000
	FILL_YMMVAL_32(src3.u32, mask2, mask2, mask1, mask2, mask1, mask1, mask2, mask2);
	avxDataBlendByte(&dst, &src1, &src2, &src3);

	printf("Result for avxDataBlendByte - dword\n");
	printf("mask: ");
	for (int i = 0; i < 8; i++) {
		int bit = fetch_bit(src3.u32[i], 31, 31);
		if (i < 7) {
			printf("%d,", bit);
		}
		else {
			printf("%d", bit);
		}
	}
	printf("\n\n");
	printf("src1 lo : %s\n", src1.ToString_i32(buf, sizeof(buf), false));
	printf("src1 hi : %s\n", src1.ToString_i32(buf, sizeof(buf), true));
	printf("\n");
	printf("src2 lo : %s\n", src2.ToString_i32(buf, sizeof(buf), false));
	printf("src2 hi : %s\n", src2.ToString_i32(buf, sizeof(buf), true));
	printf("\n");
	printf("src3 lo : %s\n", src3.ToString_x32(buf, sizeof(buf), false));
	printf("src3 hi : %s\n", src3.ToString_x32(buf, sizeof(buf), true));
	printf("\n");
	printf("dst lo  : %s\n", dst.ToString_i32(buf, sizeof(buf), false));
	printf("dst hi  : %s\n", dst.ToString_i32(buf, sizeof(buf), true));
}

// copy two packed eles to one packed ele
void avxDataBlendTest() {
	avxDataBlendFloatTest();
	printf("\n");
	avxDataBlendByteTest();
}

void avxDataPermuteIntTest() {
	__declspec(align(32)) YmmVal dst, src, ind;
	char buf[256] = { '\0' };

	FILL_YMMVAL_32(src.i32, 10, 20, 30, 40, 50, 60, 70, 80);
	FILL_YMMVAL_32(ind.i32, 3, 7, 0, 4, 5, 1, 6, 2);

	avxDataPermuteInt(&dst, &src, &ind);
	printf("Result for avxDataPermuteInt\n");
	for (int i = 0; i < 8; i++) {
		printf("dst[%d]: %5d\t", i, dst.i32[i]);
		printf("src[%d]: %5d\t", i, src.i32[i]);
		printf("ind[%d]: %5d\t", i, ind.i32[i]);
		printf("\n");
	}
}

void avxDataPermuteFloatTest() {
	__declspec(align(32)) YmmVal dst, src, ind;

	FILL_YMMVAL_32(src.r32, 100.0f, 200.f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f, 800.0f);
	FILL_YMMVAL_32(ind.i32, 3, 7, 0, 4, 5, 1, 6, 2);

	avxDataPermuteFloat(&dst, &src, &ind);
	printf("Result for avxDataPermuteFloat\n");
	for (int i = 0; i < 8; i++) {
		printf("dst[%d]: %5f\t", i, dst.r32[i]);
		printf("src[%d]: %5f\t", i, src.r32[i]);
		printf("ind[%d]: %5d\t", i, ind.i32[i]);
		printf("\n");
	}
}

void avxDataPermuteFloatInLaneTest() {
	__declspec(align(32)) YmmVal dst, src, ind;

	// Low Lane and High Lane will be treated respectively
	FILL_YMMVAL_32(src.r32, 100.0f, 200.f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f, 800.0f);
	FILL_YMMVAL_32(ind.i32, 3, 2, 2, 0, 1, 3, 3, 2);

	avxDataPermuteFloatInLane(&dst, &src, &ind);
	printf("Result for avxDataPermuteFloatInLane\n");
	for (int i = 0; i < 8; i++) {
		printf("dst[%d]: %5f\t", i, dst.r32[i]);
		printf("src[%d]: %5f\t", i, src.r32[i]);
		printf("ind[%d]: %5d\t", i, ind.i32[i]);
		printf("\n");
	}
}

// permute Ymm using Ymm mask
void avxDataPermuteTest() {
	avxDataPermuteIntTest();
	printf("\n");
	avxDataPermuteFloatTest();
	printf("\n");
	avxDataPermuteFloatInLaneTest();
}

void avxDataGatherFloatTest() {
	const int m_yes = 0x80000000;
	const int m_no = 0x00000000;
	const int n = 15;
	float f[n];
	__declspec(align(32)) YmmVal dst, index, mask;
	memset(&dst, 0, sizeof(dst));

	srand(NULL);
	for (int i = 0; i < n; i++) {
		f[i] = (float)(rand() % 1000);
	}

	FILL_YMMVAL_32(index.i32, 2, 1, 6, 5, 4, 13, 11, 9);
	FILL_YMMVAL_32(mask.i32, m_yes, m_yes, m_no, m_yes, m_yes, m_no, m_yes, m_yes);

	printf("Result for avxDataGatherFloat\n");
	printf("Test array:\n");
	for (int i = 0; i < n; i++) {
		printf("x[%2d]: %6.1f\n", i, f[i]);
	}
	printf("\n");
	printf("Before:\n");
	for (int i = 0; i < 8; i++) {
		printf("dst : %8.1f\t\t", dst.r32[i]);
		printf("idx : %4d\t", index.i32[i]);
		printf("msk : 0x%08X\n", mask.i32[i]);
	}
	avxDataGatherFloat(&dst, &index, &mask, f);
	printf("\n");
	printf("After:\n");
	for (int i = 0; i < 8; i++) {
		printf("dst : %8.1f\t\t", dst.r32[i]);
		printf("idx : %4d\t", index.i32[i]);
		printf("msk : 0x%08X\n", mask.i32[i]);
	}
}

void avxDataGatherInt64Test() {
	const Int64 m_yes = 0x8000000000000000LL;
	const Int64 m_no = 0x00000000;
	const int n = 15;
	Int64 x[n];
	__declspec(align(32)) YmmVal dst, index, mask;
	memset(&dst, 0, sizeof(dst));

	srand(NULL);
	for (int i = 0; i < n; i++) {
		x[i] = ((Int64)(rand() % 1000)) << 20;
	}

	FILL_YMMVAL_32(index.i32, 2, 7, 9, 12, 0, 0, 0, 0);
	FILL_YMMVAL_64(mask.i64, m_yes, m_yes, m_no, m_yes);

	printf("Result for avxDataGatherInt64\n");
	printf("Test array:\n");
	for (int i = 0; i < n; i++) {
		printf("x[%02d]: %8lld\n", i, x[i]);
	}
	printf("\n");
	printf("Before:\n");
	for (int i = 0; i < 4; i++) {
		printf("dst : %8lld\t\t", dst.i64[i]);
		printf("idx : %4d\t", index.i32[i]);
		printf("msk : 0x%016llX\n", mask.i64[i]);
	}
	avxDataGatherInt64(&dst, &index, &mask, x);
	printf("\n");
	printf("After:\n");
	for (int i = 0; i < 4; i++) {
		printf("dst : %8lld\t\t", dst.i64[i]);
		printf("idx : %4d\t", index.i32[i]);
		printf("msk : 0x%016llX\n", mask.i64[i]);
	}
}

// copy array in mem to Ymm
void avxDataGatherTest() {
	avxDataGatherFloatTest();
	printf("\n");
	avxDataGatherInt64Test();
}

void avxFMAScalarTest() {
	float dst = 3.0f;
	float src1 = 2.0f;
	float src2 = (float)M_PI;

	printf("Result for avxFMA132SS: src1 * src3 + src2, save to src1\n");
	printf("Before:\n");
	printf("src1: %f, src2: %f, src3: %f\n", dst, src1, src2);
	avxFMA132SS(&dst, &src1, &src2);
	printf("After:\n");
	printf("src1: %f, src2: %f, src3: %f\n", dst, src1, src2);
	printf("\n");

	dst = 3.0f;
	src1 = 2.0f;
	src2 = (float)M_PI;
	printf("Result for avxFMA231SS: src2 * src3 + src1, save to src1\n");
	printf("Before:\n");
	printf("src1: %f, src2: %f, src3: %f\n", dst, src1, src2);
	avxFMA231SS(&dst, &src1, &src2);
	printf("After:\n");
	printf("src1: %f, src2: %f, src3: %f\n", dst, src1, src2);
}

void avxFMAPackedTest() {
	char buf[256] = { '\0' };
	__declspec(align(16)) XmmVal dst, src1, src2;
	FILL_XMMVAL_32(dst.r32, 1.0f, 2.0f, 3.0f, 4.0f);
	FILL_XMMVAL_32(src1.r32, 2.0f, 3.0f, 4.0f, 1.0f);
	FILL_XMMVAL_32(src2.r32, 3.0f, 4.0f, 6.0f, 2.0f);

	printf("Result for avxFMA132PS: src1 * src3 + src2, save to src1\n");
	printf("Before:\n");
	printf("dst  :%s\n", dst.ToString_r32(buf, sizeof(buf)));
	printf("src1 :%s\n", src1.ToString_r32(buf, sizeof(buf)));
	printf("src2 :%s\n", src2.ToString_r32(buf, sizeof(buf)));
	avxFMA132PS(&dst, &src1, &src2);
	printf("After:\n");
	printf("dst  :%s\n", dst.ToString_r32(buf, sizeof(buf)));
	printf("src1 :%s\n", src1.ToString_r32(buf, sizeof(buf)));
	printf("src2 :%s\n", src2.ToString_r32(buf, sizeof(buf)));
	printf("\n");

	FILL_XMMVAL_32(dst.r32, 1.0f, 2.0f, 3.0f, 4.0f);
	FILL_XMMVAL_32(src1.r32, 2.0f, 3.0f, 4.0f, 1.0f);
	FILL_XMMVAL_32(src2.r32, 3.0f, 4.0f, 6.0f, 2.0f);

	printf("Result for avxFMA231PS: src2 * src3 + src1, save to src1\n");
	printf("Before:\n");
	printf("dst  :%s\n", dst.ToString_r32(buf, sizeof(buf)));
	printf("src1 :%s\n", src1.ToString_r32(buf, sizeof(buf)));
	printf("src2 :%s\n", src2.ToString_r32(buf, sizeof(buf)));
	avxFMA231PS(&dst, &src1, &src2);
	printf("After:\n");
	printf("dst  :%s\n", dst.ToString_r32(buf, sizeof(buf)));
	printf("src1 :%s\n", src1.ToString_r32(buf, sizeof(buf)));
	printf("src2 :%s\n", src2.ToString_r32(buf, sizeof(buf)));
}

void avxFMATest() {
	avxFMAScalarTest();
	printf("\n");
	avxFMAPackedTest();
}

void avxFlagLessMulTest() {
	const int n = 3;
	Uint32 a[n] = { 64,3200,10000000 };
	Uint32 b[n] = { 1001,12,25000000 };

	printf("Result for avxFlagLessMul\n");
	for (int i = 0; i < n; i++) {
		Uint8 fl[2];
		Uint64 c = avxFlagLessMul(a[i], b[i], fl);

		printf("Test case : %d\n", i);
		printf("   a: %u, b: %u, c: %llu\n", a[i], b[i], c);
		printf("   status flag before: 0x%02X\n", fl[0]);
		printf("   status flag before: 0x%02X\n", fl[1]);
		printf("\n");
	}
}

void avxFlagLessShiftTest() {
	const int n = 4;
	Int32 x[n] = { 0x00000008,0x80000080, 0x00000040, 0xfffffc10 };
	Uint32 cnt[n] = { 2,5,3,4 };

	printf("Result for avxFlagLessShift\n");
	for (int i = 0; i < n; i++) {
		Int32 fl[3];
		avxFlagLessShift(x[i], cnt[i], fl);

		printf("Test case : %d\n", i);
		printf("   x			:	0x%08X (%11d) count: %u\n", x[i], x[i], cnt[i]);
		printf("   sarx (arith right)	:	0x%08X (%11d)\n", fl[0], fl[0]);
		printf("   shlx (logical left)  :	0x%08X (%11d)\n", fl[1], fl[1]);
		printf("   shrx (logical right) :	0x%08X (%11d)\n", fl[2], fl[2]);
		printf("\n");
	}
}

void avxGPRegFlagLessTest() {
	avxFlagLessMulTest();
	printf("\n");
	avxFlagLessShiftTest();
}

void avxGPRegBitManipCountZeroBitTest() {
	const int n = 5;
	Uint32 x[n] = { 0x00100000,0x00000800,0x80000000,0x00000001,0 };
	
	printf("Result for avxGPRegBitManipCountZeroBit\n");
	for (int i = 0; i < n; i++) {
		// lzcnt : leading zero
		// tzcnt : trailing zero
		Uint32 lzcnt, tzcnt;
		avxGprCountZeroBits(x[i], &lzcnt, &tzcnt);
		printf("x : 0x%08X  ", x[i]);
		printf("lzcnt(leading zero)  : %2u  ", lzcnt);
		printf("tzcnt(trailing zero) : %2u\n", tzcnt);
	}
}

// bit field extract
void avxGPRegBitManipBextrTest() {
	Uint32 x = 0x12345678;
	Uint8 st = 3;
	Uint8 len = 16;

	printf("Result for avxGPRegBitManipBextr\n");
	Uint32 ret1 = avxGprBextr(x, st, len);
	Uint32 ret2 = fetch_bit(x, st, st + len);
	printf("x: 0x%08X  ", x);
	printf("start: %2u  ", st);
	printf("len: %2u  ", len);
	printf("bextr    : 0x%08X  ", ret1);
	printf("fetch_bit: 0x%08X\n", ret2);
}

void avxGPRegBitManipTestAndNotTest() {
	Uint32 x = 0xff00ff00;
	Uint32 y = 0x12345678;

	printf("Result for avxGPRegBitManipTestAndNot, And of(~y) with x and save in x\n");
	Uint32 ret1 = avxGprAndNot(x, y);
	Uint32 ret2 = x & ~y;
	printf("x: 0x%08X, y: 0x%08X\n\n", x, y);
	printf("z     : 0x% 08X  ", ret1);
	printf("x & ~y: 0x%08X\n", ret2);
}

void avxGPRegBitManipTest() {
	avxGPRegBitManipCountZeroBitTest();
	printf("\n");
	avxGPRegBitManipBextrTest();
	printf("\n");
	avxGPRegBitManipTestAndNotTest();
}