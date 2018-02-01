#include "stdafx.h"
#include "CppUnitTest.h"

#include <iostream>
#include <utility> // for pair

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSample
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::pair<int, int> p1 = std::make_pair(10, 20);
			std::pair<int, int> p2(30, 40);
			
			Assert::AreEqual(10, p1.first);
			Assert::AreEqual(30, p2.first);
			
			p1.swap(p2);

			Assert::AreEqual(30, p1.first);
			Assert::AreEqual(10, p2.first);

			if (p1 == p2) {

				Assert::Fail(L"Fail");
			}
			else {
				Assert::Fail(L"Success");
			}
		}

	};
}