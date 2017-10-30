#include "Circle.h"

std::ostream &operator<<(std::ostream &os, const Circle &c)
{
	os << "Origin: " << c.o_ << std::endl << "Radius: " << c.r_ << std::endl;
	return os;
}
