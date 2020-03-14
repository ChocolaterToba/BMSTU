#include <iostream>
#include "fractionsCheck.h"
#include "fraction.h"
#include "windows.h"

using namespace std;

int main() {
	setlocale(0, "russian");
	//ввод дроби с клавиатуры	
	cout << "¬ведите дробь: \n";
	Fractions z;
	cin >> z;
	cout << "z=" << z << endl;
	//проверка конструкторов
	Fractions fr1(10, 14), fr2;
	cout << "fr2=" << fr2 << endl;
	cout << "fr1=" << fr1 << endl;
	Fractions fr = "-1 4/8";
	cout << "fr=" << fr << endl;
	Fractions x(z), y;
	cout << "x=" << x << endl;
	double dbl = -1.25;
	Fractions f = dbl;
	cout << "f=" << f << endl;
	//проверка перегруженной операции "+"
	y = x + z;
	cout << "y=" << y << endl;
	y += x;
	f += dbl / 2;
	cout << "f=" << f << endl;
	y = x + dbl;
	cout << "y=" << y << endl;
	y = dbl + y;
	cout << "y=" << y << endl;
	y += dbl;
	cout << "y=" << y << endl;
	int i = 5;
	y += i;
	cout << "y=" << y << endl;
	y = i + x;
	cout << "y=" << y << endl;
	y = x + i;
	cout << "y=" << y << endl;
	y += dbl + i + x;
	cout << "y=" << y << endl;
	system("pause");
}
