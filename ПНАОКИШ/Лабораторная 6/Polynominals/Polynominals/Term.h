#pragma once
#include <iostream>
#include <string>

using namespace std;

class Polynomial;

class Term {
private:
	int multiplier;
	size_t power;

public:
	Term(int multiplier = 0, int power = 0);
	Term(string& line);
	~Term() = default;

	friend Term operator+(const Term& first, const Term& second);
	friend istream& operator>>(istream& stream, Term& term);
	friend ostream& operator<<(ostream& stream, const Term& term);

	friend class Polynomial;

	friend istream& operator>>(istream& stream, Polynomial& polynomial);
	friend ostream& operator<<(ostream& stream, const Polynomial& polynomial);
};
