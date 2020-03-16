#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	setlocale(0, "Russian");
	double a; // Вводимое с клавиатуры число
	double result; // Итоговый результат
	int i; // Переменная-счётчик
	char answer; // Переменная для повторного выполнения программы
	for (;;) {
		result = 1;
		cout << "Введите значение a: ";
		cin >> a;
		if (a >= 0) {
			for (i = 2; i <= 8; i += 2) {
				result *= pow(i, 2);
			}
			cout << "Результат: " << setprecision(15) << result - a
				 << endl << endl;
		}
		else {
			for (i = 3; i <= 9; i += 3) {
				result *= (i - 2);
			}
			cout << "Результат: " << result << endl << endl;
		}
		cout << "Продолжить работу? (y / n) ";
		cin >> answer;
		if (answer != 'y') {
			break;
		}
		cout << endl << endl;
	}
	return 0;
}
