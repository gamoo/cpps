#include "stdafx.h"
#include <memory>
#include <string>

using namespace std;

//
// https://msdn.microsoft.com/ko-kr/library/hh279674.aspx
// https://msdn.microsoft.com/en-us/library/hh279674.aspx
// 

void foo()
{
	std::cout << "ptrtest::foo()" << std::endl;
}

// https://msdn.microsoft.com/en-us/library/hh279674.aspx
// unique_ptr

void unique_test()
{
	class Sfx1 {
	public:
		std::string title;
		std::string singer;
	};
	
	std::unique_ptr<Sfx1> sfx1(new Sfx1{ "Title", "Test" });

	std::unique_ptr<Sfx1> sfx2 = std::make_unique<Sfx1>();

	// raw pointer
	std::cout << sfx2.get() << std::endl;

	auto sfx3 = std::make_unique<Sfx1>();

	std::cout << sfx3->title << std::endl;

	// move raw pointer
	std::unique_ptr<Sfx1> sfx4 = std::move(sfx1);				

	//std::cout << "sfx1 = " << sfx1->title << std::endl;		// runtime error
	std::cout << "Sfx4 = " << sfx4->title << std::endl;

	// free memory
	sfx4.reset();												

	//std::cout << "Sfx4 = " << sfx4->title << std::endl;		// runtime error

	std::unique_ptr<Sfx1> t1 = std::make_unique<Sfx1>(Sfx1{ "Smart", "Studio" });

	std::cout << "t1 = " << t1->title << std::endl;				// OK

}

//https://msdn.microsoft.com/en-us/library/hh279669.aspx

void shared_test()
{
	struct Complete {
		int x;
		std::string value;
	};

	std::shared_ptr<Complete> c1(new Complete{ 3, "sms" });

	std::cout << "c1 = " << c1->value << std::endl;

	std::shared_ptr<Complete> c2 = std::make_shared<Complete>(Complete{ 5,"contacts" });

	std::cout << "c2 = " << c2->value << std::endl;								// contacts
	std::cout << "c2.use_count = " << c2.use_count() << std::endl;				// 1

	// initialize via assignment, Increments ref count
	auto c3 = c2;

	std::cout << "c3 = " << c3->value << std::endl;								// contacts
	std::cout << "c2.use_count = " << c2.use_count() << std::endl;				// 2
	std::cout << "c3.use_count = " << c3.use_count() << std::endl;				// 2
	
	// initialize with copy constructor, Increments ref count
	auto c4(c1);

	std::cout << "c4 = " << c4->value << std::endl;								// sms
	std::cout << "c4.ref_count = " << c4.use_count() << std::endl;				// 2

	// Initialize with another shared_ptr. sp1 and sp2
	// swap pointers as well as ref counts.
	c4.swap(c3);

	std::cout << "c4 = " << c4->value << std::endl;								// contacts
	std::cout << "c4.ref_count = " << c4.use_count() << std::endl;				// 2
	std::cout << "c4.raw = " << c4.get() << std::endl;

	std::shared_ptr<Complete> c5(nullptr);

	//std::cout << "c5(nullptr) = " << c5->value << std::endl;					// runtime error

}

// en
// https://msdn.microsoft.com/en-us/library/hh279672.aspx

// ko
// https://blog.naver.com/kirayamato4/221150448366
// http://egloos.zum.com/sweeper/v/3059940

//shared_ptr은 자신이 참조하고 있는 객체(메모리 주소)에 대해 reference counting을 함으로써, 객체의 수명에 직접적으로 관여한다.
//shared_ptr 객체 하나가 소멸되더라도, 동일한 메모리 주소를 참조하고 있는 다른 shared_ptr 객체가 있으면 참조하고 있던 메모리 주소의 객체는 소멸되지 않는다.
//
//하지만, weak_ptr은 shared_ptr을 관리하기 위한 reference count에 포함되지 않는다.
//즉, shared_ptr의 객체만 참조할 뿐, shared_ptr의 reference count를 올리지 않는 것이다.
//
//사실 weak_ptr이 shared_ptr을 참조할 때 shared_ptr의 weak reference count는 증가시킨다.
//객체의 생명 주기에 관여하는 strong reference count를 올리지 않는 것 뿐이다.
//(shared_ptr, weak_ptr 객체를 디버거로 살펴보면 strong / weak refCount가 따로 표시된다)
//(weak reference count는 객체의 소멸에는 전혀 관여하지 않으니 헤깔리지 말도록!)
//위에서 얘기한 것처럼, weak_ptr은 shared_ptr의 참조자라고 표현하는 것이 맞을 듯 하다.
//
//같은 weak_ptr 또는 shared_ptr로부터만 복사 생성 / 대입 연산이 가능하며,
//shared_ptr로만 convert가 가능하다.
//
//따라서, weak_ptr<_Ty>는 _Ty 포인터에 대해 직접 access가 불가능하며,
//(shared_ptr의 get() 메쏘드 같은 녀석이 아예 없다)
//_Ty 포인터에 엑세스를 원하면 lock 메써드를 통해 shared_ptr로 convert 한 뒤, shared_ptr의 get 메쏘드를 사용해야 한다.

void week_test()
{
	struct ContactCount {
		int x;
		std::string value;
	};

	std::shared_ptr<ContactCount> s1 = std::make_shared<ContactCount>(ContactCount{ 5, "contacts" });
	
	// weak ref 1
	std::weak_ptr<ContactCount> w1 = s1;

	{

		std::shared_ptr<ContactCount> s2 = w1.lock();

		if (s2) {

			// weak_ptr<_Ty>의 _Ty 포인터에 엑세스 하려면
			// 이렇게 shared_ptr로 convert하는 방법 밖에 없다

			std::wcout << L"s2.use_count = " << s2.use_count() << std::endl;
		}

		// sp2가 여기에서 소멸, strong RefCount = 1, weak refCount = 1
	}
	std::wcout << L"s1.use_count = " << s1.use_count() << std::endl;

	// ref 0 , delete 
	s1.reset();

	if (w1.expired()) {

		std::wcout << L"shared_ptr expired" << std::endl;		// expired
	}

	auto s3 = w1.lock();

	if (s3) {
		std::wcout << L"s is alive" << std::endl;
	}
	else {
		std::wcout << L"s is dead" << std::endl;			// OK
	}





	// press key
	std::wcout << L"Press any key" << std::endl;
	char ch;
	std::cin.getline(&ch, 1);
}

// http://pacs.tistory.com/entry/%ED%95%AD%EB%AA%A9-13-%EC%9E%90%EC%9B%90-%EA%B4%80%EB%A6%AC%EC%97%90%EB%8A%94-%EA%B0%9D%EC%B2%B4%EA%B0%80-%EA%B7%B8%EB%A7%8C-sharedptr-autoptr
// auto_ptr

void auto_test()
{
	class AutoS {
	public:
		int x;
		std::string v;
	};

	std::auto_ptr<AutoS> a1(new AutoS{ 3, "background" });
	std::auto_ptr<AutoS> a2(a1); // copy a1 , a2에게 자원을 넘겨주고 a2 자신은 null로 바뀜, 그래서 shared_ptr 등장
	
	//std::wcout << L"a1.string = " << a1->v.c_str() << std::endl;	// runtime error
	std::wcout << L"a2.string = " << a2->v.c_str() << std::endl;

	std::shared_ptr<AutoS> s1(new AutoS{ 5, "shared" });
	std::shared_ptr<AutoS> s2(s1);

	std::wcout << L"s1.string = " << s1->v.c_str() << std::endl;
	wcout << L"s2.string = " << s2->v.c_str() << endl;
	
}