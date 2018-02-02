#include "stdafx.h"
#include <map>
#include <functional>

using namespace std;

// https://msdn.microsoft.com/ko-kr/library/s44w4h2s.aspx

void map_test()
{
	typedef std::map<char, int> ClassMap;

	ClassMap m1;

	m1.insert(ClassMap::value_type('a', 1));
	m1.insert(ClassMap::value_type('b', 2));
	m1.insert(ClassMap::value_type('c', 3));

	std::map<int, std::string> classNameMap{
		{ 1 , "a" },
	{ 2, "b" },
	{ 3, "c" },
	{ 4, "d" },
	{ 5, "e" },
	{ 6, "f" },
	{ 7, "g" },
	{ 8, "h" },
	{ 9, "i" },
	{ 10, "j" },
	{ 11, "k" },
	{ 12, "l" },
	{ 13, "m" },
	{ 14, "n" },
	{ 15, "o" },
	{ 17, "p" },
	{ 16, "q" },
	{ 18, "r" },
	{ 19, "s" },
	{ 231, "t" },
	{ 312, "u" },
	{ 156, "v" },
	{ 176, "w" }
	};

	std::string contactName = classNameMap.at(1);

#define GET_CLASS_NAME(x)	classNameMap.at(x).c_str()

	for (auto m : classNameMap) {

		std::cout << "INDEX(" << m.first << ") = " << GET_CLASS_NAME(m.first) << std::endl;
	}
}

// https://msdn.microsoft.com/ko-kr/library/s44w4h2s.aspx

void mt1()
{
	cout << boolalpha;

	map<int, int> m9({ {5, 5}, {6, 6}, {7, 7}, {8, 8} }, less<int>());

	cout << "m9 = ";

	for (auto i : m9) {
		cout << i.first << " " << i.second << ",";
	}

	cout << endl;

	map<int, int> m10({ {9, 9}, {10, 10}, {11, 11}, {12, 12} }, less<int>(), m9.get_allocator());

	cout << "m10 = ";

	for (auto i : m10) {
		cout << i.first << " " << i.second << ",";
	}

	cout << endl;
}