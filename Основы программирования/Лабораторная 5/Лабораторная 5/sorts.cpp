#include "sorts.h"
#include "massive_manip.h"

using namespace std;

int* selection_sort(int* a, int size, int& comparisons, int& changes) { // ���������� ������� ������� ���������� ������������� ��������.
	int i; // ������ ������� ������������� ��������.
	int inner_i; // ������ ������� ������������� ��������.
	int maximal_index; // ������ ����� ������������� ��������.
	comparisons = 0; // ���������� ��������� ����� ����������.
	changes = 0; // ���������� ������������ ���������.
	int* b = copy_massive(a, size); // ����������� �������, ����� ����������� ������ �� ���������.
	for (i = size - 1; i > 0; i--) {
		maximal_index = i;
		for (inner_i = 0; inner_i < i; inner_i++) { // ����� ����������� �������� � ����������������� ����� �������.
			comparisons++;
			if (b[inner_i] > b[maximal_index]) {
				maximal_index = inner_i;
			}
		}
		if (maximal_index != i) { // ��� �������������, ������������ �������� �������� �� ��������� � ����� ���������������� ����� �������.
			changes++;
			swap(b[maximal_index], b[i]);
		}
	}
	return b;
}


int* bubble_sort(int* a, int size, int& comparisons, int& changes) { // ���������� ������� ������� ��������.
	int i; // ������, ������������, �� ������ �������� ��������� ���������.
	int inner_i; // ������ ������� ������������� ��������.
	int temp; // ���������� ��� ������ �������� 2 ��������� �������.
	comparisons = 0; // ���������� ��������� ����� ����������.
	changes = 0; // ���������� ������������ ���������.
	int* b = copy_massive(a, size); // ����������� �������, ����� ����������� ������ �� ���������.
	bool already_sorted = false; // ����������, ������������, �� �������������� �� ��� ������.
	for (i = size - 1; i > 0 && !already_sorted; i--) {
		already_sorted = true;
		for (inner_i = 0; inner_i < i; inner_i++) {
			comparisons++;
			if (b[inner_i] > b[inner_i + 1]) { // ��������� ���� �������� �������� �� ����������������� ����� �������.
				changes++;
				already_sorted = false;
				swap(b[inner_i], b[inner_i + 1]);
			}
		}
	}
	return b;
}