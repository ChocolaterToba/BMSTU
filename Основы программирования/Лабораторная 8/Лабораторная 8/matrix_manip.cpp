#include "matrix_manip.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

void fill_matrix(double** matrix, int size) // Заполнение матрицы по правилу.
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		matrix[i][i] = 1;
		for (j = i + 1; j < size; j++) // Элементы выше главной диагонали.
		{
			matrix[i][j] = matrix[i][j - 1] / pow(j + 1, i + 1);
		}
		if (i)
		{
			matrix[i][0] = -1;
		}
		for (j = 1; j < i; j++) // Элементы ниже главной диагонали
		{
			matrix[i][j] =  -1 * matrix[i][j - 1] / pow(j + 1, i + 1);
		}
	}
}

void print_matrix(double** matrix, int in_rows, int in_cols, int precision, bool science) // Вывод матрицы.
{
	int element_width; // Ширина поля под 1 элемент матрицы.
	int cols; // Количество элементов, помещающихся в 1 строке.
	int big_rows; // Количество "больших строк".
	int i, j, k; // Переменные для итерации.
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