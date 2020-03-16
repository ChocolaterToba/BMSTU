#include "main.h"
#include "matrix_manip.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(0, "Russian");
	int i, j; // Переменные для итерации.
	int size; // Размер матрицы.
    int precision; // Необходимая точность вычислений.
	char answer; // Переменная для ввода необходимого вида отображения чисел.
	for(;;) // Получение размера матрицы.
	{
		cout << "Введите размер массива: ";
		cin >> size;
		if (size > 0)
		{
			break;
		}
		cout << "Неверный размер массива!" << endl;
	}
	double** matrix = new double*[size]; // Создание матрицы.
	for (i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
	}
	fill_matrix(matrix, size); // Заполнение матрицы.
	cout << "Какая погрешность вам необходима при выводе? Введите количество знаков после запятой: ";
	cin >> precision;
	cout << endl;
	cout << "Выводить в научном(y) виде или с плавающей точкой(n)  (y/n): ";
	cin >> answer;
	print_matrix(matrix, size, size, precision, answer == 'y'); // Вывод матрицы.
	cout << endl;
	delete[] matrix;
	double B[10][10]; // Создание статического массива.
	double* B_help[10]; // Создание вспомогательного массива для вывода массива B.
	for (i = 0; i < 10; i++)
	{
		B_help[i] = B[i];
		for(j = 0; j < 10; j++)
		{
			B[i][j] = j + i * 10;
		}
	}
	print_matrix(B_help, 10, 10, 0, false); // Вывод матрицы B.
	cout << endl;
	cout << B << "  " << B[0] << "  " << B[2] << endl;
	cout << B[0][0] << "  " << **B << "  " << *B[0] << endl;
	cout << *(*(B+1)) << "  " << *B[1] << endl;
	cout << *(B[0]+1) << "  " << *(*B+1) << endl;
	cout << B[0][20] << "  " << *(B[0]+20) << "  " << *B[2]<<endl;
	system("pause");
}