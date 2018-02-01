#include "stdafx.h"
#include <map>

// https://msdn.microsoft.com/ko-kr/library/s44w4h2s.aspx

void map_test()
{
	typedef std::map<char, int> ClassMap;

	ClassMap m1;

	m1.insert(ClassMap::value_type('a', 1));
	m1.insert(ClassMap::value_type('b', 2));
	m1.insert(ClassMap::value_type('c', 3));

	std::map<int, std::string> classNameMap{
		{ 1 , "contacts" },
	{ 2, "photo" },
	{ 3, "sms" },
	{ 4, "calllog" },
	{ 5, "bell" },
	{ 6, "wallpaper" },
	{ 7, "adlist" },
	{ 8, "bookmark" },
	{ 9, "memo" },
	{ 10, "video" },
	{ 11, "music" },
	{ 12, "voicerec" },
	{ 13, "telrec" },
	{ 14, "utils" },
	{ 15, "Games" },
	{ 17, "messanger" },
	{ 16, "calendar" },
	{ 18, "alarm" },
	{ 19, "document" },
	{ 231, "lockscreen" },
	{ 312, "certificate" },
	{ 156, "setting" },
	{ 176, "mms" }
	};

	std::string contactName = classNameMap.at(1);

#define GET_CLASS_NAME(x)	classNameMap.at(x).c_str()

	for (auto m : classNameMap) {

		std::cout << "CLASS INDEX(" << m.first << ") = " << GET_CLASS_NAME(m.first) << std::endl;
	}
}

