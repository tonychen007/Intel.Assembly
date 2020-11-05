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

const int g_cnt = 9000000;
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

void* aligned_malloc(size_t required_bytes, size_t alignment) {

	int offset = alignment - 1 + sizeof(void*);
	void* p1 = (void*)malloc(required_bytes + offset);

	if (p1 == NULL)
		return NULL;

	void** p2 = (void**)(((size_t)p1 + offset) & ~(alignment - 1));
	p2[-1] = p1;

	return p2;
}

void aligned_free(void* p2) {
	void* p1 = ((void**)p2)[-1];
	free(p1);
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

	float* a = (float*)aligned_malloc(n * sizeof(float), 16);
	float* b = (float*)aligned_malloc(n * sizeof(float), 16);
	float* c1 = (float*)aligned_malloc(n * sizeof(float), 16);
	float* c2a = (float*)aligned_malloc(n * sizeof(float), 16);
	float* c2b = (float*)aligned_malloc(n * sizeof(float), 16);

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

	aligned_free(a);
	aligned_free(b);
	aligned_free(c1);
	aligned_free(c2a);
	aligned_free(c2b);
}

bool LlCompare(int num_nodes, LlNode* l1, LlNode* l2, LlNode* l3, int* node_fail) {
	const double epsilon = 1.0e-9;

	for (int i = 0; i < num_nodes; i++) {
		*node_fail = i;

		if ((l1 == NULL) || (l2 == NULL) || (l3 == NULL))
			return false;

		for (int j = 0; j < 4; j++) {
			bool b12_c = fabs(l1->ValC[j] - l2->ValC[j]) > epsilon;
			bool b13_c = fabs(l1->ValC[j] - l3->ValC[j]) > epsilon;
			if (b12_c || b13_c)
				return false;

			bool b12_d = fabs(l1->ValD[j] - l2->ValD[j]) > epsilon;
			bool b13_d = fabs(l1->ValD[j] - l3->ValD[j]) > epsilon;
			if (b12_d || b13_d)
				return false;
		}

		l1 = l1->Link;
		l2 = l2->Link;
		l3 = l3->Link;
	}

	*node_fail = -2;
	if ((l1 != NULL) || (l2 != NULL) || (l3 != NULL))
		return false;

	*node_fail = -1;
	return true;
}

void LlPrint(LlNode* p, FILE* fp, const char* msg) {
	int i = 0;
	const char* fs = "%14.6lf %14.6lf %14.6lf %14.6lf\n";

	if (msg != NULL)
		fprintf(fp, "%s\n", msg);

	while (p != NULL) {
		fprintf(fp, "\nLlNode %d [0x%p]\n", i, p);
		fprintf(fp, "  ValA: ");
		fprintf(fp, fs, p->ValA[0], p->ValA[1], p->ValA[2], p->ValA[3]);

		fprintf(fp, "  ValB: ");
		fprintf(fp, fs, p->ValB[0], p->ValB[1], p->ValB[2], p->ValB[3]);

		fprintf(fp, "  ValC: ");
		fprintf(fp, fs, p->ValC[0], p->ValC[1], p->ValC[2], p->ValC[3]);

		fprintf(fp, "  ValD: ");
		fprintf(fp, fs, p->ValD[0], p->ValD[1], p->ValD[2], p->ValD[3]);

		i++;
		p = p->Link;
	}
}

LlNode* LlCreate(int num_nodes) {
	LlNode* first = NULL;
	LlNode* last = NULL;

	srand(83);
	for (int i = 0; i < num_nodes; i++) {
		LlNode* p = (LlNode*)_aligned_malloc(sizeof(LlNode), 64);
		p->Link = NULL;

		if (i == 0)
			first = last = p;
		else {
			last->Link = p;
			last = p;
		}

		for (int i = 0; i < 4; i++) {
			p->ValA[i] = rand() % 500 + 1;
			p->ValB[i] = rand() % 500 + 1;
			p->ValC[i] = 0;
			p->ValD[i] = 0;
		}
	}

	return first;
}

void LlTraverseCpp(LlNode* p) {
	while (p != NULL) {
		for (int i = 0; i < 4; i++)
		{
			p->ValC[i] = sqrt(p->ValA[i] * p->ValA[i] + p->ValB[i] * p->ValB[i]);
			p->ValD[i] = sqrt(p->ValA[i] / p->ValB[i] + p->ValB[i] / p->ValA[i]);
		}
		p = p->Link;
	}
}

void PrefetchTest() {
	const int num_nodes = 8;
	LlNode* list1 = LlCreate(num_nodes);
	LlNode* list2a = LlCreate(num_nodes);
	LlNode* list2b = LlCreate(num_nodes);

#ifdef _WIN64
	const char* platform = "X86-64";
	size_t sizeof_ll_node = sizeof(LlNode);
#else
	const char* platform = "X86-32";
	size_t sizeof_ll_node = sizeof(LlNode);
#endif

	printf("Results for LinkedListPrefetch\n");
	printf("Platform target:  %s\n", platform);
	printf("sizeof(LlNode):   %d\n", sizeof_ll_node);
	printf("LlNode member offsets\n");
	printf("  ValA:           %d\n", offsetof(LlNode, ValA));
	printf("  ValB:           %d\n", offsetof(LlNode, ValB));
	printf("  ValC:           %d\n", offsetof(LlNode, ValC));
	printf("  ValD:           %d\n", offsetof(LlNode, ValD));
	printf("  FreeSpace:      %d\n", offsetof(LlNode, FreeSpace));
	printf("  Link:           %d\n", offsetof(LlNode, Link));
	printf("\n");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++)
		LlTraverseCpp(list1);
	TIME_END;
	TIME_DIFF("LlTraverseCpp");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++)
		LlTraverseAVXNoPrefetch(list2a);
	TIME_END;
	TIME_DIFF("LlTraverseA no prefetch");

	TIME_BEGIN;
	for (int i = 0; i < g_cnt; i++)
		LlTraverseAVXPrefetch(list2b);
	TIME_END;
	TIME_DIFF("LlTraverseB prefetch");

	int node_fail;

	if (!LlCompare(num_nodes, list1, list2a, list2b, &node_fail))
		printf("\nLinked list compare FAILED - node_fail = %d\n", node_fail);
	else
		printf("\nLinked list compare OK\n");

	/*
	FILE* fp = stdout;
	LlPrint(list1, fp, "\n----- list1 -----");
	LlPrint(list2a, fp, "\n ----- list2a -----");
	LlPrint(list2b, fp, "\n ----- list2b -----");
	fclose(fp);
	*/

}