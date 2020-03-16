#include <iostream>

using namespace std;

int main() {
	setlocale(0, "Russian");
	int n; // Вводимое с клавиатуры число
	int m; // Вводимое с клавиатуры число
	int i; // Переменная-счётчик
	int result; // Результат, итоговая сумма
	char answer; // Переменная для повторного выполнения программы
	for (;;) {
		cout << "Введите натуральные n и m через пробел: ";
		cin >> n >> m;
		cout << endl;
		if (n <= 0 || m <= 0) {
			cout << "Ошибка! Хотя бы одно из чисел не натуральное!"
				<< endl << endl;
			continue;
		}
		else {
			result = 0;
			for (i = 5; i <= n; i += 5) {
				if (i % m) {
					result += i;
				}
			}
			cout << "Результат:" << result << endl << endl;
		}
		cout << "Продолжить работу? (y / n) ";
		cin >> answer;
		if (answer != 'y') {
			break;
		}
		cout << endl << endl;
	}
}
