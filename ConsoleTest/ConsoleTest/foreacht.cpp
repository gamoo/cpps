#include "stdafx.h"
#include "foreacht.h"
#include <algorithm>
#include <map>

using namespace std;

void fe_test()
{
	map<int, int> t{ {1, 2}, {3, 4} };

	for_each(t.begin(), t.end(), [&](pair<int , int> n) {

		cout << n.first << "=" << n.second << endl;
	});

	float f = 0.f;

	cout << (f ? f : 1) << endl;
}