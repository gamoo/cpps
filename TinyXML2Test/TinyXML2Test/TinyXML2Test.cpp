// TinyXML2Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tinyxml2.h"

#include <iostream>

using namespace tinyxml2;

int main()
{
	XMLDocument doc;

	XMLDeclaration* decl = doc.NewDeclaration();

	doc.InsertFirstChild(decl);

	XMLElement* element1 = doc.NewElement("Element1");
	XMLElement* element2 = doc.NewElement("Element2");

	doc.InsertEndChild(element1);

	XMLElement* elementChild1 = doc.NewElement("ElementChild1");

	doc.InsertEndChild(element2);
	doc.InsertAfterChild(element1, elementChild1);

	element1->InsertEndChild(elementChild1);

	for (int n = 0; n < 3; ++n) {
		elementChild1->SetAttribute("attrib", n);
	}
	elementChild1->SetText("Data");

	XMLPrinter printer;
	doc.Print(&printer);
	doc.Print();

	const char* xml = printer.CStr();

	XMLDocument doc2;
	doc2.Parse(xml);

	std::cout << std::endl;
	std::cout << "Parse" << std::endl << std::endl;

	XMLElement* pelement1 = doc.FirstChildElement("Element1");
	XMLElement* pelementChild1 = pelement1->FirstChildElement("ElementChild1");

	std::cout << "Text = " << pelementChild1->GetText() << std::endl << std::endl;
	std::cout << "Attribute = " << pelementChild1->Attribute("attrib") << std::endl << std::endl;
	

	doc2.Print();


    return 0;
}

