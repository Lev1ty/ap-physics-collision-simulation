#pragma once

#include "Vector.h"

struct Circle
{
	double r_; // radius
	Vector o_; // origin
	friend std::ostream &operator<<(std::ostream &, const Circle &); // formatted output
};