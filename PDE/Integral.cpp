#include <iostream>
#include <cmath>
#include "Gauss.h"
#include "Function.h"
#include "Integral.h"
using namespace std; 
Integral::Integral(double lower, double upper)
{
	this->lower = lower;
	this->upper = upper;

	for (int i = 0; i < N; i++)
	{
		X[i] = (upper - lower) * s[i] + lower;
	}

	for (int i = 0; i < N; i++)
	{
		Y1[i] = f(X[i]);
		Y2[i] = X[i] * Y1[i];
		Y3[i] = p(X[i]);
		Y4[i] = q(X[i]);
		Y5[i] = X[i] * Y4[i];
		Y6[i] = X[i] * Y5[i];
		Y7[i] = F(X[i]);
		Y8[i] = X[i] * Y7[i];
		Y9[i] = Y7[i] * Y7[i];
		
	}
}
  
double Integral::integrate(const double Y[])
{
	/////////////// Gaussian quadrature for the case n = 7
	double sum = 0; 
	for (int i = 0; i < N; i++)
	{
		sum += w[i] * Y[i];
	}
	return (upper - lower) * sum;
}
Integral::~Integral()
{
}