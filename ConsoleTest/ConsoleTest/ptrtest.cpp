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

//shared_ptr�� �ڽ��� �����ϰ� �ִ� ��ü(�޸� �ּ�)�� ���� reference counting�� �����ν�, ��ü�� ���� ���������� �����Ѵ�.
//shared_ptr ��ü �ϳ��� �Ҹ�Ǵ���, ������ �޸� �ּҸ� �����ϰ� �ִ� �ٸ� shared_ptr ��ü�� ������ �����ϰ� �ִ� �޸� �ּ��� ��ü�� �Ҹ���� �ʴ´�.
//
//������, weak_ptr�� shared_ptr�� �����ϱ� ���� reference count�� ���Ե��� �ʴ´�.
//��, shared_ptr�� ��ü�� ������ ��, shared_ptr�� reference count�� �ø��� �ʴ� ���̴�.
//
//��� weak_ptr�� shared_ptr�� ������ �� shared_ptr�� weak reference count�� ������Ų��.
//��ü�� ���� �ֱ⿡ �����ϴ� strong reference count�� �ø��� �ʴ� �� ���̴�.
//(shared_ptr, weak_ptr ��ü�� ����ŷ� ���캸�� strong / weak refCount�� ���� ǥ�õȴ�)
//(weak reference count�� ��ü�� �Ҹ꿡�� ���� �������� ������ ����� ������!)
//������ ����� ��ó��, weak_ptr�� shared_ptr�� �����ڶ�� ǥ���ϴ� ���� ���� �� �ϴ�.
//
//���� weak_ptr �Ǵ� shared_ptr�κ��͸� ���� ���� / ���� ������ �����ϸ�,
//shared_ptr�θ� convert�� �����ϴ�.
//
//����, weak_ptr<_Ty>�� _Ty �����Ϳ� ���� ���� access�� �Ұ����ϸ�,
//(shared_ptr�� get() �޽�� ���� �༮�� �ƿ� ����)
//_Ty �����Ϳ� �������� ���ϸ� lock �޽�带 ���� shared_ptr�� convert �� ��, shared_ptr�� get �޽�带 ����ؾ� �Ѵ�.

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

			// weak_ptr<_Ty>�� _Ty �����Ϳ� ������ �Ϸ���
			// �̷��� shared_ptr�� convert�ϴ� ��� �ۿ� ����

			std::wcout << L"s2.use_count = " << s2.use_count() << std::endl;
		}

		// sp2�� ���⿡�� �Ҹ�, strong RefCount = 1, weak refCount = 1
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
	std::auto_ptr<AutoS> a2(a1); // copy a1 , a2���� �ڿ��� �Ѱ��ְ� a2 �ڽ��� null�� �ٲ�, �׷��� shared_ptr ����
	
	//std::wcout << L"a1.string = " << a1->v.c_str() << std::endl;	// runtime error
	std::wcout << L"a2.string = " << a2->v.c_str() << std::endl;

	std::shared_ptr<AutoS> s1(new AutoS{ 5, "shared" });
	std::shared_ptr<AutoS> s2(s1);

	std::wcout << L"s1.string = " << s1->v.c_str() << std::endl;
	wcout << L"s2.string = " << s2->v.c_str() << endl;
	
}