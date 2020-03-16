#include "main.h"
#include "matrix_manip.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(0, "Russian");
	int i, j; // ���������� ��� ��������.
	int size; // ������ �������.
    int precision; // ����������� �������� ����������.
	char answer; // ���������� ��� ����� ������������ ���� ����������� �����.
	for(;;) // ��������� ������� �������.
	{
		cout << "������� ������ �������: ";
		cin >> size;
		if (size > 0)
		{
			break;
		}
		cout << "�������� ������ �������!" << endl;
	}
	double** matrix = new double*[size]; // �������� �������.
	for (i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
	}
	fill_matrix(matrix, size); // ���������� �������.
	cout << "����� ����������� ��� ���������� ��� ������? ������� ���������� ������ ����� �������: ";
	cin >> precision;
	cout << endl;
	cout << "�������� � �������(y) ���� ��� � ��������� ������(n)  (y/n): ";
	cin >> answer;
	print_matrix(matrix, size, size, precision, answer == 'y'); // ����� �������.
	cout << endl;
	delete[] matrix;
	double B[10][10]; // �������� ������������ �������.
	double* B_help[10]; // �������� ���������������� ������� ��� ������ ������� B.
	for (i = 0; i < 10; i++)
	{
		B_help[i] = B[i];
		for(j = 0; j < 10; j++)
		{
			B[i][j] = j + i * 10;
		}
	}
	print_matrix(B_help, 10, 10, 0, false); // ����� ������� B.
	cout << endl;
	cout << B << "  " << B[0] << "  " << B[2] << endl;
	cout << B[0][0] << "  " << **B << "  " << *B[0] << endl;
	cout << *(*(B+1)) << "  " << *B[1] << endl;
	cout << *(B[0]+1) << "  " << *(*B+1) << endl;
	cout << B[0][20] << "  " << *(B[0]+20) << "  " << *B[2]<<endl;
	system("pause");
}