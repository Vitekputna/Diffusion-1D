#include "matplot.h"
matplot::matplot()
{
	m_pEngine = engOpen("null");
}

matplot::~matplot()
{

}

void matplot::figure()
{
	engEvalString(m_pEngine, "figure()");
}

void matplot::plot(double* x, double* y, int x_size, bool hold)
{
	int y_size = x_size;

	mxArray* Y = mxCreateDoubleMatrix(x_size, 1, mxREAL);
	memcpy((void*)mxGetPr(Y), (void*)y, x_size * sizeof(double));
	engPutVariable(m_pEngine, "Y", Y);

	mxArray* X = mxCreateDoubleMatrix(y_size, 1, mxREAL);
	memcpy((void*)mxGetPr(X), (void*)x, y_size * sizeof(double));
	engPutVariable(m_pEngine, "X", X);

	engEvalString(m_pEngine, "plot(X,Y,'-')");

	if (hold)
	{
		engEvalString(m_pEngine, "hold on");
	}
}

void matplot::plot(double* y, int size, bool hold)
{
	mxArray* Y = mxCreateDoubleMatrix(size, 1, mxREAL);
	memcpy((void*)mxGetPr(Y), (void*)y, size * sizeof(double));
	engPutVariable(m_pEngine, "Y", Y);

	engEvalString(m_pEngine, "plot(Y,'-')");

	if (hold)
	{
		engEvalString(m_pEngine, "hold on");
	}
}

void matplot::animation2D(double* x_file, double* y_file, int arraysize, bool hold)
{
	mxArray* SIN = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void*)mxGetPr(SIN), (void*)y_file, sizeof(double) * arraysize);
	engPutVariable(m_pEngine, "sinus", SIN);

	mxArray* DEG = mxCreateDoubleMatrix(arraysize, 1, mxREAL);
	memcpy((void*)mxGetPr(DEG), (void*)x_file, sizeof(double) * arraysize);
	engPutVariable(m_pEngine, "degrees", DEG);

	if (hold)
	{
		//engEvalString(m_pEngine, "figure('units','normalized','outerposition',[0 0 1 1])");
		engEvalString(m_pEngine, "for i = 1:length(degrees),plot(degrees(i),sinus(i),'r.'),ylim([-1 1]),xlim([0 1000]),pause(0.005),hold on,end");
	}
	else
	{
		//engEvalString(m_pEngine, "figure('units','normalized','outerposition',[0 0 1 1])");
		engEvalString(m_pEngine, "for i = 1:length(degrees),plot(degrees(i),sinus(i),'r.'),ylim([-1 1]),xlim([0 1000]),pause(0.005),end");
	}
}

void matplot::animated_line(double* x_file, double* y_file, int arraysize, int timesteps, bool hold)
{
	mxArray* SIN = mxCreateDoubleMatrix(arraysize, timesteps, mxREAL);
	memcpy((void*)mxGetPr(SIN), (void*)y_file, sizeof(double) * arraysize * timesteps);
	engPutVariable(m_pEngine, "datafile", SIN);

	mxArray* DEG = mxCreateDoubleMatrix(1, arraysize, mxREAL);
	memcpy((void*)mxGetPr(DEG), (void*)x_file, sizeof(double) * arraysize);
	engPutVariable(m_pEngine, "x", DEG);

	

	if (hold)
	{
		engEvalString(m_pEngine, "for i = 1:size(datafile,2),plot(x,datafile(:,i),'r'),hold on,pause(0.005),end");
	}
	else
	{
		engEvalString(m_pEngine, "for i = 1:size(datafile,2),plot(x,datafile(:,i),'r'),pause(0.005),end");
	}
}

void matplot::exit()
{
	engEvalString(m_pEngine, "exit");
}

void matplot::title(std::string middle)
{
	std::string front = "title('";
	std::string back = "')";
	std::string to_send = front + middle + back;
	engEvalString(m_pEngine, to_send.c_str());
}

void matplot::xlabel(std::string middle)
{
	std::string front = "xlabel('";
	std::string back = "')";
	std::string to_send = front + middle + back;
	engEvalString(m_pEngine, to_send.c_str());
}

void matplot::ylabel(std::string middle)
{
	std::string front = "ylabel('";
	std::string back = "')";
	std::string to_send = front + middle + back;
	engEvalString(m_pEngine, to_send.c_str());
}

void matplot::pause(float delay)
{
	std::string number = std::to_string(delay);

	std::string front = "pause('";
	std::string back = "')";
	std::string to_send = front + number + back;

	engEvalString(m_pEngine, to_send.c_str());
}
