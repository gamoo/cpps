#include "stdafx.h"
#include <memory>
#include <string>

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
	class Song {
		std::string title;
		std::string singer;
	};
	
	std::unique_ptr<Song> song(new Song{ "Nothing", "Test" });

}