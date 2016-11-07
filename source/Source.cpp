/*
AdvancedOverloading
(c) 2016
original authors: David I. Schwartz
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial illustrates the application of operator overloading in the form of Traits of a set Class.
*	It also covers the concepts of set, struct, const, predefined macro __FUNCTION__, keyword new, pointer ,and reference.
*/


#include <iostream>  // for cout
#include <set>       // for using set
#include "Thing.h"
#include "GreaterThing.h"
#include "LessThing.h"
typedef unsigned int uint;

void main() {

	// set Class: http://msdn.microsoft.com/en-us/library/e8wh7665.aspx:
	// unique, sorted values (No member appears more than once)
	// see MSDN for more rules

	// ----------------------------------------test the unique elements & the default traits of a set---------------------------------------- //
	cout << "\nTest1" << endl;   // output: Test1
	set<int> s1;                 // initialize a set whose element type is int
	s1.insert(3);                // inserts the element '3' into s1.
	s1.insert(1);                // inserts the element '1' into s1.
	s1.insert(2);                // inserts the element '2' into s1.
	s1.insert(2);                // inserts the element '2' into s1.
	set<int>::iterator itr1;     // declare a iterator type itr1 which can read any element in a set
	cout << "set1 (of ints) contents:" << endl;                                 // output: set1 (of ints) contents:
	for (itr1 = s1.begin(); itr1 != s1.end(); itr1++) cout << (*itr1) << endl;  // print out all the elments in the set from the first to the last
	                                                                            // output: 1
                                                                                //         2
                                                                                //         3
	// ---------------------------------------------------------------------------------------------------------------------------------------- //



	//  -----------------------------test the default order of a set whose elements are class objects in the heap------------------------------ //
	cout << "\n\nTest2" << endl;           // output: Test2
	set<Thing*>* s2 = new set<Thing*>();   // intialize a pointer s2 to template class set whose element type is pointer to Thing type object
	s2->insert(new Thing(3));              // create a Thing object, pass 3 as its constructor argument; insert it to the set
	s2->insert(new Thing(1));              // create a Thing object, pass 1 as its constructor argument; insert it to the set
	s2->insert(new Thing(2));              // create a Thing object, pass 2 as its constructor argument; insert it to the set
	set<Thing*>::iterator itr2;            // declare a iterator type itr2 
	for (itr2 = s2->begin(); itr2 != s2->end(); itr2++)  // make itr2 point to every elments in the s2 from the first to the last
		cout << (*itr2)->getX() << endl;   // print out private member x of Thing object set from the first to last
	                                       // output: 2
										   //         3
										   //         1  (the default order depends on the value of the adress of these three Thing objects)
	s2->insert(new Thing(2));              // Thing objects are NOT their "x" values!
	cout << "set2 (of Things) contents:" << endl;        // output: set2 (of Things) contents:
	for (itr2 = s2->begin(); itr2 != s2->end(); itr2++)  // make itr2 point to every elments in the s2
		cout << (*itr2)->getX() << endl;                 // print out private member x of Thing object set from the first to last
														 // output: 2
														 //         2
														 //         3
														 //         1  (the order depends on the value of the adress of these three Thing objects)
	for (itr2 = s2->begin(); itr2 != s2->end(); itr2++)  // from the beginning to the end
		delete *itr2;                                    // deallocate the memory for the elements in s2
	                                                     // output: 
	                                                     //Thing::~Thing 2
	                                                     //Thing::~Thing 2
		                                                 //Thing::~Thing 3
		                                                 //Thing::~Thing 1
	delete s2;                                           // deallocate the memory for s2
	// ---------------------------------------------------------------------------------------------------------------------------------------- //


	// ------------------------------test the traits using operator overloading/ stack allocated----------------------------------------------- //
	cout << "\n\nTest3" << endl;  // output: Test3
	set<Thing, LessThing> s3;     // initialize a set s3 whose element data type is Thing object and traits are LessThing
	s3.insert(Thing(4));          // create a Thing object; pass 4 to its constructor; insert this object to s3
	                              // output: Thing::Thing
								  //         Thing::~Thing 4
	s3.insert(Thing(6));          // create a Thing object; pass 6 to its constructor; insert this object to s3
								  // output: Thing::Thing
								  //         Thing::~Thing 6
	s3.insert(Thing(5));          // create a Thing object; pass 5 to its constructor; insert this object to s3
								  // output: Thing::Thing
								  //         Thing::~Thing 5
	s3.insert(Thing(5));          // create a Thing object; pass 5 to its constructor; insert this object to s3
								  // output: Thing::Thing
								  //         Thing::~Thing 5
	set<Thing, LessThing>::iterator itr3;      // declare a iterator type itr3
	cout << "set3 (of Thing values) contents (sort by less):" << endl;  // output: set3 (of Thing values) contents (sort by less):
	for (itr3 = s3.begin(); itr3 != s3.end(); itr3++)    // make itr3 point to every element of s3 from the first to the last
		cout << (*itr3).getX() << endl;                  // print out the x in order
	                                                     // output: 4
														 //         5
														 //         6
	// ---------------------------------------------------------------------------------------------------------------------------------------- //
     

	// ------------------------------test the traits using operator overloading/ heap allocated------------------------------------------------ //
	cout << "\n\nTest4" << endl;  // output: Test4
	set<Thing*, GreaterThing>* s4 = new set<Thing*, GreaterThing>(); // intialize a pointer s4 to a set whose element type is pointer to Thing type object and traits type is GreaterThing
	s4->insert(new Thing(8));     // create a Thing object, pass 8 as its constructor argument; insert it to the set
	s4->insert(new Thing(7));     // create a Thing object, pass 7 as its constructor argument; insert it to the set
	s4->insert(new Thing(9));     // create a Thing object, pass 9 as its constructor argument; insert it to the set
	s4->insert(new Thing(8));     // create a Thing object, pass 8 as its constructor argument; insert it to the set
	s4->insert(new Thing(8));     // create a Thing object, pass 8 as its constructor argument; insert it to the set
	set<Thing*, GreaterThing>::iterator itr4;  // declare a iterator type itr4
	cout << "set4 (of Thing pointers) contents (sort by greater):" << endl;  // output: set4 (of Thing pointers) contents (sort by greater):
	for (itr4 = s4->begin(); itr4 != s4->end(); itr4++)
		cout << (*itr4)->getX() << endl;                                     // print out the x of elements in order 
																			 // output: 9
																			 //         8
																			 //         7

	for (itr4 = s4->begin(); itr4 != s4->end(); itr4++)
		delete *itr4;                                                        // deallocate the memory for the set
																			 // output: Thing::~Thing 9
																			 //         Thing::~Thing 8
																			 //         Thing::~Thing 7
	delete s4;                                                               // deallocate the memory for pointer s4
	// ---------------------------------------------------------------------------------------------------------------------------------------- //

	system("pause");

#pragma endregion
}