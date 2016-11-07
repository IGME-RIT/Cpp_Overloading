#pragma once
#include "Thing.h"

struct LessThing {  // define struct LessThing
	bool operator()(const Thing& lhs, const Thing& rhs) const {  // operator '()' overloading

		return lhs.getX() < rhs.getX();                          // compare private member x of Thing objects. 
		                                                         // If x's value on the left is less than that on the right side, return true; otherwise return false.
	}
};