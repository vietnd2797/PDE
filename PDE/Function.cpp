#include <cmath>
#include "Gauss.h"
#include "Function.h"
double f(double x)
{
	return -exp(x)*(2 * (x*x + x + 1)*cos(x) + (2 * x - 1)*sin(x)); 
}
double F(double x)
{
	return exp(x)*sin(x);
}
double p(double x)
{
	return 1 + x * x;
}
double q(double x)
{
	return 1;
}


