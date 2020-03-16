#include "gauss.h"
#include "matrix_manip.h"
#include <algorithm>
#include <iostream>

using namespace std;

double** gauss(double** initial_matrix, int size)
{
	double** matrix = new double*[size]; // ����������������� �������.
	int i, j, k; // ���������� ��� ��������.
	for(i = 0; i < size; i++) // ������������ ���������������� ������ �� ��������.
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
		// "���������" ������, ���� �������, ������� ������ ���� �� ����� 0, ����� 0.
		{
			swap(matrix[i], matrix[j]);
		}
		if (!matrix[i][i])
		{
			return matrix;
		}
		for (j = size * 2 - 1; j >= i; j--)
		// �������������� ������, ����� ������� ������� ������� ������ 1.
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
	for (i = 0; i < size; i++) // ��������� ��������� ������� �� ��������.
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