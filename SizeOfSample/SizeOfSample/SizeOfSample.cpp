// SizeOfSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	std::cout << sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255" << std::endl;

	char tmp[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255"];

	std::cout << sizeof(tmp) << std::endl;

    return 0;
}

