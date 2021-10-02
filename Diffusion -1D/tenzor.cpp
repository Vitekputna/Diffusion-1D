#include "tenzor.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

template<typename T>
inline tenzor<T>::tenzor()
{
	x_size = 0;
	y_size = 0;
	data_p = NULL;
}

template<typename T>
tenzor<T>::~tenzor()
{
	free(data_p);
	file.close();
}

template<typename T>
tenzor<T>::tenzor(int x_size, int y_size)
{
	std::ofstream file;

	this->x_size = x_size;
	this->y_size = y_size;

	data_p = reinterpret_cast<T*>(calloc(x_size * y_size, sizeof(T)));
}

template<typename T>
T& tenzor<T>::operator[](const int pos)
{
	T* address = data_p;
	return address[pos];
}

template<typename T>
tenzor<T> tenzor<T>::operator+(tenzor<T>& other)
{
	tenzor<T> output(other.x_size, other.y_size);

	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < y_size; j++)
		{
			output.get(i, j) = this->get(i, j) + other.get(i, j);
		}
	}


	return output;
}

template<typename T>
tenzor<T> tenzor<T>::operator-(tenzor<T>& other)
{
	tenzor<T> output(other.x_size, other.y_size);

	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < y_size; j++)
		{
			output.get(i, j) = this->get(i, j) - other.get(i, j);
		}
	}


	return output;
}

template<typename T>
tenzor<T> tenzor<T>::operator*(int number)
{
	tenzor<T> output(x_size, y_size);

	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < y_size; j++)
		{
			output.get(i, j) = number * this->get(i, j);
		}
	}

	return output;
}

template<typename T>
tenzor<T> tenzor<T>::operator*(float number)
{
	return tenzor<T>();
}

template<typename T>
tenzor<T>::tenzor(const tenzor& A)
{
	x_size = A.x_size;
	y_size = A.y_size;



	data_p = reinterpret_cast<T*>(malloc(x_size * y_size * sizeof(T)));

	if (data_p)
	{
		std::memcpy(data_p, A.data_p, x_size * y_size * sizeof(T));
	}
}

template<typename T>
T& tenzor<T>::get(const int x, const int y)
{
	T* address = data_p;
	T* ard = &address[x * y_size + y];
	return address[x * y_size + y];
}

template<typename T>
T* tenzor<T>::row(const int row)
{
	return data_p + row * y_size;
}

template<typename T>
T* tenzor<T>::collum(const int collum)
{
	std::cout << "no worky worky" << std::endl;
	return 0;
}

template<typename T>
void tenzor<T>::print()
{
	std::cout << "matrix:" << typeid(this).name() << std::endl;

	for (int i = 0; i < x_size; i++)
	{
		for (int j = 0; j < y_size; j++)
		{
			std::cout << this->get(i, j) << "\t";
		}
		std::cout << std::endl;
	}
}

template<typename T>
void tenzor<T>::print_to_file(std::string name)
{
	file.open(name);
	int r = 1;
	for (int i = 0; i < x_size * y_size; i++)
	{
		file << this->data_p[i] << " ";

		if (i == (y_size * r - 1))
		{
			file << "\n";
			r++;
		}
	}	
}


template class tenzor<int>;
template class tenzor<char>;
template class tenzor<float>;
template class tenzor<double>;