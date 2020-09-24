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

		_aligned_free(buff);
	}	
}

int sseStringReplaceCpp(char* s, char olds, char news) {
	int n = 0;

	while (*s != '\0') {
		if (*s == olds) {
			*s = news;
			n++;
		}
		s++;
	}

	return n;
}

void sseStringReplaceTest() {
	const int long_size = 1024 * 1024 * 2;
	char long_str[long_size + 1];
	for (int i = 0; i < long_size; i++) {
		long_str[i] = rand() % 255;
		if (i % 2 == 0) long_str[i] = '*';
		if (long_str[i] == '\0') long_str[i] = '*';
	}
	long_str[long_size] = '\0';

	const char* testString[] = {
		"*******",
		"***--***+++",
		"*Red*Green*Blue*Yellow*Maroon*White*Black*Orange*Purple*Beige*Silver*Indigo*Fuchsia",
		long_str
	};

	const int numChars = sizeof(testString) / sizeof(char*);
	const int checksum = 0xdeadbeef;
	const int page_size = 4096;
	const int buff_size = 1024 * 1024 * 4;
	const int offset_min = page_size - 40;
	const int offset_max = page_size + 40;
	const char oldchar = '*';
	const char newchar = '#';

	char* buff1 = (char*)_aligned_malloc(buff_size, page_size);
	char* buff2 = (char*)_aligned_malloc(buff_size, page_size);

	if (buff1 == nullptr || buff2 == nullptr) return;

	printf("Result for sseStringReplaceTest.\n");
	printf("OldChar = %c, newChar = %c\n\n", oldchar, newchar);

	chrono::duration<float, milli> ep1(0);
	chrono::duration<float, milli> ep2(0);
	for (int i = 0; i < numChars; i++) {
		const char* s = testString[i];
		int slen = strlen(s);

		for (int offset = offset_min; offset < offset_max; offset++) {
			bool b_print = (offset == offset_min) ? true : false;
			char* s1 = buff1 + offset;
			char* s2 = buff2 + offset;
			int size = buff_size - offset;
			int n1 = -1, n2 = -1;

			strcpy_s(s1, size, s);
			strcpy_s(s2, size, s);
			*(s1 + slen + 1) = oldchar;
			*(unsigned int*)(s1 + slen + 2) = checksum;
			*(s2 + slen + 1) = oldchar;
			*(unsigned int*)(s2 + slen + 2) = checksum;

			if (b_print) {
				if (slen < 80) {
					printf("s1 before replace : %s\n", s1);
				}
			}
			auto st1 = chrono::system_clock::now();
			n1 = sseStringReplaceCpp(s1, oldchar, newchar);
			auto ed1 = chrono::system_clock::now();
			if (b_print) {
				if (slen < 80) {
					printf("s1 after replace : %s\n", s1);
				}
			}
			if (b_print) {
				if (slen < 80) {
					printf("s2 before replace : %s\n", s2);
				}
			}
			auto st2 = chrono::system_clock::now();
			n2 = sseStringReplace(s2, oldchar, newchar);
			auto ed2 = chrono::system_clock::now();
			if (b_print) {
				if (slen < 80) {
					printf("s2 after replace : %s\n", s2);
					printf("\n");
				}
			}

			// deal with error
			if (strcmp(s1, s2) != 0) {
				printf("String compare failed! s1 = %s, s2 = %s\n", s1, s2);
			}
			if (n1 != n2) {
				printf("String compared count failed! n1 = %d, n2 = %d\n", n1, n2);
			}
			if (*(s1 + slen + 1) != oldchar) {
				printf("s1 end oldchar overwritten\n");
			}
			if (*(s2 + slen + 1) != oldchar) {
				printf("s2 end oldchar overwritten\n");
			}
			if (*(unsigned int*)(s1 + slen + 2) != checksum) {
				printf("s1 end checksum overwritten\n");
			}
			if (*(unsigned int*)(s2 + slen + 2) != checksum) {
				printf("s2 end checksum overwritten\n");
			}

			ep1 += ed1 - st1;
			ep2 += ed2 - st2;
		}
	}

	printf("\n");
	printf("cpp version time: %f ms\n", ep1.count());
	printf("asm version time: %f ms\n", ep2.count());

	_aligned_free(buff1);
	_aligned_free(buff2);
}