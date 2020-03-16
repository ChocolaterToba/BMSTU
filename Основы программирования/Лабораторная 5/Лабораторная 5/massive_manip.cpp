#include "massive_manip.h"

using namespace std;

void fill_massive(int* a, int size) { // Заполнение массива случайными целыми числами.
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = 100 * rand() / RAND_MAX;
	}
}

int* copy_massive(int* a, int size) { // Копирование массива.
	int i;
	int* b = new int[size];
	for (i = 0; i < size; i++) {
		b[i] = a[i]; // Копирование элементов массива a в массив b.
	}
	return b;
}

int* reverse_massive(int* a, int size) { // Инверсия массива.
	int i;
	int* b = new int[size];
	for (i = 0; i < size; i++) {
		b[i] = a[size - 1 - i];
	}
	return b;
}

void print_massive(int* a, int size) { // Вывод массива на экран.
	int i;
	for (i = 0; i < size; i++) {
		cout << "a[" << i << "]=" << a[i] << endl;
	}
	cout << endl;
}