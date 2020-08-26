#include "../header/MiscDef.h"

//#define TEST_ON

void testCode() {
	// test code
	MmxVal a, b, c;
	FILL_MMXVAL_8(a.i8, 1, 2, 3, 4, 5, 6, 7, 8);
	FILL_MMXVAL_8(b.u8, 2, 2, 2, 2, 2, 2, 2, 2);

	__asm {
		movq mm0, a
		movq mm1, b
		PMADDUBSW mm0, mm1
		movq c, mm0
		emms
	}

	FILL_MMXVAL_16(a.i16, 1, 2, 3, 4);
	FILL_MMXVAL_16(b.i16, 2, 2, 2, 2);

	__asm {
		movq mm0, a
		movq mm1, b
		PMADDWD mm0, mm1
		movq c, mm0
		emms
	}
}

int main() {
	// MmxValAddTest();
	// MmxShiftTest();
	// MmxValMulTest1();
	// MmxValMulTest2();
	// MmxCalcMinMaxTest();
	MmxCalcMeanTest();

#if defined TEST_ON
	testCode();
#endif

	return 0;
}