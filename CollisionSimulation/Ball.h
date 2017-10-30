#pragma once

#include "Circle.h"

struct Ball : public Circle
{
	Vector v_, a_, f_; // velocity acc and force
	double m_, theta_, omega_, alpha_, tau_, moment_, t_; // mass and angular parameters
	friend std::ostream &operator<<(std::ostream &, const Ball &); // formatted output
};