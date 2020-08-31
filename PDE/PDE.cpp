#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include "Gauss.h"
#include "Function.h"
#include "PDE.h"
#include "Integral.h"
//#define PI (3.1415926535897932384626433832795028841971693993751058209749445923078)
//#define F(x) sin(10 * PI * x)
using namespace std;

PDE::PDE(double a, double b, int n)
{
	this->a = a;
	this->b = b;
	this->n = n;
	h = (b - a) / (n + 1); 
	x = new double[n + 2];
	x[0] = a;
	x[n + 1] = b;
	for (int i = 1; i <= n; i++)
	{
		x[i] = x[0] + i * h;
	}
	u = new double[n];
	L = new double[n];
	A1 = new double[n - 1];
	A2 = new double[n];
	A3 = new double[n - 1];
	U = new double[n];
	

}
void PDE::setVectorLandMatrixA() 
{	 
    for (int i = 1; i <= n; i++)
	{
		Integral I1 (x[i - 1], x[i]);
		Integral I2 (x[i], x[i + 1]);
		L[i - 1] = h * (I1.integrate(I1.Y2) - I2.integrate(I2.Y2) - x[i - 1] * I1.integrate(I1.Y1) + x[i + 1] * I2.integrate(I2.Y1));
		A2[i - 1] = x[i - 1] * (x[i - 1] * I1.integrate(I1.Y4) - 2 * I1.integrate(I1.Y5)) + I1.integrate(I1.Y6) + I1.integrate(I1.Y3) + x[i + 1] * (x[i + 1] * I2.integrate(I2.Y4) - 2 * I2.integrate(I2.Y5)) + I2.integrate(I2.Y6) + I2.integrate(I2.Y3); 
		A1[i - 1] = A3[i - 1] = (x[i] + x[i + 1]) * I2.integrate(I2.Y5) - x[i] * x[i + 1] * I2.integrate(I2.Y4) - I2.integrate(I2.Y6) - I2.integrate(I2.Y3);
	}
}
void PDE::setVectorU()  // Tridiagonal matrix algorithm
{
	double *t1 = new double[n];
	double *t2 = new double[n];
	t1[0] = A2[0]; 
	t2[0] = L[0];
	for (int i = 1; i < n; i++)
	{
		t1[i] = A2[i] - A1[i - 1] * A3[i - 1] / t1[i - 1];
		t2[i] = L[i] - A1[i - 1] * t2[i - 1] / t1[i - 1];
	}
	u[n - 1] = t2[n - 1] / t1[n - 1]; 
	for (int i = n - 2; i >= 0; i--)
	{
		u[i] = (t2[i] - A3[i] * u[i + 1]) / t1[i]; 
	}
	delete[] t1;
	delete[] t2; 
}
double PDE::findL2Error()
{
	double S[N];
	double sum = 0; 
	for (int i = 0; i < N; i++)
	{
		S[i] = (F(x[0] + h * s[i]) - u[0] * s[i]) * (F(x[0] + h * s[i]) - u[0] * s[i]) + (F(x[n] + h * s[i]) - u[n - 1] * (1 - s[i])) * (F(x[n] + h * s[i]) - u[n - 1] * (1 - s[i]));
		for (int j = 1; j < n; j++)
		{	
			S[i] += (F(x[j] + h * s[i]) - (u[j] - u[j - 1]) * s[i] - u[j - 1]) * (F(x[j] + h * s[i]) - (u[j] - u[j - 1]) * s[i] - u[j - 1]);
		}
		sum += w[i] *  S[i];
	}
	return sqrt (h * sum); 
}
void PDE::findErrorforPoint()
{	
	for (int i = 0; i < n; i++)
	{
		U[i] = fabs(F(x[i + 1]) - u[i]); 
	}
}
void PDE::displayResult ()
{
	cout << "\nThe approximate solution of the equation in x[1] is: " << u[0] << endl;
	cout << "\nThe error in x[1] is: " << U[0] << endl; 
	cout << "\nThe L2 error is: " << findL2Error() << endl;
}
double PDE::findMaxofU()
{
	double max = fabs(u[0]);
	for (int i = 1; i < n; i++)
	{
		if (max < fabs(u[i]))
		{
			max = fabs(u[i]); 
		}
	}
	return max; 
}
void PDE::getInfoToFile()
{
	ofstream file1("ValueU.txt", ios::out);
	if (file1.is_open())
	{
		for (int i = 0; i < n - 1; i++)
		{
			file1 << u[i] << " ";
		}
		file1 << u[n - 1] << '\n'; 
		file1.close(); 
	}
	else
	{
		cout << "Error: Cannot open file!" << endl;
	}
	ofstream file2("ValueX.txt", ios::out); 
	if (file2.is_open())
	{
		for (int i = 1; i < n; i++)
		{
			file2 << x[i] << " ";
		}
		file2 << x[n] << '\n'; 
		file2.close();
	}
	else
	{
		cout << "Error: Cannot open file!" << endl;
	}
	ofstream file3("ValueAB.txt", ios::out);
	if (file3.is_open())
	{
		file3 << a << ' ' << b; 
	}
	else
	{
		cout << "Error: Cannot open file!" << endl;
	}
	ofstream file4("MaxU.txt", ios::out); 
	if (file4.is_open())
	{
		file4 << findMaxofU();
	}
	else
	{
		cout << "Error: Cannot open file!" << endl; 
	}
}
PDE::~PDE()
{
	delete[] x;
	delete[] u;
	delete[] L;
	delete[] A1;
	delete[] A2;
	delete[] A3;
	delete[] U; 
}