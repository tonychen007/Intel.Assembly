#include <stdio.h>
#include <string.h>

#include "../header/MiscDef.h"
using namespace std;

void IntegerAddTest() {
	Int64 a = 100;
	Int64 b = 200;
	Int64 c = -300;
	Int64 d = 400;
	Int64 e = -500;
	Int64 f = 600;

	Int64 sum = IntegerAdd(a, b, c, d, e, f);
	printf("Result for IntegerAdd\n");
	printf("a: %5lld\tb: %5lld\tc: %5lld\n", a, b, c);
	printf("d: %5lld\te: %5lld\tf: %5lld\n", d, e, f);
	printf("sum: %5lld\n", sum);
}

void IntegerMulTest() {
	Int8 a = 2;
	Int16 b = -3;
	Int32 c = 8;
	Int64 d = 4;
	Int8 e = 3;
	Int16 f = -7;
	Int32 g = -5;
	Int64 h = 10;

	Int64 ret = IntegerMul(a, b, c, d, e, f, g, h);
	printf("Result for IntegerMul\n");
	printf("a: %5d\tb: %5d\tc: %5d\td: %5lld\n", a, b, c, d);
	printf("e: %5d\tf: %5d\tg: %5d\th: %5lld\n", e, f, g, h);
	printf("ret: %5lld\n", ret);
}

void IntegerDivTest() {
	Int64 a = 102;
	Int64 b = 7;
	Int64 quo_rem_ab[2];
	Int64 c = 61;
	Int64 d = 9;
	Int64 quo_rem_cd[2];

	IntegerDiv(a, b, quo_rem_ab, c, d, quo_rem_cd);
	printf("Result for IntegerDiv\n");
	printf("a: %5lld\tb: %5lld\n", a, b);
	printf("quo: %5lld\trem: %5lld\n", quo_rem_ab[0], quo_rem_ab[1]);
	printf("c: %5lld\td: %5lld\n", c, d);
	printf("quo: %5lld\trem: %5lld\n", quo_rem_cd[0], quo_rem_cd[1]);
}

void IntegerArithmeticTest() {
	IntegerAddTest();
	printf("\n");
	IntegerMulTest();
	printf("\n");
	IntegerDivTest();
}