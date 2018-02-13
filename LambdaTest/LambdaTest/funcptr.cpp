#include "stdafx.h"
#include "funcptr.h"

#include <iostream>
#include <algorithm>

using namespace std;

namespace NS {

class A
{
public:
	
	template<class UnaryFunction>
	void RegisterFunc(UnaryFunction f);

	void Do();
	
	void(*m_func)(int,int);
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

class B
{
public:
	void Do();
	A a;
};


void B::Do()
{
	for_each
	a.RegisterFunc([&](int n, int c) {
		std::cout << "register " << n << c << std::endl;
	});

	a.Do();
}


} // namespace NS;



void foo()
{
	/*
	NS::A a;

	a.RegisterFunc([](int n, int c) { 
		std::cout << "register " << n << c<< std::endl; 
	});

	a.Do();
	*/

	NS::B b;

	b.Do();
}

