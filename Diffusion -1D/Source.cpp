#include <stdio.h>
#include <iostream>
#include "tenzor.h"
#include "matplot.h"

const int size = 100;
const int timesteps = 3500;
const int capturetime = 25;
const double dx = 0.01;
const double c = -0.02;

const double L_boundary = 100;
const double R_boundary = 200;

double last;
double delta = 100;

std::string name = "datafile.txt";

matplot M;

int main()
{
	tenzor<double> U(1, size);

	double x[size];

	for (int i = 0; i < size; i++)
	{
		x[i] = i * dx;
	}

	
	U.get(0, 0) = L_boundary;
	U.get(0, size - 1) = R_boundary;

	std::cout << "Solving.." << std::endl;

	int k = 0;
	for(int t = 0;t < timesteps;t++)
	{
		for (int i = 1; i < size - 1; i++)
		{
			U.get(0, i) = (U.get(0, i + 1) + U.get(0, i - 1)) / 2 + c;
		}

		if (t == k*timesteps/capturetime)
		{
			M.animated_line(x, U.data_p, size, 1,true);
			k++;
		}
	}
	std::cout << "Done :)" << std::endl;

	//M.animated_line(x,U.data_p,size,1,false);

	system("pause");
	U.print_to_file(name);
	M.exit();
}