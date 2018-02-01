#include "stdafx.h"

// https://mbevin.wordpress.com/2012/11/16/uniform-initialization/

void clst1()
{
	class SfxClassName {
	public:
		std::string name;
		std::string description;
		int index;
	};

	class SfxClassIndex {
	public:
		int index;
		double value;
	};

	std::string t = "test";

	SfxClassName scn;

	// uniform initialization
	SfxClassName scn2 = { "contacts", "read_count", 1 };
	SfxClassName scn5[] = { { "contacts", "read_count", 1 },{ "contacts", "read_count", 1 } };
	
	SfxClassIndex idx { 3, 5.0 };
	
	class SfxBasic {
		// default is private
	public:
		int basic;
	};

	SfxBasic bt;

	bt.basic;

	struct SfxStruct {
		// default is public
		int basic;
	};

	SfxStruct st;

	st.basic;

	

}