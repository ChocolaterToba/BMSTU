#include "matrix_manip.h"
#include <iostream>
#include <iomanip>

using namespace std;

void print_matrix(double** matrix, int in_rows, int in_cols, int precision, bool science) // ����� �������.
{
	int element_width; // ������ ���� ��� 1 ������� �������.
	int cols; // ���������� ���������, ������������ � 1 ������.
	int big_rows; // ���������� "������� �����".
	int i, j, k;
	if (science)
	{
		element_width = precision + 10;
		cout << scientific;
	}
	else
	{
		element_width = precision + 6; // �� ����� ����� � ������� float ����� ������ �����.
		cout << fixed;
	}
	cols = 80 / element_width;
	big_rows = in_cols / cols + (bool)(in_cols % cols);
	for (i = 0; i < big_rows; i++) // ����� "������� �����" ��� ������ ������� ������.
	{
		for (j = 0; j < in_rows; j++) // ����� ������� ����� �������.
		{
			for (k = 0; (k < cols) & (i * cols + k < in_cols); k++) // ����� �������� ������� (� ������� ������).
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