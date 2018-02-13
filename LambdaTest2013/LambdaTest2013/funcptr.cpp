#include "stdafx.h"
#include "funcptr.h"

#include <iostream>

using namespace std;


class A
{
public:

	template<class UnaryFunction>
	void RegisterFunc(UnaryFunction f);

	void Do();

	void(*m_func)(int, int);
};

template<class UnaryFunction>
void A::RegisterFunc(UnaryFunction f)
{
	m_func = f;
}

void A::Do()
{
	m_func(5, 3);
}

void foo()
{
	A a;

	a.RegisterFunc([](int n, int c) {
		std::cout << "register " << n << c << std::endl;
	});

	a.Do();
}

