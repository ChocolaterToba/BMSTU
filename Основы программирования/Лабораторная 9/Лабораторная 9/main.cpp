#include "main.h"
#include "gauss.h"
#include "matrix_manip.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(0, "Russian");
	int i, j, size;
	cout << "Введите нужный размер матрицы: ";
	cin >> size;
	if (size < 1)
	{
		cout << "Неверный размер матрицы!";
		system("pause");
		return  0;
	}
	double** matrix = new double*[size];
	for (i = 0; i < size; i++) // Заполнение матрицы.
	{
		matrix[i] = new double[size];
		cout << "Введите через пробел " << size << " элемента(ов) " << i + 1 << "-й строки"<< endl;
		for (j = 0; j < size; j++)
		{
			cin >> matrix[i][j];
		}
	}
	double** new_matrix = gauss(matrix, size);
	for (i = 0; i < size; i++) // Проверка, что обратная матрица нашлась.
	{
		if (!new_matrix[i][i])
		{
			cout << "Обратной матрицы не существует" << endl;
			delete[] new_matrix;
			delete[] matrix;
			system("pause");
			return 0;
		}
	}
	cout << "Обратная матрица:" << endl;
	print_matrix(new_matrix, size, size, 8, false);
	cout << "Произведение изначальной матрицы и обратной:" << endl;
	print_matrix(multiply_matrix(matrix, new_matrix, size),
		         size, size, 8, false);
	delete[] new_matrix;
	delete[] matrix;
	system("pause");
	return 1;
}