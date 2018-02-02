#include "stdafx.h"
#include "tpltest.h"

#include <tuple>

// http://ko.cppreference.com/w/cpp/utility/tuple


void tuple_test()
{
	std::tuple<int, int> t1(10, 20);
	std::tuple<int, int> t2 = std::make_tuple(30, 40);

	auto first = std::get<0>(t2);
	auto second = std::get<1>(t2);

	std::cout << "t1.first = " << first << std::endl;

	int x1, x2;
	std::tie(x1, x2) = t1;

	std::cout << "x1 = " << x1 << std::endl;
	std::cout << "x2 = " << x2 << std::endl;
}
