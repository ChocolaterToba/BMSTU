#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	setlocale(0, "Russian");
	int n; // n вводится с клавиатуры
	int i; // Переменная-счётчик
	double x; // Значение x, вводится с клавиатуры
	double a; // Значение a, вводится с клавиатуры
	double y; // Итоговая сумма
	double last; // Последний элемент суммы
	char answer; // Переменная для повторного выполнения программы
	for (;;) {
		cout << "Введите значения x, a через пробел: ";
		cin >> x >> a;
		cout << endl;
		if (a <= 0) {
			cout << "Неверное значение a!" << endl << endl;
			continue;
		}
		for (;;) {
			cout << "Введите значение n: ";
			cin >> n;
			cout << endl;
			if (n <= 0) {
				cout << "Неверное значение n!" << endl << endl;
				continue;
			}
			else {
				y = 0;
				last = 1;
				for (i = 1; i <= n; i++) {
					y += last;
					last *= x * log(a) / i;
					if (i == 3 || i == 5 || i == 10) {
						cout << "Сумма на " << i << "-м слагаемом: " << fixed << y << endl << endl;
					}
				}
				cout << "Итоговая сумма: " << fixed << y << endl << endl;
				cout << "Хотите ввести другое значение n? (y / n) ";
				cin >> answer;
				cout << endl;
				if (answer != 'y') {
					break;
				}
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