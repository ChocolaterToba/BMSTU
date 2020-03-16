#include "matrix_manip.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

void fill_matrix(double** matrix, int size) // ���������� ������� �� �������.
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		matrix[i][i] = 1;
		for (j = i + 1; j < size; j++) // �������� ���� ������� ���������.
		{
			matrix[i][j] = matrix[i][j - 1] / pow(j + 1, i + 1);
		}
		if (i)
		{
			matrix[i][0] = -1;
		}
		for (j = 1; j < i; j++) // �������� ���� ������� ���������
		{
			matrix[i][j] =  -1 * matrix[i][j - 1] / pow(j + 1, i + 1);
		}
	}
}

void print_matrix(double** matrix, int in_rows, int in_cols, int precision, bool science) // ����� �������.
{
	int element_width; // ������ ���� ��� 1 ������� �������.
	int cols; // ���������� ���������, ������������ � 1 ������.
	int big_rows; // ���������� "������� �����".
	int i, j, k; // ���������� ��� ��������.
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