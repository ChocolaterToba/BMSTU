#include "matrix_manip.h"
#include <iostream>
#include <iomanip>

using namespace std;

void print_matrix(double** matrix, int in_rows, int in_cols, int precision, bool science) // Вывод матрицы.
{
	int element_width; // Ширина поля под 1 элемент матрицы.
	int cols; // Количество элементов, помещающихся в 1 строке.
	int big_rows; // Количество "больших строк".
	int i, j, k;
	if (science)
	{
		element_width = precision + 10;
		cout << scientific;
	}
	else
	{
		element_width = precision + 6; // На вывод числа в формате float нужно меньше места.
		cout << fixed;
	}
	cols = 80 / element_width;
	big_rows = in_cols / cols + (bool)(in_cols % cols);
	for (i = 0; i < big_rows; i++) // Номер "больших строк" для вывода длинных матриц.
	{
		for (j = 0; j < in_rows; j++) // Номер обычных строк матрицы.
		{
			for (k = 0; (k < cols) & (i * cols + k < in_cols); k++) // Номер столбцов матрицы (в большой строке).
			{
				cout << setw(element_width) << left
					<< setprecision(precision)
					<< matrix[j][i * cols + k];
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
}

double** multiply_matrix(double** first, double** second, int size)
{
	double** result = new double* [size];
	int i, j, k;
	for (i = 0; i < size; i++)
	{
		result[i] = new double[size];
		for (j = 0; j < size; j++)
		{
			result[i][j] = 0;
			for (k = 0; k < size; k++)
			{
				result[i][j] += first[i][k] * second[k][j];
			}
		}
	}
	return result;
}