#pragma once

#include <algorithm>
#include <array>
#include <vector>
#include <cassert>

#include "Ball.h"

const double PI = atan(1) * 4;

struct Simulation2D
{
	std::vector<std::array<Ball, 2>> s_; // stores states of pair of balls over time
	double fps_, mu_; // frequency (frames per second), static fric coefficient
	std::array<Ball, 2> Step(double) const; // generates values based on previous step
	void Execute(int); // main loop for execution
	friend std::ostream &operator<<(std::ostream &, const Simulation2D &); // formatted print for debugging
	void ExportCSV(std::ostream &) const; // export data to csv
private:
	int Spin(const Ball &, const Ball &, const Vector &) const; // calculate direction of spin (CW or CCW)
};