#include <stdio.h>
#include <string.h>
#include <chrono>

#include "../header/MiscDef.h"
using namespace std;

void sseStringCalcLengthTest() {
	const int page_size = 4096;
	const int buff_size = 1024 * 1024 * 2;
	const int offset_min = page_size - 40;
	const int offset_max = page_size + 40;

	char long_str[1024 * 768];
	for (int i = 0; i < sizeof(long_str); i++) {
		long_str[i] = 'a' + rand() % 26;
	}

	const char* testString[] =
	{
		"1234567890",										// len < 16
		"123456789012345678",								// 16 < len = 18
		"123456789012345678901234567890abcde",				// 32 < len = 35
		long_str
	};

	const int string_size = sizeof(testString) / sizeof(char*);

	printf("result for sseStringCalcLengthTest()\n");
	for (int i = 0; i < string_size; i++) {
		bool err = false;
		const char* s1 = testString[i];
		chrono::duration<float, milli> ep1(0);
		chrono::duration<float, milli> ep2(0);		

		char* buff = (char*)_aligned_malloc(buff_size, 4096);
		if (buff == nullptr) return;
		
		printf("test string is : %s\n", strlen(s1) < 80 ? s1 : "too long...");
		for (int offset = offset_min; offset < offset_max; offset++) {
			char* s2 = buff + offset;
			memset(buff, 0x55, buff_size);
			//memcpy(s2, s1, buff_size - offset);
			strcpy_s(s2, buff_size - offset, s1);

			auto st1 = chrono::system_clock::now();
			int l1 = strlen(s2);
			auto ed1 = chrono::system_clock::now();
			auto st2 = chrono::system_clock::now();
			int l2 = sseStringCalcLength(s2);
			auto ed2 = chrono::system_clock::now();

			if ((l1 != l2) && !err) {
				err = true;
				printf("String compare failed.\n");
				printf("buff: %p, offset: %d, s2: %p\n", buff, offset, s2);
				printf("len1 : %d, len2: %d\n", l1, l2);
				int test = 0;
			}
			else {
				ep1 += ed1 - st1;
				ep2 += ed2 - st2;
			}
		}

		if (!err) {
			printf("No error detected.\n");
			printf("strlen time is: %f ms\n", ep1.count());
			printf("asm strlen time is: %f ms\n", ep2.count());
			printf("\n");
		}
	}	
}