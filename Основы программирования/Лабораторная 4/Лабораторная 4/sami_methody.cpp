#include "sami_methody.h"

using namespace std;

void half_div(int multiplier, int precision) {
	setlocale(0, "Russian");
	double left = -10;
	double right = 10;
	double middle;
	int N = 0;
	while (right - left >= 2 * pow(0.1, precision)) { // Решение методом половинного деления
		N++;
		middle = (left + right) / 2;
		if ((middle - multiplier * cos(middle) > 0) !=
			(left - multiplier * cos(left) > 0)) {
			right = middle;
		}
		else {
			left = middle;
		}
	}
	cout << "Результат метода половинного деления:" << endl;
	cout << fixed << setprecision(precision) << (left + right) / 2 << "   " << N << endl;
}

void newton(int multiplier, int precision) {
	setlocale(0, "Russian");
	double x = 0;
	double new_x = 1;
	int N = 0;
	while (abs(new_x - x) >= pow(0.1, precision)) { // Решение методом половинного деления
		N++;
		x = new_x;
		new_x = multiplier * (new_x * sin(new_x) + cos(new_x)) /
			(1 + multiplier * sin(new_x));
	}
	cout << "Результат метода Ньютона:" << endl;
	cout << fixed << setprecision(precision) << new_x << "   " << N << endl;
}

void simple_iter(int multiplier, int precision) {
	setlocale(0, "Russian");
	double x = -1;
	double new_x = 0;
	int N = 0;
	while (abs(new_x - x) >= pow(0.1, precision)) { // Решение методом половинного деления
		N++;
		x = new_x;
		new_x = multiplier * cos(new_x);
	}
	cout << "Результат метода простой итерации:" << endl;
	cout << fixed << setprecision(precision) << new_x << "   " << N << endl;
}
