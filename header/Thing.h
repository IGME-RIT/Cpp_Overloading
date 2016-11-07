#pragma once
#include <iostream>
using namespace std;

class Thing {       // declare class Thing
public:             
	Thing(int i);                       // declare constructor
	Thing(const Thing& t);              // declare overloading constructor
	Thing& operator=(const Thing& t);   // declare operator overloading funtion
	~Thing();                           // declare destructor
	int getX() const;                   // declare function member
private:
	int x;                              // declare private member x
};
