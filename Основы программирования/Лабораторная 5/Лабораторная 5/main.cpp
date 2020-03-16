#include "main.h"
#include "sorts.h"
#include "massive_manip.h"

using namespace std;

int main() {
	setlocale(0, "Russian");
	int size; // Размер динамического массива.
	char answer; // Переменная для зацикливания программы.
	int comparisons; // Количество сравнений.
	int changes; // Количество перестановок.
	int i; // Переменная-счётчик
	int* a, * b, * c, * d; // Указатели на различные используемые массивы
	for (;;) {
		// Получение изначального неотсортированного массива.
		cout << "Введите желаемую длину массива: ";
		cin >> size;
		cout << endl;
		if (size <= 0) {
			cout << "Неверная длина массива!" << endl << endl;
			continue;
		}
		a = new int[size]; // Инициализация динамического массива.
		fill_massive(a, size);
		cout << "Неотсортированный массив:" << endl;
		print_massive(a, size);
		b = selection_sort(a, size, comparisons, changes); // Получение массива, отсортированного методом максимального значения.
		cout << "Отсортированный массив:" << endl;
		print_massive(b, size);
		cout << "      Показатели для изначального массива:" << endl << endl;
		cout << "  Метод максимального значения:" << endl;
		print_massive(b, size);
		cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		delete[] b;
		cout << "  Метод пузырька:" << endl;
		b = bubble_sort(a, size, comparisons, changes); // Получение массива, отсортированного методом пузырька.
		print_massive(b, size);
		cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		delete[] a;

		cout << "      Показатели для уже отсортированного массива:" << endl << endl;
		cout << "  Метод максимального значения:" << endl;
		c = selection_sort(b, size, comparisons, changes);
		cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		delete[] c;
		cout << "  Метод пузырька:" << endl;
		c = bubble_sort(b, size, comparisons, changes);
		cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		delete[] c;

		c = reverse_massive(b, size);
		delete[] b;
		cout << "      Показатели для инвертированного массива:" << endl << endl;
		cout << "  Метод максимального значения:" << endl;
		d = selection_sort(c, size, comparisons, changes); // Получение массива, отсортированного методом максимального значения.
		print_massive(d, size);
		cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		delete[] d;
		cout << "  Метод пузырька:" << endl;
		d = bubble_sort(c, size, comparisons, changes); // Получение массива, отсортированного методом пузырька.
		print_massive(d, size);
		cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		delete[] d;
		delete[] c;
		for (i = 5; i <= 500; i *= 10)
		{
			a = new int[i];
			fill_massive(a, i);
			cout << "      Показатели для массива длиной " << i << ":" << endl << endl;
			cout << "  Метод максимального значения:" << endl;
			b = selection_sort(a, i, comparisons, changes); // Получение массива, отсортированного методом максимального значения.
			cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
			delete[] b;
			cout << "  Метод пузырька:" << endl;
			b = bubble_sort(a, i, comparisons, changes); // Получение массива, отсортированного методом пузырька.
			delete[] b;
			cout << "Сравнений: " << comparisons << " Перестановок:" << changes << endl << endl;
		}
		cout << "Хотите продолжить? (y/n) ";
		cin >> answer;
		if (answer != 'y') {
			break;
		}
		cout << endl;
	}
}
