#include <stdio.h>
#include <string.h>
#include <chrono>

#include "../header/MiscDef.h"
using namespace std;

const int cnt = 190000000;
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

void CmpAndTest() {
	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
		__asm {
			cmp eax, 0
		}
	}
	TIME_END;
	TIME_DIFF("cmp");

	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
		__asm {
			test eax, 0
		}
	}
	TIME_END;
	TIME_DIFF("test");
}

void MemoryImmdRegisterImmdTest() {
	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
		__asm {
			cmp dword ptr[ebp + 100], 100
		}
	}
	TIME_END;
	TIME_DIFF("cmp dword ptr");

	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
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
	for (int i = 0; i < cnt; i++) {
		__asm {
			mov eax, 0
		}
	}
	TIME_END;
	TIME_DIFF("mov eax, 0");

	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
		__asm {
			xor eax, eax
		}
	}
	TIME_END;
	TIME_DIFF("xor eax, eax");
}

void BitOperandTest() {
	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
		__asm {
			mov dx, 42
		}
	}
	TIME_END;
	TIME_DIFF("mov dx, 42");

	TIME_BEGIN;
	for (int i = 0; i < cnt; i++) {
		__asm {
			mov edx, 42
		}
	}
	TIME_END;
	TIME_DIFF("mov edx, 42");
}

void BasicOptimizationTest() {
	CmpAndTest();
	printf("\n");
	MemoryImmdRegisterImmdTest();
	printf("\n");
	MoveZeroXorXorTest();
	printf("\n");
	BitOperandTest();
}