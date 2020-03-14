#include <iostream>
#include "multipliers.h"
#include "..\Stack\My_stack.h"

using namespace std;

int main() {
	int number;
	cout << "Please input a number to get it's multipliers: ";
	cin >> number;
	cout << endl << endl;
	MyStack<int> multipliers;
	MyStack<int> other;
	get_multipliers(number, multipliers);
	cout << number << "=";
	while (!multipliers.empty()) {
		other.push(*(multipliers.top_inf()));
		cout << *(multipliers.top_inf()) << "*";
		multipliers.pop();
	}
	cout << '\b' << '\0' << '\b' << endl;

	cout << number << "=";
	while (!other.empty()) {
		cout << *(other.top_inf()) << "*";
		other.pop();
	}
	cout << '\b' << '\0' << '\b' << endl;
}

void get_multipliers(int number, MyStack<int>& multipliers) {
	if (number <= 0) {
		cout << "This function is undefined for numbers less that or equal to 0!" << endl << endl;
		return;
	}
	if (number == 1) {
		multipliers.push(1);
		return;
	}
	for (int i = 2; i <= number; i++) {
		while (number % i == 0) {
			multipliers.push(i);
			number /= i;
		}
	}
}
