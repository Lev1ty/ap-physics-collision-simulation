#include "Ball.h"

std::ostream &operator<<(std::ostream &os, const Ball &b)
{
	os << Circle(b) << "Mass: " << b.m_ << std::endl << "Velocity: " << b.v_ << std::endl
		<< "Acceleration: " << b.a_ << std::endl << "Force: " << b.f_ << std::endl
		<< "Angular displacement: " << b.theta_ << std::endl << "Angular Velocity: " << b.omega_ << std::endl
		<< "Angular acceleration: " << b.alpha_ << std::endl << "Moment of Inertia: " << b.moment_ << std::endl
		<< "Torque: " << b.tau_ << std::endl;
	return os;
}
