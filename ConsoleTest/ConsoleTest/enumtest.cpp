#include "stdafx.h"
#include "enumtest.h"

using namespace std;

typedef enum {
	TEST_1 = 0,
	TEST_2 = 1,
	TEST_3 = 2
} TestEnum;

void et1()
{
	TestEnum e1 = TEST_1;
	int* p = new int();

	*p = 5;

	cout << "sizeof(int*) = " << sizeof(p) << endl;					// 4
	cout << "sizeof(TestEnum) = " << sizeof(e1) << endl;			// 4
}