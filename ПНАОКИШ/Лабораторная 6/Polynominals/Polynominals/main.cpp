#include "Polynomial.h"
#include <iostream>

using namespace std;

int main() {
	Polynomial first, second, third;
	cout << "Input first polynomial" << endl;
	cin >> first;
	cout << "Input second polynomial" << endl;
	cin >> second;
	cout << "first + second = " << first << " + " << second << " = " << first + second << endl;
	cout << "first * second = " << first << " * " << second << " = " << first * second << endl;
	return 0;
}