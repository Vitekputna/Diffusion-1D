#pragma once
#include <stdio.h>
#include <string>
#include <fstream>

template<typename T>
class tenzor
{
public:
	int x_size;
	int y_size;
	T* data_p;
	std::ofstream file;

	tenzor();
	~tenzor();
	tenzor(int x_size, int y_size);
	T& operator[](const int pos);
	tenzor<T> operator+(tenzor<T>& other);
	tenzor<T> operator-(tenzor<T>& other);
	tenzor<T> operator*(int number);
	tenzor<T> operator*(float number);
	tenzor(const tenzor& A);
	T& get(const int x, const int y);
	T* row(const int row);
	T* collum(const int collum);
	void print();
	void print_to_file(std::string mame);
};

template<typename T>
tenzor<T> operator*(const int number, tenzor<T>& rhs)
{
	return rhs * number;
}


