#include <stdio.h>
#include <math.h>

extern "C" double CtoF(double deg);
extern "C" double FtoC(double deg);
extern "C" int CalcSphereAreaVolume(double r, double* sa, double* v);
extern "C" int CalcMeanStdev(double* arr, int n, double* mean, double* stdev);

#define ARRSIZE(x) sizeof(x)/sizeof(x[0])

#define PRINT_ARR(x) { \
	int sz = ARRSIZE(x); \
	for (int i = 0; i < sz - 1; i++) { \
		printf("%g,", x[i]); } \
	printf("%g\n", x[sz - 1]); } \

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

void CalcSphereAreaVolumeTest() {
	double sa = 0.0;
	double v = 0.0;
	int rc = -1;

	rc = CalcSphereAreaVolume(-1.0, &sa, &v);
	printf("r: %lf, sa: %lf, v: %lf\n", -1.0, sa, v);
	rc = CalcSphereAreaVolume(3.0, &sa, &v);
	printf("r: %lf, sa: %lf, v: %lf\n", 3.0, sa, v);
	rc = CalcSphereAreaVolume(9.124, &sa, &v);
	printf("r: %lf, sa: %lf, v: %lf\n", 9.124, sa, v);
}

void CalcMeanStdevTest() {
	double arr[] = { 10,2,33,15,41,21,65,6 };
	int sz = ARRSIZE(arr);

	double mean1 = 0, stdev1 = 0;
	double mean2 = 0, stdev2 = 0;
	double t = 0;

	for (int i = 0; i < sz; i++) {
		t += arr[i];
	}
	mean1 = t / sz;
	t = 0;
	for (int i = 0; i < sz; i++) {
		double d = (arr[i] - mean1);
		t += d * d;
	}
	stdev1 = sqrt(t / (sz - 1));
	PRINT_ARR(arr);
	printf("\n");
	printf("mean1 is %g, stddev1 is %g\n", mean1, stdev1);

	CalcMeanStdev(arr, sz, &mean2, &stdev2);
	printf("mean1 is %g, stddev1 is %g\n", mean2, stdev2);
}