#include "main.h"
#include "gauss.h"
#include "matrix_manip.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(0, "Russian");
	int i, j, size;
	cout << "������� ������ ������ �������: ";
	cin >> size;
	if (size < 1)
	{
		cout << "�������� ������ �������!";
		system("pause");
		return  0;
	}
	double** matrix = new double*[size];
	for (i = 0; i < size; i++) // ���������� �������.
	{
		matrix[i] = new double[size];
		cout << "������� ����� ������ " << size << " ��������(��) " << i + 1 << "-� ������"<< endl;
		for (j = 0; j < size; j++)
		{
			cin >> matrix[i][j];
		}
	}
	double** new_matrix = gauss(matrix, size);
	for (i = 0; i < size; i++) // ��������, ��� �������� ������� �������.
	{
		if (!new_matrix[i][i])
		{
			cout << "�������� ������� �� ����������" << endl;
			delete[] new_matrix;
			delete[] matrix;
			system("pause");
			return 0;
		}
	}
	cout << "�������� �������:" << endl;
	print_matrix(new_matrix, size, size, 8, false);
	cout << "������������ ����������� ������� � ��������:" << endl;
	print_matrix(multiply_matrix(matrix, new_matrix, size),
		         size, size, 8, false);
	delete[] new_matrix;
	delete[] matrix;
	system("pause");
	return 1;
}