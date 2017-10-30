#include "Simulation2D.h"

std::array<Ball, 2> Simulation2D::Step(double time) const
{
	// spring constant function
	auto k_ = [](double x) { return abs(-56686.7*pow(x, 2) + 42828.16*x - 298.511); };

	std::array<Ball, 2> s = s_.back();
	s[0].t_ = s[1].t_ = time;

	// translational motion
	s[0].f_ = s[1].f_ = Cartesian{ 0,0 }; // reset force
	s[0].o_ += s[0].v_ / fps_; // update pos
	s[1].o_ += s[1].v_ / fps_;
	auto del = s[1].o_ - s[0].o_; // vector joining origins of balls
	auto imp = (del.GetPolar().l_ - s[0].r_ - s[1].r_) / 2; // impression on balls,
	// found by taking distance between balls and subtracting each radius and checking signage of resulting value
	s[0].f_ = k_(-imp)*Vector(Polar{ std::min(imp,0.0), del.GetPolar().t_ }); // force exerted by spring
	s[1].f_ = k_(-imp)*Vector(Polar{ std::min(imp,0.0), del.GetPolar().t_ + PI });
	s[0].a_ = s[0].f_ / s[0].m_; // update acceleration
	s[1].a_ = s[1].f_ / s[1].m_;
	s[0].v_ += s[0].a_ / fps_; // update velocity by fps
	s[1].v_ += s[1].a_ / fps_;

	// rotational motion
	s[0].alpha_ = s[1].alpha_ = 0; // reset force
	s[0].theta_ += s[0].omega_ / fps_; // update pos
	s[1].theta_ += s[1].omega_ / fps_;
	// find torque by multiplying radius by frictional force WRT spring force
	double alpha = 2 * PI - del.GetPolar().t_;
	int sign = Spin(s[0], s[1],
		-Vector(Polar{ s[0].v_.GetPolar().l_*sin(alpha + s[0].v_.GetPolar().t_),PI / 2 - alpha }));
	s[0].tau_ = s[0].r_*mu_*k_(-imp)*sign*-std::min(imp, 0.0);
	s[1].tau_ = s[1].r_*mu_*k_(-imp)*-sign*-std::min(imp, 0.0);
	s[0].moment_ = s[0].m_*pow(s[0].r_, 2) * 2 / 5; // moment of inertia for sphere
	s[1].moment_ = s[1].m_*pow(s[1].r_, 2) * 2 / 5;
	s[0].alpha_ = s[0].tau_ / s[0].moment_; // get angular acc from torque
	s[1].alpha_ = s[1].tau_ / s[1].moment_;
	s[0].omega_ += s[0].alpha_ / fps_; // update angular velocity according to fps
	s[1].omega_ += s[1].alpha_ / fps_;

	return s;
}

int Simulation2D::Spin(const Ball &cur, const Ball &other, const Vector &negvel) const
{
	// determine direction of spin based on relative positions of balls
	// and vector
	// assumed that frictional force generally directs opposite the velocity vector
	// returns -1 for CW and 1 for CCW
	double strip = [&](double angle) { // strip angle so that it is within [0, 2PI]
		angle = 10 * PI + angle;
		assert(angle >= 0);
		while (angle > 2 * PI) angle -= 2 * PI;
		return angle;
	}(negvel.GetPolar().t_);
	if (cur.o_.GetCartesian().x_<other.o_.GetCartesian().x_
		&&cur.o_.GetCartesian().y_>other.o_.GetCartesian().y_) // "other" in quadrant III
	{
		if (strip >= PI&&strip <= 3 * PI / 2) return -1;
		if (strip == 2 * PI || (strip >= 0 && strip <= PI / 2)) return 1;
	}
	if (cur.o_.GetCartesian().x_ < other.o_.GetCartesian().x_
		&&cur.o_.GetCartesian().y_ < other.o_.GetCartesian().y_) // "other" in quadrant IV
	{
		if (strip == 0 || (strip >= 3 * PI / 2 && strip <= 2 * PI)) return -1;
		if (strip >= PI / 2 && strip <= PI) return 1;
	}
	if (cur.o_.GetCartesian().x_ > other.o_.GetCartesian().x_
		&&cur.o_.GetCartesian().y_ < other.o_.GetCartesian().y_) // "other" in quadrant I
	{
		if (strip == 2 * PI || (strip >= 0 && strip <= PI / 2)) return -1;
		if (strip >= PI && strip <= 3 * PI / 2) return 1;
	}
	if (cur.o_.GetCartesian().x_ > other.o_.GetCartesian().x_
		&&cur.o_.GetCartesian().y_ > other.o_.GetCartesian().y_) // "other" in quadrant II
	{
		if (strip >= PI / 2 && strip <= PI) return -1;
		if (strip == 0 || (strip >= 3 * PI / 2 && strip <= 2 * PI)) return 1;
	}
}

void Simulation2D::Execute(int t)
{
	for (int i = s_.size(); i <= t*fps_; i++)
		s_.emplace_back(Step(i / fps_));
}

void Simulation2D::ExportCSV(std::ostream &os) const
{
	for (auto &&s : s_)
		os << s[0].t_ << "," 
		<< s[0].o_.GetCartesian().x_ << ","
		<< s[0].o_.GetCartesian().y_ << ","
		<< s[0].theta_ << ","
		<< s[1].o_.GetCartesian().x_ << ","
		<< s[1].o_.GetCartesian().y_ << ","
		<< s[1].theta_ << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Simulation2D &s)
{
	for (auto &&a : s.s_)
		os << a[0] << std::endl << a[1] << std::endl;
	return os;
}
