#pragma once

#include "ymmVal.h"

int fetch_bit(Uint32 val, int from, int to) {
	if (val <= 0 || from > to) return 0;

	Uint32 one = 1;
	one = (one << to);
	int diff = to - from;
	for (int i = 0; i < diff; i++) {
		Uint32 one1 = 1;
		one1 = (one1 << (from + diff - 1 - i));
		one += one1;
	}
	
	return (val & one) >> from;
}

struct CpuidRegs {
	Uint32 EAX;
	Uint32 EBX;
	Uint32 ECX;
	Uint32 EDX;
};

// This structure contains status flags for cpuid reportable features
// used in this book.
struct CpuidFeatures {
	// General information
	Uint32 MaxEAX;      // Maximum EAX value supported by cpuid
	char VendorId[13];  // Processor vendor id string

	// Processor feature flags. Set to 'true' if feature extension
	// or instruction group is available for use.
	bool SSE;
	bool SSE2;
	bool SSE3;
	bool SSSE3;
	bool SSE4_1;
	bool SSE4_2;
	bool AVX;
	bool AVX2;
	bool F16C;
	bool FMA;
	bool POPCNT;
	bool BMI1;
	bool BMI2;
	bool LZCNT;
	bool MOVBE;

	// OS enabled feature information
	bool OSXSAVE;       // True if XSAVE feature set is enabled by the OS
	bool SSE_STATE;     // True if XMM state is enabled by the OS
	bool AVX_STATE;     // True if YMM state is enabled by the OS
};