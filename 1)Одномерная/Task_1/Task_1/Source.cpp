#include <iostream>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>
using namespace std;

double func(double x) {
	return sin(x);
}
 
class Fibb {
public:
	unordered_map<int, long> cache;
	long count(int n) {
		if (n < 2) {
			return n;
		}
		if (cache.find(n) != cache.end()) {
			unordered_map<int, long>::const_iterator got = cache.find(n);
			return got->second;
		}
		else {
			int res = count(n - 1) + count(n - 2);
			cache.insert({ n,res });
			return res;
		}
	}
	long get(int n) {
		if (cache.find(n) != cache.end()) {
			unordered_map<int, long>::const_iterator got = cache.find(n);
			return got->second;
		}
		else return count(n);
	}


};


double Fibb_method(double a, double b, double e) {
	Fibb f;
	int i = 1;
 
	while (fabs(a - b) / e > f.get(i)) {
		f.count(++i);
	 
	}
	double l = a + f.get(i - 2) * (b - a) / f.get(i),
		m = a + f.get(i - 1) * (b - a) / f.get(i);

	for (int k = i - 1; k >= 2; k--) {
		if (func(l)<func(m))
		{
			b = m; m = l;  
			l = a + f.get(k - 2) * (b - a) / f.get(k);
		}
		else
		{
			a = l; l = m;  
			m = a + f.get(k - 1) * (b - a) / f.get(k);
		}

	}
	cout << "Number of iter: " << i  << "\n";
	return (a + b) /2;
}

double lazy(double a, double b, double e,int n) {
  
	size_t iter = 1;
	double step = e/100, min=b,x0=a;

	while (func(x0) > func(x0 + step)) {
		if (func(x0) > func(x0 + step)) {
			x0 += step;
			step = step;
		}
		else {
			x0 -= step;
			step = -step;
		}
		++iter;
	}
	cout << "Number of iter: " << iter << "\n";
	
	return x0;
}

double G_way(double a, double b,double eps) {

	const double GS = 1.6335;
	double m1,m2;
	size_t iter = 1;
	int O = log((b - a) / eps) / log(GS)+1;
 
	for (int i= 0; i < O; i++) {
		m1 = b - (b - a)*GS;
		m2 = a + (b - a)*GS;
		if (func(m1) < func(m2)) {
			b = m1;
		}
		else {
			a = m2;
		}
		++iter;
	}
	cout << "Number of iter: " << iter << "\n";
	return b;
}
int main() {

	double a= M_PI_2, b=-M_PI_2,c ;
	const double e = 0.0001;
	//lazy
	cout << func(lazy(a, b, e, 100)) << "\n";
	
	size_t iter = 0;
	//diho
	while (fabs(a - b) > e)
	{
		c= (a + b) / 2;
		if (func(c- e/10) < func(c+ e/10))
		{
			a = c + e / 10;
			 
		}
		else b = c - e / 10;
		++iter;
		 
	}
	cout << "Number of iter: " << iter << "\n";
	cout << func(c) << "\n";
	
	//golden divide
	cout << func(G_way(a, b,e)) << endl;

	//Fibbo
	Fibb F;
	cout << func(Fibb_method(a, b, 0.0001)) << "\n";

	return 0;
}