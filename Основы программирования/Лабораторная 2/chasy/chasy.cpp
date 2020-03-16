#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");
	for (;;) {
		int h, m;
		cout << "Введите часы и минуты через пробел" << endl;
		cin >> h >> m;
		if (h > 23 || h < 0 || m > 59 || m < 0)
			cout << "Неверные данные!";
		else {
			if (m == 0 && h % 12 == 0) {
				if (h == 0)
					cout << "Полночь";
				else if (h == 12)
					cout << "Полдень";
			}
			else {
				int h_out;
				if (h == 12)
					h_out = 12;
				else
					h_out = h % 12;
				cout << h_out << " час";
				if (h_out > 1 && h_out < 5)
					cout << "а";
				else if (h_out == 0 || h_out > 4)
					cout << "ов";
				if (m == 0) {
					if (h < 5)
						cout << " ночи";
					else if (h < 12)
						cout << " утра";
					else if (h < 18)
						cout << " дня";
					else
						cout << " вечера";
					cout << " ровно";
				}
				else {
					cout << " " << m << " минут";
					if (m < 5 || m > 20) {
						if (m % 10 == 1)
						    cout << "а";
						else if (m % 10 > 1 && m % 10 < 5)
							cout << "ы";
					}
					if (h < 5)
						cout << " ночи";
					else if (h < 12)
						cout << " утра";
					else if (h < 18)
						cout << " дня";
					else
						cout << " вечера";
				}
			}
		}
		cout << endl << endl;
	}
}
