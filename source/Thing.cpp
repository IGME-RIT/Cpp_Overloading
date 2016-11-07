#pragma once
#include "Thing.h"

Thing::Thing(int i) : x(i) {}           // define constructor

Thing::Thing(const Thing& t) {          // define another constructor
	x = t.x;                            // x gets the value of Thing t's private member
	cout << __FUNCTION__ << endl;       // printout the function name (undecorated)
}

Thing& Thing::operator=(const Thing& t) {// define operator overloading function
	x = t.x;                             
	cout << __FUNCTION__ << endl;        
	return *this;                        // return to the dereference of this
}

Thing::~Thing() {                              // define destructor
	cout << __FUNCTION__ << " " << x << endl;  // print out the funtion name and x
}

int Thing::getX() const { return x; }          // define function getX which returns to private member x
