#include "Vector.h"

Vector operator*(double d, const Vector &v)
{
	return v*d;
}

std::ostream &operator<<(std::ostream &os, const Vector &v)
{
	os << "(x, y) = (" << v.c_.x_ << ", " << v.c_.y_ << "); (r, theta) = (" 
		<< v.p_.l_ << ", " << v.p_.t_ << ")";
	return os;
}
