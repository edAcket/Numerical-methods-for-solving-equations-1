#include <stdio.h>     
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <process.h>
#include <time.h>

double eps = 0.01;
double h, tau;

double solve(double y1, double y2, double y3,int i,int j)
{
	double y0 = y3;
	double y, f, dfdx, du;
	double d = eps + 1;
	while (d > eps)
	{
		y = y0;
		f =  (y*y) / (4 * h) + y/ (2 * tau) + (y3 - y1 - y2) / (2 * tau) +
			(y2*y2 - y1 * y1 - y3 * y3) / (4 * h);
		dfdx = y / (2 * h) + 1 / (2 * tau);
		y0 = y - f / dfdx;
		du = fabs(y0 - y);
		d = du;
	}
	return y0;
}

/*
double f1(double x)
{
	double y;
	y = 0.0 - x;
	return (y);
}

double f3(double x, double a, double b)
{
	double y;
	y = (x - a) / tau + (f(x) - f(b)) / h;
	return y;
}

double f4(double x)
{
	double y;
	y = 1 / tau + f1(x) / h;
	return y;
}
double solve(double a, double b)
{
	double result = b;
	double d = eps + 1;
	double y;
	while (d>eps)
	{
		y = result;
		result = y - f3(y,a,b)/ f4(y);
		d =fabs(eps - result);
	}
	return result;
}*/




int main(void)
{

	FILE *fp1;
	fp1 = fopen("result.out", "w");
	double **a,*x,*t;
	int i, j, n=100, m=1000,NN=1000;
	double X = -1, T = 3;
	const double PI = 3.141592653589793;
	a = (double**)malloc(n * sizeof(double*));
	for (i = 0; i < n; i++)  // цикл по строкам
		a[i] = (double*)malloc(m * sizeof(double));
	x = (double*)malloc(NN * sizeof(double));
	t = (double*)malloc(NN * sizeof(double));
	h = X / (1-n);
    tau = T / (m - 1);
	


	 for (int j = 0; j < m; j++)
	 {
		 t[j] = T * j / m;
	 }

	 for (int k = 0; k < n; k++)
	 {
		 x[k] = (X * k) / n;
	 }


	 for (i = 0; i < n; i++)
			 {
				 for (j = 0; j < m; j++)
				 {
					 if ((i == 0) && (j == 0))
						 a[i][j] = (2 - 4 * atan(2) / PI);
					 else
					 {
						 if (i == 0)
							 a[i][j] = (2 - 4*atan(2)/PI)*exp(-t[j]);
						 if (j == 0)
							 a[i][j] = (2- 4 * atan(x[i]+2) / PI);
					 }
				 }
			 }
	 for (i = 0; i < n-1; i++)
	 {
		 for (j = 0; j < m-1; j++)
		 {
			 a[i+1][j+1] = solve(a[i][j], a[i+1][j], a[i][j+1], i, j);
			 fprintf(fp1, "%lf %lf %lf\n", x[i], t[j] , a[i][j]);
		 }
     }
	 fclose(fp1);
   
}

