#ifndef PDE_H
#define PDE_H
class PDE
{
private: 
	int n; // chia [a, b] thanh n phan tu ( n + 1 doan [x[k], x[k+1]], k = 0,1,..,n )
	double a, b, h; // h = x[i+1] - x[i], i = 0,1,..,n ; e la sai so trong khong gian L2
	double *L; // vector cac phiem ham l(v) 
	double *A1, *A2, *A3; // 3 duong cheo ma tran A
	double *x;
public:
	double *u; // Vector nghiem gan dung u
	double *U; // Vector sai so diem
	PDE(double a, double b, int n);
	void setVectorLandMatrixA(); 
	void setVectorU();
	double findL2Error();
	void findErrorforPoint(); 
	void displayResult();
	double findMaxofU(); 
	void getInfoToFile();
	~PDE();
};
#endif
