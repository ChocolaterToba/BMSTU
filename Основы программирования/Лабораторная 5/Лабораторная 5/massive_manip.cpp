#include "massive_manip.h"

using namespace std;

void fill_massive(int* a, int size) { // ���������� ������� ���������� ������ �������.
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		a[i] = 100 * rand() / RAND_MAX;
	}
}

int* copy_massive(int* a, int size) { // ����������� �������.
	int i;
	int* b = new int[size];
	for (i = 0; i < size; i++) {
		b[i] = a[i]; // ����������� ��������� ������� a � ������ b.
	}
	return b;
}

int* reverse_massive(int* a, int size) { // �������� �������.
	int i;
	int* b = new int[size];
	for (i = 0; i < size; i++) {
		b[i] = a[size - 1 - i];
	}
	return b;
}

void print_massive(int* a, int size) { // ����� ������� �� �����.
	int i;
	for (i = 0; i < size; i++) {
		cout << "a[" << i << "]=" << a[i] << endl;
	}
	cout << endl;
}