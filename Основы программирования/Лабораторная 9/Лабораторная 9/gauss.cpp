#include "gauss.h"
#include "matrix_manip.h"
#include <algorithm>
#include <iostream>

using namespace std;

double** gauss(double** initial_matrix, int size)
{
	double** matrix = new double*[size]; // Преобразовываемая матрица.
	int i, j, k; // Переменные для итерации.
	for(i = 0; i < size; i++) // Приписывание единичнойматрицы справа от исходной.
	{
		matrix[i] = new double[size * 2];
		for(j = 0; j < size; j++)
		{
			matrix[i][j] = initial_matrix[i][j];
		}
		for(j = size; j < size * 2; j++)
		{
			matrix[i][j] = (j - size == i);
		}
	}
	for (i = 0; i < size; i++)
	{
		for (j = i + 1; !matrix[i][i] && j < size; j++)
		// "Опускание" строки, если элемент, который должен быть не равен 0, равен 0.
		{
			swap(matrix[i], matrix[j]);
		}
		if (!matrix[i][i])
		{
			return matrix;
		}
		for (j = size * 2 - 1; j >= i; j--)
		// Преобразование строки, чтобы сделать текущий элемент равным 1.
		{
			matrix[i][j] /= matrix[i][i];
		}
		for (j = size * 2 - 1; j >= i; j--)
		{
			for (k = 0; k < size; k++)
			{
				if (k != i)
				{
					matrix[k][j] -= matrix[i][j] * matrix[k][i];
				}
			}
		}
	}
	double** return_matrix = new double*[size];
	for (i = 0; i < size; i++) // Отделение единичной матрицы от обратной.
	{
		return_matrix[i] = new double[size];
		for (j = 0; j < size; j++)
		{
			return_matrix[i][j] = matrix[i][j + size];
		}
	}
	delete[] matrix;
	return return_matrix;
}