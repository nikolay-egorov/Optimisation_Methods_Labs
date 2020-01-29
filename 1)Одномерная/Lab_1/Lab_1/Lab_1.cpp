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
double diho(double a, double b, double e) {
	double c;
	size_t iter = 1;
	cout<<"Dihotomy method\n"<< "Starting with: [ " << a << " ;" << b << " ]\n----------------------------------------------------------\n"<< " Iter\t| (a+b)/2\t| F((a+b)/2)\t|     a \t|     b \t|  a/b   |\n"<< "----------------------------------------------------------\n";


	do 
	{
		c = (a + b) / 2;
	//	cout << iter << "\t|  " << c << "\t|  " << func(c) << "\t|  " << a << "\t|  " << b << "\t|  "<<fabs(a/b)<<"  \n";

		
		if (func(c - e / 10) < func(c + e / 10))
		{
			a = c + e / 10;

		}
		else b = c - e / 10;

	 	cout << iter << "\t|  " << c << "\t|  " << func(c) << "\t|  " << a << "\t|  " << b << "\t|  " << fabs(a / b) << "  \n";
		
 
	 	++iter;
	//	iter += 2;

	} while (fabs(func(a) - func(b)) > e);
 	cout << "Number of iters: " << iter-1 << "\n";
	return c;
}

double Fibb_method(double a, double b, double e) {
	Fibb f;
	int i = 1,calls=0;
 
	while (fabs(a - b) / e > f.get(i)) {
		f.count(i++);

	}
 	cout << "Fibbonachi method\n" << "Starting with: [ " << a << " ;" << b << " ]\n----------------------------------------------------------\n" << " Iter\t| (a+b)/2\t| F((a+b)/2)\t|     a \t|     b \t|  a/b   |\n" << "----------------------------------------------------------\n";

	double l = a + f.get(i - 2) * (b - a) / f.get(i),
		m = a + f.get(i - 1) * (b - a) / f.get(i), f1 = func(l), f2 = func(m);
	
	calls+=2;


	for (int k = i - 1; k >= 2; k--) {
	 	cout << k << "\t|  " << (a + b) / 2 << "\t|  " << func((a + b) / 2) << "\t|  " << a << "\t|  " << b << "\t|  " << fabs(a / b) << "  \n";

		if (f1<f2)
		{
			b = m; m = l;
			f2 = f1;
			l = a + f.get(k - 2) * (b - a) / f.get(k); 
			f1 = func(l), calls++;
		}
		else
		{
			a = l; l = m;
			m = a + f.get(k - 1) * (b - a) / f.get(k); 
			f1 = f2;
			f2 = func(m), calls++;
		}
		
	}
 	cout << "Number of iters: " << i<< "\n";
 //	cout << i << " | " << e << " |\n";
	return (a + b) / 2;
}

double lazy(double a, double b, double e, int n) {

	size_t iter = 1;
	double step = e / 100, min = b, x0 = a;

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
	cout << "Number of calls: " << iter -1<< "\n";

	return x0;
}

double G_ratio(double a, double b, double eps) {

	const double section1 = 0.38196601125;
	const double section2 = 0.61803398;
	double m1, m2,f1,f2;
	size_t iter = 1,calls=0;
	int O = log( fabs((b - a))/eps )/log(1.6335)+1;
	
 	

 	cout << "Golden ratio method\n" << "Starting with: [ " << a << " ;" << b << " ]\n----------------------------------------------------------\n" << " Iter\t| (a+b)/2\t| F((a+b)/2)\t|     a \t|     b \t|  a/b   |\n" << "----------------------------------------------------------\n";

 
	m2 = a+ (b - a)*section2;
	m1 = a + (b - a)*section1;
	f1 = func(m1), f2 = func(m2);
	calls += 2;
	for (int i = 1; i < O; i++) {
	 
		if (f1 < f2) {
			b = m2;
			m2 = m1;
			f2 = f1;
			m1 = a + (b - a)*section1;
			f1 = func(m1), calls++;

		}
		else {
			a = m1;
			m1 = m2;
			f1 = f2;
			m2 = a+ (b - a)*section2;
			f2 = func(m2), calls++;
		}
	 
		if (fabs((func(a) - func(b))) < eps ) {
 
			break;
		}
		
		cout << iter << "\t|  " << (a+b)/2 << "\t|  " << func((a + b) / 2) << "\t|  " << a << "\t|  " << b << "\t|  " << fabs(a / b) << "  \n";
		++iter;
	}
	cout << "Number of iters: " << iter-1 << "\n";
//	cout << "Number of calls: " << calls << "\n";
	return m1;
}
int main() {

	double a = M_PI_2, b = -M_PI_2, c;
	double e = 0.0001;
	
	freopen("out_ñ_1.txt", "w", stdout);
 	 std::cout.precision(6);
	cout << fixed; std::cout.precision(8);
	//freopen("out_ñ.txt", "w", stdout);

	/*for (double e = 0.00000001; e <= 0.1; e *= 10) {
		cout << e << "\n";
		diho(a, b, e);
		G_ratio(a, b, e);
		Fibb_method(a, b, e);
	}*/
	
	 //diho
	 cout << func(diho(a, b, e)) << "\n\n";
	 

	 //golden ratio
	 cout << func(G_ratio(a, b, e)) << endl;

	 //Fibbo
	  cout << func(Fibb_method(a, b, e)) << "\n";

	 
	 

	return 0;
}