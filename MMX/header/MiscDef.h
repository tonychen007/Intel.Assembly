#pragma once

#include "MmxVal.h"

const int SRAND = 14;
const unsigned int ELEMENT_NUM = 0x8000000;

// for main cc
extern void MmxValAddTest();
extern void MmxValShiftTest();
extern void MmxValMulTest1();
extern void MmxValMulTest2();
extern int MmxCalcMinMaxCppTest(Uint8* x, int n, Uint8* umin, Uint8* umax);
extern void MmxCalcMinMaxTest();
extern void MmxCalcMeanTest();

enum MmxAddOps : unsigned int {
	EPADDB,		// wraparound
	EPADDSB,		// saturated
	EPADDUSB,	// unsigned-saturated
	EPADDW,		// wraparound WORD
	EPADDSW,		// saturated WORD
	EPADDUSW,	// unsigned-saturated WORD
	EPADDD,		// DWORD

	EMAX_ADDOPS
};

enum MmxShiftOps : unsigned int {
	EPSLLW,		// shift left logical word
	EPSRLW,		// shift right logical word
	EPSRAW,		// shift right arithmetic word
	EPSLLD,		// shift left logical dword
	EPSRLD,		// shift right logical dword
	EPSRAD,		// shift right arithmetic dword

	EMAX_SHIFTOPS
};

enum MmxMulOps : unsigned int {
	// Multiply signed(2nd operand) and unsigned(1st operand) bytes, 
	// add horizontal pair of signed words, pack saturated signed-words to mm1.
	EPMADDUBSW,

	//	Multiply the packed words in mm by the packed words in mm/m64, 
	//  add adjacent doubleword results, and store in mm.
	EPMADDWD,

	//  Normal signed word mul
	EPMUL,

	EMAX_MULOPS
};

// defined in asm
extern "C" MmxVal MmxValAdd(MmxVal a, MmxVal b, MmxAddOps ops);
extern "C" int MmxValShift(MmxVal a, MmxShiftOps ops, int count, MmxVal * b);
extern "C" int MmxValMulSigned(MmxVal a, MmxVal b, MmxMulOps ops, MmxVal * lo, MmxVal * hi);
extern "C" int MmxCalcMinMax(const Uint8 * x, int n, Uint8 * umin, Uint8 * umax);
extern "C" int MmxCalcMean(const Uint8 * x, int n, int* sum, double* mean);