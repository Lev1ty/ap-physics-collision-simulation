#define _CRT_SECURE_NO_WARNINGS // VC++ exclusive

#include "Simulation2D.h"

int main()
{
	std::freopen("Results.csv", "w", stdout); // open file for output and attach 
	// to standard out, which is why we use error out for console instructions
	std::array<Ball, 2> b; // initial state

	// RECEIVE INPUT AND SET INITIAL CONDITIONS
	std::cerr << "Enter initial parameters (vectors in cartesian form delimited by space)" << std::endl;

	b[0].a_ = Cartesian{ 0,0 };
	std::cerr << "ball 0 mass (in kilograms): ";
	double b0m;
	std::cin >> b0m;
	b[0].m_ = b0m;
	b[0].f_ = Cartesian{ 0,0 };
	std::cerr << "ball 0 radius (in meters): ";
	double b0r;
	std::cin >> b0r;
	b[0].r_ = b0r;
	std::cerr << "ball 0 origin (in meters): ";
	double b0sx, b0sy;
	std::cin >> b0sx >> b0sy;
	b[0].o_ = Cartesian{ b0sx,b0sy };
	std::cerr << "ball 0 translational velocity (in meters per second): ";
	double b0vx, b0vy;
	std::cin >> b0vx >> b0vy;
	b[0].v_ = Cartesian{ b0vx,b0vy };
	std::cerr << "ball 0 rotational displacement (in radians): ";
	double b0t;
	std::cin >> b0t;
	b[0].theta_ = b0t;
	std::cerr << "ball 0 rotational velocity (in radians per second): ";
	double b0o;
	std::cin >> b0o;
	b[0].omega_ = b0o;
	b[0].moment_ = 0;
	b[0].alpha_ = 0;
	b[0].tau_ = 0;

	b[1].a_ = Cartesian{ 0,0 };
	std::cerr << "ball 1 mass (in kilograms): ";
	double b1m;
	std::cin >> b1m;
	b[1].m_ = b1m;
	b[1].f_ = Cartesian{ 0,0 };
	std::cerr << "ball 1 radius (in meters): ";
	double b1r;
	std::cin >> b1r;
	b[1].r_ = b1r;
	std::cerr << "ball 1 origin (in meters): ";
	double b1sx, b1sy;
	std::cin >> b1sx >> b1sy;
	b[1].o_ = Cartesian{ b1sx,b1sy };
	std::cerr << "ball 1 translational velocity (in meters per second): ";
	double b1vx, b1vy;
	std::cin >> b1vx >> b1vy;
	b[1].v_ = Cartesian{ b1vx,b1vy };
	std::cerr << "ball 1 rotational displacement (in radians): ";
	double b1t;
	std::cin >> b1t;
	b[1].theta_ = b1t;
	std::cerr << "ball 1 rotational velocity (in radians per second): ";
	double b1o;
	std::cin >> b1o;
	b[1].omega_ = b1o;
	b[1].moment_ = 0;
	b[1].alpha_ = 0;
	b[1].tau_ = 0;

	std::cerr << "simulation parameters: shared by both balls" << std::endl;
	std::cerr << "static friction coefficient: ";
	double mu;
	std::cin >> mu;
	std::cerr << "frequency of simulation (Hertz): ";
	int freq;
	std::cin >> freq;
	Simulation2D s0 = { {b},freq,mu };

	std::cerr << "duration of simulation (seconds): ";
	int t;
	std::cin >> t;
	s0.Execute(t);
	
	s0.ExportCSV(std::cout); // export

	//// TESTINGS PARAMETERS
	//b[0].a_ = b[1].a_ = b[0].f_ = b[1].f_ = Cartesian{ 0,0 };
	//b[0].m_ = 1; b[1].m_ = 1;
	//b[0].o_ = Cartesian{ 0,-.5 }; b[1].o_ = Cartesian{ 10,0 };
	//b[0].r_ = 1; b[1].r_ = 1;
	//b[0].v_ = Cartesian{ 1,0 }; b[1].v_ = Cartesian{ 0,0 };
	//b[0].alpha_ = b[1].alpha_ = b[0].omega_ = b[1].omega_ = b[0].theta_ = b[1].theta_
	//	= b[0].tau_ = b[1].tau_ = b[0].moment_ = b[1].moment_ = 0;
	//Simulation2D s0 = { {b},50,.7 };
	//s0.Execute(20);
	////std::cerr << s0 << std::endl;
	//s0.ExportCSV(std::cout);
}