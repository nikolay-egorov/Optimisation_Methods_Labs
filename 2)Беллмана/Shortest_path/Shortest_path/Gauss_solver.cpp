#include "Gauss_solver.h"


 
Gauss_solver::Gauss_solver(int)
{
	coef = new double*[n];
	y = new double[n];
	for (int i = 0; i < n; i++) //init our array
	{
		coef[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
		//	cin >> coef[i][j];
			 
		}
	}
}

void Gauss_solver::solve()
{
	double *x, max;
	int k, index;
	const double eps = 0.00001;   
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// find string with max a[i][k], if any
		max = abs(coef[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(coef[i][k]) > max)
			{
				max = abs(coef[i][k]);
				index = i;
			}
		}
		 
		if (max < eps)
		{
			// no soulution :(
	//		cout << "Решение не могут быть найдены из-за  " << index << " столба A\n";
			return;
		}
		for (int j = 0; j < n; j++)
		{

			swap(coef[k][j], coef[index][j]);
		 

		}

		swap(y[k], y[index]);
		 

		for (int i = k; i < n; i++)
		{
			double temp = coef[i][k];
			if (abs(temp) < eps)
				continue; // skip if it's a trivial coef
			for (int j = 0; j < n; j++) {
				coef[i][j] /= temp;

				 

			}
		//	cout << "\n";

			y[i] = y[i] / temp;
			if (i == k)
				continue;
			for (int j = 0; j < n; j++) {
				coef[i][j] -= coef[k][j];
				 
			}

			y[i] -= y[k];
		}
		k++;
		 

	}

	// reverse step
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++) {
			y[i] = y[i] - coef[i][k] * x[k];
		//	sing[i][k] -= a[i][k] * sing[i + 1][k];
		}

	}
/*	sing[0][0] -= a[0][1] * sing[1][0];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			cout << sing[i][j] << ' ';
		}
		cout << "\n";
	}
	*/
	ans = x;
	 
}

Gauss_solver::~Gauss_solver()
{
}
