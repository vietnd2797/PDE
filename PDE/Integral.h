#ifndef INTEGRAL_H
#define INTEGRAL_H
#include "Gauss.h"
class Integral
{
private:
	double upper, lower; // can tich phan
	double X[N];
	
public:
    double Y1[N]; // gia tri ham f(x)
    double Y2[N]; //gia tri ham f(x)*x
	double Y3[N]; // gia tri ham p(x)
    double Y4[N]; // gia tri ham q(x)
	double Y5[N]; // gia tri ham q(x)*x
    double Y6[N]; // gia tri ham q(x)*x*x
	double Y7[N]; // gia tri ham F(x)
    double Y8[N]; // gia tri ham F(x) * x
	double Y9[N];  // gia tri ham F(x) * F(x)
	Integral(double lower, double upper);
	double integrate(const double Y[]);
	~Integral();
};
#endif