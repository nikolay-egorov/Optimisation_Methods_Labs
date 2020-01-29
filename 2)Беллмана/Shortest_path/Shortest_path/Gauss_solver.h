#pragma once
#include <algorithm>
#include <utility>
#include <cstdlib>
using namespace std;
class Gauss_solver
{
public:
	int n;
	double **coef, *y, *ans;
	Gauss_solver(int );
	void solve();
	~Gauss_solver();
};

