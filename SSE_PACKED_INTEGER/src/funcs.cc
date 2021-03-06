#include <stdio.h>
#include <string.h>
#include <chrono>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../header/MiscDef.h"
#include "../header/xmmVal.h"
using namespace std;

void ssePackedAdd() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[2];
	char buf[256] = { '\0' };

	FILL_XMMVAL_16(a.i16, 10, 200, 30, -32766, 50, 60, 32000, -32000);
	FILL_XMMVAL_16(b.i16, 100, -200, 32760, -400, 500, -600, 1200, -950);
	ssePackedAdd16(&a, &b, c);
	printf("Result for ssePackedAdd\n");
	printf("Signed:\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("c: %s\n", c[0].ToString_i16(buf, sizeof(buf)));
	printf("\n");
	printf("Saturatrd:\n");
	printf("c: %s\n", c[1].ToString_i16(buf, sizeof(buf)));
}

void ssePackedSubDWord() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c;
	memset(&c, 0, sizeof(c));
	char buf[256] = { '\0' };

	FILL_XMMVAL_32(a.i32, 800, 500, 1000, 900);
	FILL_XMMVAL_32(b.i32, 250, -2000, -40, 1200);
	ssePackedSub32(&a, &b, &c);

	printf("Result for ssePackedSub32\n");
	printf("Signed double-word:\n");
	printf("a: %s\n", a.ToString_i32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i32(buf, sizeof(buf)));
	printf("c: %s\n", c.ToString_i32(buf, sizeof(buf)));
	printf("\n");
}

void ssePackSubWord() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[3];
	memset(&c, 0, sizeof(c));
	char buf[256] = { '\0' };

	FILL_XMMVAL_16(a.i16, 10, 200, 30, -32766, 50, 60, 32000, -32000);
	FILL_XMMVAL_16(b.i16, 100, -200, 32760, 400, 500, -600, 1200, -950);
	ssePackedSub16(&a, &b, c);

	// psubsw
	printf("Saturated word:\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("c: %s\n", c[0].ToString_i16(buf, sizeof(buf)));
	printf("\n");

	// psubw
	printf("Signed word:\n");
	printf("a: %s\n", a.ToString_i16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i16(buf, sizeof(buf)));
	printf("c: %s\n", c[1].ToString_i16(buf, sizeof(buf)));
	printf("\n");

	// psubusw
	printf("Unsinged saturated word:\n");
	printf("a: %s\n", a.ToString_u16(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_u16(buf, sizeof(buf)));
	printf("c: %s\n", c[2].ToString_u16(buf, sizeof(buf)));
	printf("\n");
}

void ssePackedMul() {
	__declspec(align(16)) XmmVal a;
	__declspec(align(16)) XmmVal b;
	__declspec(align(16)) XmmVal c[2];
	char buf[256] = { '\0' };

	FILL_XMMVAL_32(a.i32, 150000, 0, 0, 0);
	FILL_XMMVAL_32(b.i32, 150000, 0, 0, 0);
	ssePackedMul32(&a, &b, c);

	printf("Result for ssePackedMul32\n");
	printf("pmulld - store low result, high bit is truncated:\n");
	printf("a: %s\n", a.ToString_i32(buf, sizeof(buf)));
	printf("b: %s\n", b.ToString_i32(buf, sizeof(buf)));
	printf("c: %s\n", c[0].ToString_i32(buf, sizeof(buf)));
	printf("c: %s\n", c[0].ToString_x32(buf, sizeof(buf)));
	printf("\n");
	printf("pmuldq:\n");
	printf("c: %s\n", c[1].ToString_i64(buf, sizeof(buf)));
	printf("c: %s\n", c[1].ToString_x64(buf, sizeof(buf)));
	printf("\n");
}

void ssePackedFundamentalTest() {
	ssePackedAdd();
	printf("\n");
	ssePackedSubDWord();
	ssePackSubWord();
	printf("\n");
	ssePackedMul();
}

void sseHistogramTest() {
	const int buff_size = 1024 * 1024 * 16;
	const int histo_size = 256;

	Uint8* pixel = (Uint8*)_aligned_malloc(buff_size, 32);
	Uint32* histo1 = (Uint32*)_aligned_malloc(histo_size * sizeof(Uint32), 16);
	Uint32* histo2 = (Uint32*)_aligned_malloc(histo_size * sizeof(Uint32), 16);

	if (pixel == nullptr || histo1 == nullptr || histo2 == nullptr) return;

	srand(0);
	auto st = chrono::system_clock::now();
	for (int i = 0; i < buff_size; i++) {
		pixel[i] = rand() % 255;
	}
	auto ed = chrono::system_clock::now();
	chrono::duration<float, milli> ep = ed - st;
	printf("fill data, time is: %f mills\n", ep.count());
	memset(histo1, 0, histo_size);

	{
		auto st = chrono::system_clock::now();
		for (Uint32 i = 0; i < buff_size; i++)
			histo1[pixel[i]]++;
		auto ed = chrono::system_clock::now();
		chrono::duration<float, milli> ep = ed - st;
		printf("cpp histo version, time is: %f mills\n", ep.count());
	}

	{
		auto st = chrono::system_clock::now();
		sseHistogram(histo2, pixel, buff_size);
		auto ed = chrono::system_clock::now();
		chrono::duration<float, milli> ep = ed - st;
		printf("asm histo version, time is: %f mills\n", ep.count());
	}

	int cmp = memcmp(histo1, histo2, histo_size);
	(cmp == 0) ? printf("two histos are the same\n") : printf("two histos are the diffs\n");
}