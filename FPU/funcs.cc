#include <stdio.h>

extern "C" double CtoF(double deg);
extern "C" double FtoC(double deg);

void FtoCTest() {
	double degs[] = { 36.3,35.8, 39.2 };
	const int sz = sizeof degs / sizeof degs[0];
	double fdegs[sz];

	printf("C to F:\n");
	for (int i = 0; i < sz; i++) {
		double f = CtoF(degs[i]);
		printf("C is %lf, F is %lf\n", degs[i], f);
		fdegs[i] = f;
	}

	printf("\n");
	printf("F to C:\n");
	for (int i = 0; i < sz; i++) {
		double f = FtoC(fdegs[i]);
		printf("C is %lf, F is %lf\n", f, fdegs[i]);
	}
}