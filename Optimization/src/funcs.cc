#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>

#include "../header/MiscDef.h"
using namespace std;

const int g_cnt = 90000000;
using time_point = chrono::system_clock::time_point;
using time_clock = chrono::system_clock;

template<class Type, class Unit>
using time_duration = chrono::duration<Type, Unit>;

time_point st;
time_point ed;

#define TIME_BEGIN st = time_clock::now()
#define TIME_END   ed = time_clock::now()
#define TIME_DIFF(str) { \
	time_duration<double, std::milli> diff = ed - st; \
	printf("Time for %s is: %lf millis\n", str, diff.count()); \
}

#ifndef _WIN64
void CmpAndTest() {
	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			cmp eax, 0
		}
	}
	TIME_END;
	TIME_DIFF("cmp");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			test eax, 0
		}
	}
	TIME_END;
	TIME_DIFF("test");
}

void MemoryImmdRegisterImmdTest() {
	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			cmp dword ptr[ebp + 100], 100
		}
	}
	TIME_END;
	TIME_DIFF("cmp dword ptr");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			mov eax, [ebp + 100]
			cmp eax, 100
		}
	}
	TIME_END;
	TIME_DIFF("cmp register");
}

void MoveZeroXorXorTest() {
	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			mov eax, 0
		}
	}
	TIME_END;
	TIME_DIFF("mov eax, 0");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			xor eax, eax
		}
	}
	TIME_END;
	TIME_DIFF("xor eax, eax");
}

void BitOperandTest() {
	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			mov dx, 42
		}
	}
	TIME_END;
	TIME_DIFF("mov dx, 42");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		__asm {
			mov edx, 42
		}
	}
	TIME_END;
	TIME_DIFF("mov edx, 42");
}
#endif

#ifndef _WIN64
void BasicOptimizationTest() {
	CmpAndTest();
	printf("\n");
	MemoryImmdRegisterImmdTest();
	printf("\n");
	MoveZeroXorXorTest();
	printf("\n");
	BitOperandTest();
}
#endif

bool CalcResultCpp(float* c, const float* a, const float* b, int n) {
	if ((n <= 0) || ((n & 0x3) != 0))
		return false;

	if (((uintptr_t)a & 0xf) != 0)
		return false;
	if (((uintptr_t)b & 0xf) != 0)
		return false;
	if (((uintptr_t)c & 0xf) != 0)
		return false;

	for (int i = 0; i < n; i++)
		c[i] = sqrt(a[i] * a[i] + b[i] * b[i]);

	return true;
}

bool CompareResult(const float* c1, const float* c2a, const float* c2b, int n, bool pf) {
	const float epsilon = 1.0e-9f;
	bool compare_ok = true;

	for (int i = 0; i < n; i++) {
		if (pf)
			printf("%2d - %10.4f %10.4f %10.4f\n", i, c1[i], c2a[i], c2b[i]);

		bool b1 = fabs(c1[i] - c2a[i]) > epsilon;
		bool b2 = fabs(c1[i] - c2b[i]) > epsilon;

		if (b1 || b2) {
			compare_ok = false;

			if (pf)
				printf("Compare error at index %2d: %f %f %f\n", i, c1[i], c2a[i], c2b[i]);
		}
	}

	return compare_ok;
}

void NonTemporalTest() {
	const int n = 16;
	const int align = 16;

	float* a = (float*)_aligned_malloc(n * sizeof(float), 16);
	float* b = (float*)_aligned_malloc(n * sizeof(float), 16);
	float* c1 = (float*)_aligned_malloc(n * sizeof(float), 16);
	float* c2a = (float*)_aligned_malloc(n * sizeof(float), 16);
	float* c2b = (float*)_aligned_malloc(n * sizeof(float), 16);

	srand(NULL);
	for (int i = 0; i < n; i++) {
		a[i] = (float)(rand() % 100);
		b[i] = (float)(rand() % 100);
	}

	printf("%d%s\n", g_cnt, " Iteration");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		CalcResultCpp(c1, a, b, n);
	}
	TIME_END;
	TIME_DIFF("CalcResultCpp");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		CalcResultMovaps(c2a, a, b, n);
	}
	TIME_END;
	TIME_DIFF("CalcResult movaps");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++) {
		CalcResultMovntps(c2b, a, b, n);
	}
	TIME_END;
	TIME_DIFF("CalcResult movntps - not temporal hint (no cache write)");

#ifdef _WIN64
	const char* platform = "Win64";
#else
	const char* platform = "Win32";
#endif
	printf("Results for NonTemporalStore (platform = %s)\n", platform);
	bool rc = CompareResult(c1, c2a, c2b, n, true);
	if (rc)
		printf("Array compare OK\n");
	else
		printf("Array compare FAILED\n");

	_aligned_free(a);
	_aligned_free(b);
	_aligned_free(c1);
	_aligned_free(c2a);
	_aligned_free(c2b);
}