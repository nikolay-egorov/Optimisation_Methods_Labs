#include<cmath>
#include<cstdio>
#include<iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#define _USE_MATH_DEFINES
#define NMAX 2000

using namespace std;

template<class  T>
T min(T a, T b) {
	return	a < b ? a : b;
}

double func(double x, double y) {
	return (y - x * x)*(y - x * x) + (1 - x)*(1 - x);
}

double f_dx(double x, double y)
{
	return 4 * x*x*x - 4*x*y +2*x -2; 
}

 
double f_dy(double x, double y)
{
	return 2* (y - x*x);
}


double f_c_dx(double x, double y,double h) {
	return (func(x + h, y) - func(x-h, y)) / (2*h);
}

double f_c_dy(double x, double y,double h) {
	return (func(x, y+h) - func(x, y-h)) / (2*h);
}


double g(double x, double y, double alpha)
{
//	return func(x - alpha * f_dx(x, y), y - alpha * f_dy(x, y));
	return func(x + alpha * f_dx(x, y), y + alpha * f_dy(x, y));
}


double norma(double x, double y)
{
	return sqrt(x * x + y * y);
}

 
double Dihotomia(double a0, double b0, double epsilon, double x, double y)
{
	 
	int k=1;
	//ќтклонени от середины отрезка влево, вправо
	double lk, mk;
	 
	double delta = 0.5*epsilon;
 
	double ak = a0, bk = b0;
	double f1, f2;
	 
	do
	{
		 
		lk = (ak + bk - delta) / 2;
		mk = (ak + bk + delta) / 2;
		f1 = g(x, y, lk), f2 = g(x, y, mk);
		k++;
		//ѕровер€ем в какую часть попадает точка минимума слева от разбиени€ или справа и выбираем соответствующую точку
	//	if (g(x, y, lk) <= g(x, y, mk))
		if(f1<=f2)
		{
			bk = mk;
			mk = lk;
			f2 = f1;
		}
		else
		{ 
			ak = lk;
			lk = mk;
			f1 = f2;
		}
	} while ((bk - ak) >= epsilon);

	 
	return (ak + bk) / 2;
}

vector<double> Dihotomia_comb(double a0, double b0, double epsilon, double &x, double &y)
{

	int k = 1,j;
	//ќтклонени от середины отрезка влево, вправо
	double lk, mk;
	vector<double> tmp, x0;   x0.emplace_back(x), x0.emplace_back(y);
	tmp.emplace_back(x), tmp.emplace_back(y);
	vector<double> GF; GF.emplace_back(f_dx(x, y)), GF.emplace_back(f_dy(x, y));
	double delta = 0.5*epsilon;

	double ak = a0, bk = b0;
	double f1, f2,x_temp,y_temp;
	lk = (ak + bk - delta) / 2;
	mk = (ak + bk + delta) / 2;
	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + lk * GF[j];
	f1 = func(tmp[0], tmp[1]);
	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + mk * GF[j];
	f2 = func(tmp[0], tmp[1]);

	for (int k = 1; k < 100; k++) {

		//ѕровер€ем в какую часть попадает точка минимума слева от разбиени€ или справа и выбираем соответствующую точку
		//	if (func(x,y) <= g(x, y, mk))
		if (f1 <= f2)
		{
			bk = mk;
			mk = lk;
			f2 = f1;
			lk = (ak + bk - delta) / 2;
			for (j = 0; j<x0.size(); j++)
				tmp[j] = x0[j] + lk * GF[j];
			f1 = func(tmp[0], tmp[1]);
		}
		else
		{
			ak = lk;
			lk = mk;
			f1 = f2;
			mk = (ak + bk + delta) / 2;
			for (j = 0; j<x0.size(); j++)
				tmp[j] = x0[j] + mk * GF[j];
			f2 = func(tmp[0], tmp[1]);
		}
		if (fabs(bk - ak) <= epsilon)
			break;


	}
	double c = (ak + bk) / 2;
	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + lk * GF[j];
	f1 = func(tmp[0], tmp[1]);
	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + mk * GF[j];
	f2 = func(tmp[0], tmp[1]);
 
	if (f1 <= f2) {
		for (j = 0; j<x0.size(); j++)
			tmp[j] = x0[j] + lk * GF[j];
		 
	}
	else {
		for (j = 0; j<x0.size(); j++)
			tmp[j] = x0[j] + mk * GF[j];
	 
 

	}
	x = tmp[0], y = tmp[1];
	return tmp;
}


double G_sect(double a, double b, double epsilon, double x, double y) {
	int k = 1;
 
	double lk, mk;

	double delta = 0.5*epsilon;

	//ќтрезок локализации минимума
	double ak = a, bk = b, gRatio = 1.8835;

	int O= log(fabs((b - a)) / epsilon) / log(gRatio) + 1;

	for(int i=1;i<O;i++)
	{
		lk = bk - (bk - ak)*gRatio - delta;
	 
	 	mk = ak + (bk - ak)*gRatio + delta;

		if (g(x, y, lk) <= g(x, y, mk))
			bk = lk;
		else
			ak = mk;
	}
	return (ak + bk) / 2;
}

vector<double> G_sect_combo(double a, double b, double epsilon, double &x, double &y,bool analytic_diver) {
	int k = 1;

	double lk, mk;

	//ќтрезок локализации минимума
//	double ak = a, bk = b;
	double x_temp, y_temp, f1, f2;

	
	vector<double> tmp, x0;   x0.emplace_back(x), x0.emplace_back(y);
	tmp.emplace_back(x), tmp.emplace_back(y);
//	vector<double> GF; GF.emplace_back(f_dx(x, y)), GF.emplace_back(f_dy(x, y));
	vector<double> GF; 
	if (analytic_diver) {
		GF.emplace_back(f_c_dx(x, y, epsilon)); GF.emplace_back(f_c_dy(x, y, epsilon));
	}
	else
		GF.emplace_back(f_dx(x, y)), GF.emplace_back(f_dy(x, y));
	const double section1 = 0.38196601125;
	const double section2 = 0.61803398;
	int i, j;

	lk = a + section1 * (b - a);
	mk = a + section2 * (b - a);

	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + lk * GF[j];
	f1 = func(tmp[0], tmp[1]);
	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + mk * GF[j];
	f2 = func(tmp[0], tmp[1]);


	for (int k = 1; k < 100; k++) {

		//ѕровер€ем в какую часть попадает точка минимума слева от разбиени€ или справа и выбираем соответствующую точку
		if (f1 <= f2)
		{
			b = mk;
			mk = lk;
			f2 = f1;
			lk = a + section1 * (b - a);
			for (j = 0; j<x0.size(); j++)
				tmp[j] = x0[j] + lk * GF[j];
			f1 = func(tmp[0], tmp[1]);
		}
		else
		{
			a = lk;
			lk = mk;
			f1 = f2;
			mk = a + section2 * (b - a);
			for (j = 0; j<x0.size(); j++)
				tmp[j] = x0[j] + mk * GF[j];
			f2 = func(tmp[0], tmp[1]);
		}
		 


	}

	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + lk * GF[j];
	f1 = func(tmp[0], tmp[1]);
	for (j = 0; j<x0.size(); j++)
		tmp[j] = x0[j] + mk * GF[j];
	f2 = func(tmp[0], tmp[1]);

	if (f1 <= f2) {
		for (j = 0; j<x0.size(); j++)
			tmp[j] = x0[j] + lk * GF[j];

	}
	else {
		for (j = 0; j<x0.size(); j++)
			tmp[j] = x0[j] + mk * GF[j];


	}
	x = tmp[0], y = tmp[1];

	return tmp;

}
 
double Gradient_move(int bx, int by, double epsilon,double a,double b)
{
	double x[3];
	double y[3];
//	double alpha[NMAX];
	double alpha;
	int k;
	bool acc_flag = false,constr=true;
	 
	x[0] = bx;
	y[0] = by;
	double left=a, right=b;
	/*double lt,h = epsilon;
	for ( lt = a; func(lt, lt) > func(lt +h, lt +h); lt += h,h*=2) {
		 
	} 
	 
	 cout << lt << endl; */




	std::cout << "Results:"
		<< "\n" << "x(" << 0 << "): (" << x[0] << ", " << y[0] << ")" << endl;


	for (k = 0;k<1000 ; k++)
	{
		//Ќаходим alpha_k как минимум функции g на отрезке -10000,100000
	/*	if (!constr) {
			alpha = 0.5;
		}
		else {
			if (acc_flag)
				alpha = Dihotomia(left, right, epsilon, x[0], y[0]);
			else
				alpha = G_ratio(left, right, epsilon, x[0], y[0]);
		*/ 
		alpha = Dihotomia(left, right, epsilon, x[0], y[0]);
		//¬ычисл€ем u[k]
		x[1] = x[0] - alpha * f_dx(x[0], y[0]);
		y[1] = y[0] - alpha * f_dy(x[0], y[0]);
		
 
		cout << "x(" << k + 1 << "): " << "(" << x[1] << ", " << y[1] << ")" << "\n"
			<< "f(" << x[1] << ", " << y[1] << ") = " << func(x[1], y[1]) << endl;

		 
		if (norma(x[1] - x[0], y[1] - y[0]) < 2) 
			acc_flag = true;
	 
		if(fabs(func(x[1], y[1])-func(x[0], y[0])) <  epsilon)
		{
		//	if(acc_flag)
			break;
		}

		 x[0] = x[1]; y[0] = y[1];
 
		
	}

	cout << "Min is (epsilon=" << epsilon << ")" << "\n"
		<< "f(" << x[1] << ", " << y[1] << ") = " << func(x[1], y[1]) << "\nIters: " << k << endl;

	 
	return func(x[1], y[1]);
}



int main()

{
	int iters;
	double x= 53, y=33, eps=0.0001;
//	Gradient_move(x, y, eps,-10000,10000);
	vector <double> ans; ans.push_back(x), ans.push_back(y);
	vector<double> old_x; old_x.emplace_back(x); old_x.emplace_back(y);
	 
	bool analytic_diver =1 ;
	freopen("out_1.txt", "w", stdout);
	std::cout.precision(6);
	cout << fixed; std::cout.precision(8);
	cout << "Default derivative mode\n\n";
	srand(time(0));

	for (eps = 0.01; eps > 0.0000001; eps /= 10) {
		
		x = rand() % 150-10;
		y = rand() % 150-10;
		cout << "Starting point: " << x << ' ' << y << endl;
		for (iters = 1; iters < NMAX; iters++) {
			old_x[0] = ans[0], old_x[1] = ans[1];
			//	ans= Dihotomia_comb(1000, -1000, eps, x, y);
			ans = G_sect_combo(-50, 100, eps, x, y, analytic_diver);
			if (fabs(func(ans[0], ans[1]) - func(old_x[0], old_x[1])) <= eps) {
				break;
			}

		}
		cout << "Eps is " << eps << "\n";
		cout << "Value: " << func(ans[0], ans[1]) << endl;
		cout << "Point: ";
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i] << ' ';
		cout << "Iters: " << iters << endl;

	}
	//x = rand() % 150;
	//y = rand() % 150;
	//cout << "Starting point: " << x << ' ' << y << endl;
	//for (iters = 1; iters < NMAX; iters++) {
	//	old_x[0] = ans[0], old_x[1] = ans[1];
	//	//	ans= Dihotomia_comb(1000, -1000, eps, x, y);
	//	ans = G_sect_combo(-50, 100, eps, x, y, analytic_diver);
	//	if (fabs(func(ans[0], ans[1]) - func(old_x[0], old_x[1])) <= eps) {
	//		break;
	//	}

	//}
	//cout << "Eps is " << eps << "\n";
	//cout << "Value: " << func(ans[0], ans[1]) << endl;
	//cout << "Point: ";
	//for (int i = 0; i < ans.size(); i++)
	//	cout << ans[i] << ' ';
	//cout << "Iters: " << iters << endl;

	return 0;
}