#include "stdafx.h"
#include "tpltest.h"

#include <tuple>
#include <list>
#include <map>

using namespace std;

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

void tuple_test2()
{
	map<pair<int, int>, int> mm{
		{{1, 1}, 3117 },
		{{2, 2}, 3227}
	};

	cout << "pair(1,1) = " << mm[{1, 1}] << endl;
	cout << "pair(1,1) = " << mm[make_pair(2, 2)] << endl;

}
