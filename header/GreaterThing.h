#pragma once
#include "Thing.h"

struct GreaterThing {  // define struct GreaterThing
	bool operator()(const Thing* lhs, const Thing* rhs) const {  
		
		return lhs->getX() > rhs->getX(); // compare private member x of Thing objects.
										  // If x's value on the left is greater than that on the right side, return true; otherwise return false

	}
};