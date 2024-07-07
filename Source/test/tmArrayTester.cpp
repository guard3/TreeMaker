/*******************************************************************************
File:         tmArrayTester.cpp
Project:      TreeMaker 5.x
Purpose:      Test application for the tmArray container classes
Author:       Robert J. Lang
Modified by:  Konstantinos Bolosis
Created:      2005-09-27
Copyright:    ©2005 Robert J. Lang. All Rights Reserved.
*******************************************************************************/

// Standard libraries
#include <iostream>

// My libraries
#include "tmArray.h"          // my general-purposes container class
#include "tmArrayIterator.h"  // my redefinition of PowerPlant tmArrayIterator

// stream output for a list (helps in testing)
template <class T>
std::ostream& operator<<(std::ostream& os, const tmArray<T>& aList) {
	os << '<';
	if (auto it = aList.begin(); it != aList.end()) {
		os << *it;
		while (++it != aList.end())
			os << ", " << *it;
	}
	return os << '>';
}

// Main test program
int main() {
	std::cout << "Hello World.\n";

	const char *a = "A", *b = "B", *c = "C", *d = "D", *e = "E", *f = "F", *g = "G", *h = "H";

	tmArray<const char*> alist;

	alist.push_back(b);
	alist.push_back(c);
	alist.push_front(a);
  
	std::cout
		<< "alist is " << alist << '\n'
		<< "size() is " << alist.size() << '\n'
		<< "front = " << alist.front() << '\n'
		<< "NthItem(2) = " << *alist.NthItem(2) << '\n'
		<< "back = " << alist.back() << "\n\n";

	alist.union_with(a);
	alist.union_with(d);
	std::cout << "After union_with(a, d) the list is " << alist << '\n';

	alist.erase_remove(d);
	std::cout << "After erase_remove(d) the list is " << alist << '\n';


	alist.erase_remove(b);
	std::cout
		<< "After erase_remove(b) the list is " << alist << '\n'
		<< "2nd item is now " << alist.NthItem(2) << '\n'
		<< "size() is now " << alist.size() << "\n\n"
		<< std::boolalpha
		<< "list contains a? " << alist.contains(a) << '\n'
		<< "list contains b? " << alist.contains(b) << '\n'
		<< "list contains c? " << alist.contains(c) << "\n\n";

	alist.ReplaceItemAt(1, d);
	std::cout
		<< "After ReplaceItemAt(1, d) the list is " << alist << '\n'
		<< "1st item is now " << alist.NthItem(1) << '\n'
		<< "Index of 'd' is " << alist.GetIndex(d) << '\n'
		<< "Offset of 'd' is " << alist.GetOffset(d) << '\n'
		<< "alist[0] = " << alist[0] << "\n\n";

	alist.push_back(e);
	std::cout << "After push_back(e) the list is " << alist << '\n';

	alist.replace_with(d, a);
	std::cout << "After replace_with(d, a) the list is " << alist << '\n';

	// tmArrayIterator/tmArrayIterator test
	tmArrayIterator<const char*> i(alist);
	const char* dp;
	std::cout << "Forward iterator test.\n";
	while (i.Next(&dp))
		std::cout << "an element is " << dp << '\n';
	std::cout << "Backward iterator test.\n";
	i.ResetTo(tmArray_END);
	while (i.Previous(&dp))
		std::cout << "an element is " << dp << '\n';

	// operator[] returns an lvalue
	std::cout << '\n';
	alist[0] = f;
	std::cout << "Set alist[0] = f; alist = " << alist << "\n\n";

	// combinational routines
	tmArray<const char*> blist;
	blist.push_back(f);
	blist.push_back(g);
	blist.push_back(h);
	std::cout
		<< "alist = " << alist << '\n'
		<< "blist = " << blist << '\n';
	blist.intersect_with(alist);
	std::cout << "blist.intersect_with(alist) = " << blist << '\n';
	blist.union_with(alist);
	std::cout << "blist.union_with(alist) = " << blist << '\n';

	// intersection routines
	tmArray<int> clist;
	clist.push_back(1);
	clist.push_back(2);
	clist.push_back(3);
	clist.push_back(4);
	tmArray<int> dlist;
	dlist.push_back(5);
	dlist.push_back(4);
	std::cout
		<< "clist = " << clist << '\n'
		<< "dlist = " << dlist << '\n'
		<< "clist.intersects(dlist) = " << clist.intersects(dlist) << '\n'
		<< "dlist.intersects(clist) = " << dlist.intersects(clist) << '\n';
}
