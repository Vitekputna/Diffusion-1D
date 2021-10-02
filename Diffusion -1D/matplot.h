#pragma once

#include <engine.h>
#include <iostream>
#include <string>

#pragma comment (lib, "libmat.lib")
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")

class matplot
{
public:
	Engine* m_pEngine;
	matplot();
	~matplot();

	void figure();
	void plot(double* x, double* y, int x_size, bool hold);
	void plot(double* y, int size, bool hold);
	void animation2D(double* x_file, double* y_file, int arraysize, bool hold);
	void animated_line(double* x_file, double* y_file, int arraysize, int timesteps, bool hold);
	void exit();
	void title(std::string middle);
	void xlabel(std::string middle);
	void ylabel(std::string middle);
	void pause(float delay);
};
