#pragma once
#include <iostream>
#include <vector>
#include "Term.h"


using namespace std;

class Polynomial {
private:
	vector<Term> poly;
	size_t degree;
	bool order;  // True if ascending order, false otherwise

public:
	Polynomial(int multiplier = 0);
	Polynomial(Term& term);
	Polynomial(const Polynomial& other);

	void operator=(const Polynomial& other);
	void operator+=(const Polynomial& other);
	void operator*=(const Polynomial& other);

	friend Polynomial operator+(const Polynomial& first, const Polynomial& second);
	friend Polynomial operator*(const Polynomial& first, const Polynomial& second);
	friend istream& operator>>(istream& stream, Polynomial& polynomial);
	friend ostream& operator<<(ostream& stream, const Polynomial& polynomial);
};