#include <stdio.h>
#include <iostream>
#include <cmath>
#include "data.h"
#include "matplot.h"

double dx = 0.01;
double x_end = 1;
int x_size = x_end / dx;

double dt0 = 1e-3;
double t_end = 0.25;
int t_size = t_end / dt0;

double CFL = 0.5;

data U(t_size, x_size);
data x(1, x_size);
data qe(1, x_size);
data qw(1, x_size);
data TV(1, t_size);

data dt(1, t_size);

//double qe; //i+1/2
//double qw; //i-1/2

double Fe;
double Fw;

double maxqe = 0;
double Time = 0;

matplot M;

double flux(double u)
{
	return 0.5 * pow(u, 2);
}

void Total_variation(int t)
{
	double sum = 0;
	for (int i = 0; i < x_size-1; i++)
	{
		sum += abs(U.get(t,i+1) - U.get(t, i));
	}
	TV.get(0, t) = sum;
}

int main()
{
	//PP
	for (int i = 0; i < x_size; i++)
	{
		if (i * dx > 0.25 && i * dx < 0.5)
		{
			U.get(0, i) = 1;
			x.get(0, i) = i * dx;

		}
		else
		{
			U.get(0, i) = 0;
			x.get(0, i) = i * dx;
		}
	}

	//
	//for (int t = 0; t < t_size-1; t++)
	int t = 0;
	while(Time < t_end && t < t_size)
	{
		for (int i = 1; i < x_size - 1; i++)
		{
			qe.get(0, i) = abs(0.5 * (U.get(t, i + 1) + U.get(t, i)));
			qw.get(0, i) = abs(0.5 * (U.get(t, i - 1) + U.get(t, i)));

			maxqe = std::max(maxqe, abs(qe.get(0, i)));
		}

		dt.get(0, t) = CFL * dx / (maxqe);

		for (int i = 1; i < x_size-1; i++)
		{

			Fe = 0.5 * (flux(U.get(t, i)) + flux(U.get(t, i + 1))) - 0.5 * qe.get(0,i) * (U.get(t, i + 1) - U.get(t, i));
			Fw = 0.5 * (flux(U.get(t, i)) + flux(U.get(t, i - 1))) - 0.5 * qw.get(0,i) * (U.get(t, i) - U.get(t, i-1));

			U.get(t + 1, i) = U.get(t, i) -dt.get(0,t) / dx * (Fe - Fw);
		}
		U.get(t, x_size-1) = U.get(t, x_size-2);
		Time += dt.get(0, t);
		std::cout << Time << std::endl;
		t++;
	}

	U.get(t_size - 1, x_size - 1) = U.get(t_size - 2, x_size - 2);

	U.print_to_file("data.txt");
	M.animated_line(x.data_p,U.data_p,x_size,t,false);
	system("pause");
	M.exit();


}