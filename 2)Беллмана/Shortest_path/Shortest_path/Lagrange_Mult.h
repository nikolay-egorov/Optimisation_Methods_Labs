#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#include<cstdio>
#include<iostream>
#include <vector>
using namespace std;
class Lagrange_Mult
{
public:

	Lagrange_Mult();
	~Lagrange_Mult();

	double func(double x, double y) {
		return pow(M_E,x*y);
	}

	double f_dx(double x, double y)
	{
		return y*pow(M_E, x*y);
	}


	double f_dy(double x, double y)
	{
		return x * pow(M_E, x*y);
	}
	double f_dx_full(double x, double y)
	{
		return 3*x*x + y * pow(M_E, x*y);
	}

	double g(double x, double y) {
		return x*x*x + y * y*y - 16;
	}

	 

};

