// ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ptrtest.h"
#include "maptest.h"

#include "enumtest.h"
#include "tpltest.h"

int main()
{
#pragma region ptr
	//unique_test();
	//shared_test();
	//week_test();
	//auto_test();
#pragma endregion


#pragma region map
	
	//map_test();
	//mt1();

#pragma endregion


#pragma region enum
	//et1();
#pragma endregion

	tuple_test2();



    return 0;
}

