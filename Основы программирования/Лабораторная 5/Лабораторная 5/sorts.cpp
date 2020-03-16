#include "sorts.h"
#include "massive_manip.h"

using namespace std;

int* selection_sort(int* a, int size, int& comparisons, int& changes) { // Сортировка массива методом нахождения максимального значения.
	int i; // Индекс первого сравниваемого элемента.
	int inner_i; // Индекс второго сравниваемого элемента.
	int maximal_index; // Индекс этого максимального значения.
	comparisons = 0; // Количество сравнений между элементами.
	changes = 0; // Количество перестановок элементов.
	int* b = copy_massive(a, size); // Копирование массива, чтобы изначальный массив не изменялся.
	for (i = size - 1; i > 0; i--) {
		maximal_index = i;
		for (inner_i = 0; inner_i < i; inner_i++) { // Поиск наибольшего значения в неотсортированной части массива.
			comparisons++;
			if (b[inner_i] > b[maximal_index]) {
				maximal_index = inner_i;
			}
		}
		if (maximal_index != i) { // При необходимости, максимальное значение меняется со значением в конце неосортированной части массива.
			changes++;
			swap(b[maximal_index], b[i]);
		}
	}
	return b;
}


int* bubble_sort(int* a, int size, int& comparisons, int& changes) { // Сортировка массива методом пузырька.
	int i; // Индекс, показывающий, до какого элемента проводить сравнение.
	int inner_i; // Индекс первого сравниваемого элемента.
	int temp; // Переменная для обмена значений 2 элементов массива.
	comparisons = 0; // Количество сравнений между элементами.
	changes = 0; // Количество перестановок элементов.
	int* b = copy_massive(a, size); // Копирование массива, чтобы изначальный массив не изменялся.
	bool already_sorted = false; // Переменная, показывающая, не отсортировался ли уже массив.
	for (i = size - 1; i > 0 && !already_sorted; i--) {
		already_sorted = true;
		for (inner_i = 0; inner_i < i; inner_i++) {
			comparisons++;
			if (b[inner_i] > b[inner_i + 1]) { // Сравнение двух соседних значений из неотсортированной части массива.
				changes++;
				already_sorted = false;
				swap(b[inner_i], b[inner_i + 1]);
			}
		}
	}
	return b;
}