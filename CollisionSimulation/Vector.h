#pragma once

#include <cmath>
#include <iostream>

struct Cartesian { double x_, y_; };

struct Polar { double l_, t_; };

// contains basic operators and formatted output functions for Vector
// polar form updates when cartesian form is updated
class Vector
{
public:
	Vector() {}
	Vector(Cartesian c) { SetCartesian(c); }
	Vector(Polar p) { SetPolar(p); }
	Cartesian GetCartesian() const { return c_; }
	Polar GetPolar() const { return p_; }
	void SetCartesian(const Cartesian &c) { c_ = c; p_ = ToPolar(); }
	void SetPolar(const Polar &p) { p_ = p; c_ = ToCartesian(); }
	Vector operator-() const { return Cartesian{ -c_.x_,-c_.y_ }; }
	Vector operator+(const Vector &v) const {
		return Cartesian{ c_.x_ + v.GetCartesian().x_, c_.y_ + v.GetCartesian().y_ };
	}
	Vector operator-(const Vector &v) const { return *this + (-v); }
	Vector operator*(double d) const { return Cartesian{ c_.x_*d,c_.y_*d }; }
	friend Vector operator*(double d, const Vector &v);
	Vector operator/(double d) const { return Cartesian{ c_.x_ / d,c_.y_ / d }; }
	Vector &operator+=(const Vector &v) { *this = *this + v; return *this; }
	Vector &operator-=(const Vector &v) { return *this += (-v); }
	Vector &operator*=(double d) { *this = *this*d; return *this; }
	Vector &operator/=(double d) { *this = *this / d; return *this; }
	friend std::ostream &operator<<(std::ostream &, const Vector &);
private:
	Cartesian c_;
	Polar p_;
	Cartesian ToCartesian() const { return { cos(p_.t_)*p_.l_, sin(p_.t_)*p_.l_ }; }
	Polar ToPolar() const { return { sqrt(pow(c_.x_,2) + pow(c_.y_,2)),atan2(c_.y_,c_.x_) }; }
};