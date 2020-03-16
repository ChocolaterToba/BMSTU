#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	setlocale(0, "Russian");
	const double e = 2.7182818284590; // Число Эйлера
	double precision; // Требуемая погрешность
	int n; // Номер последнего элемента в сумме
	double x; // Переменная x, используемая в формуле
	double S; // Значение суммы
	double last; // Значение последнего элемента суммы
	char answer; // Переменная для повтора цикла
	for (;;) {
		cout << "Какую погрешность вам надо? Введите: ";
		cin >> precision;
		if (precision <= 0) {
			cout << "Некорректная погрешность!" << endl << endl;
			continue;
		}
		else {
			cout << left << setw(4) << "x"
				 << setw(abs(log10(precision)) + 3) << "Y(x)"
				 << setw(abs(log10(precision)) + 3) << "S(x)"
				 << "N" << endl; // Вывод шапки таблицы
			for (x = 0; x <= 1; x += 0.2) {
				n = 0;
				S = 0;
				last = 1;
				while (last >= precision) { // Накопление суммы
					n += 1;
					S += last;
					last *= pow(x, 2) / (4 * pow(n, 2) - 2 * n);
				}
				n += 1;
				S += last; // Прибавление последнего элемента к сумме
				cout << setw(4) <<  left << setprecision(1) << x
					 << showpoint << setw(abs(log10(precision)) + 3)
					 << setprecision(abs(log10(precision)) + 1)
					 << (pow(e, x) + pow(e, -x)) / 2
					 << setw(abs(log10(precision)) + 3)
					 << S << n << endl; // Вывод значений
			}
		}
		cout << "Продолжить работу? (y / n) ";
		cin >> answer;
		if (answer != 'y') {
			break;
		}
		cout << endl << endl;
	}
}
