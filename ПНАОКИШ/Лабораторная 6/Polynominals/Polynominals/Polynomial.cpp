#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Polynomial.h"

Polynomial::Polynomial(int multiplier) {
	poly.resize(1);
	poly[0].multiplier = multiplier;
	degree = 0;
	order = true;
}

Polynomial::Polynomial(Term& term) {
	poly.resize(term.power + 1);
	poly[term.power] = term;
	for (size_t i = 1; i <= term.power; ++i) {
		poly[i].power = i;
	}
	degree = term.power;
	order = true;
}

Polynomial::Polynomial(const Polynomial& other) {
	poly = other.poly;  // That copies poly, but resulting poly is entirely separate.
	degree = other.degree;
	order = other.order;
}

void Polynomial::operator=(const Polynomial& other) {
	poly = other.poly;  // That copies poly, but resulting poly is entirely separate.
	degree = other.degree;
	order = other.order;
}

void Polynomial::operator+=(const Polynomial& other) {
	size_t new_degree = max(degree, other.degree);
	vector<Term> new_poly(new_degree + 1);
	for (size_t i = 0; i <= new_degree; ++i) {
		new_poly[i].power = i;
	}

	if (other.order) {
		for (size_t i = 0; i <= other.degree; ++i) {
			new_poly[i] = other.poly[i];
		}
	}
	else {
		for (size_t i = 0; i <= other.degree; ++i) {
			new_poly[i] = other.poly[other.degree - i];
		}
	}

	if (order) {
		for (size_t i = 0; i <= degree; ++i) {
			new_poly[i].multiplier += poly[i].multiplier;
		}
	}
	else {
		for (size_t i = 0; i <= degree; ++i) {
			new_poly[i].multiplier += poly[degree - i].multiplier;
		}
		reverse(new_poly.begin(), new_poly.end());
	}
	

	poly = new_poly;
	degree = new_degree;
}

void Polynomial::operator*=(const Polynomial& other) {
	vector<Term> new_poly(degree + other.degree + 1);
	for (size_t i = 0; i <= degree + other.degree; ++i) {
		new_poly[i].power = i;
	}

	if (order) {
		if (other.order) {
			for (size_t i = 0; i <= degree; ++i) {
				for (size_t j = 0; j <= other.degree; ++j) {
					new_poly[i + j].multiplier += poly[i].multiplier * other.poly[j].multiplier;
				}
			}
		}
		else {
			for (size_t i = 0; i <= degree; ++i) {
				for (size_t j = 0; j <= other.degree; ++j) {
					new_poly[i + j].multiplier += poly[i].multiplier * other.poly[other.degree - j].multiplier;
				}
			}
		}
	}
	else {
		if (other.order) {
			for (size_t i = 0; i <= degree; ++i) {
				for (size_t j = 0; j <= other.degree; ++j) {
					new_poly[i + j].multiplier += poly[degree - i].multiplier * other.poly[j].multiplier;
				}
			}
		}
		else {
			for (size_t i = 0; i <= degree; ++i) {
				for (size_t j = 0; j <= other.degree; ++j) {
					new_poly[i + j].multiplier += poly[degree - i].multiplier * other.poly[other.degree - j].multiplier;
				}
			}
		}
		reverse(new_poly.begin(), new_poly.end());
	}
	poly = new_poly;
	degree += other.degree;
}

Polynomial operator+(const Polynomial& first, const Polynomial& second) {
	Polynomial result(first);
	result += second;
	return result;
}

Polynomial operator*(const Polynomial& first, const Polynomial& second) {
	Polynomial result(first);
	result *= second;
	return result;
}

istream& operator>>(istream& stream, Polynomial& polynomial) {
	string poly_string;
	getline(stream, poly_string);
	poly_string.erase(remove(poly_string.begin(), poly_string.end(), ' '), poly_string.end());

	polynomial.poly.resize(1);
	polynomial.poly[0].multiplier = 0;
	polynomial.degree = 0;
	polynomial.order = true;
	while (!poly_string.empty()) {
		bool negative_term = false;
		if (poly_string[0] == '-') {
			negative_term = true;
			poly_string.erase(0, 1);
		}

		size_t plus_pos = poly_string.find('+');
		size_t minus_pos = poly_string.find('-');

		Term term;
		if (plus_pos < minus_pos) {
			string term_string = poly_string.substr(0, plus_pos);
			poly_string.erase(0, plus_pos + 1);

			if (term_string[0] == '(') {
				// Removing brackets.Backwards one is at the end, so we delete it first (it's faster).
				term_string.erase(term_string.length() - 1);
				term_string.erase(0);
			}

			term = Term(term_string);
		}
		else if (plus_pos > minus_pos) {
			string term_string = poly_string.substr(0, minus_pos);
			poly_string.erase(0, minus_pos);

			term = Term(term_string);
		}
		else {  // In that case, there are no pluses or minuses - we have our last term.
			term = Term(poly_string);
			poly_string = "";
		}
		
		if (negative_term) {
			term.multiplier *= -1;
		}

		polynomial += Polynomial(term);
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Polynomial& polynomial) {
	bool first_term = true;
	vector<Term> new_poly = polynomial.poly;
	if (polynomial.order) {
		reverse(new_poly.begin(), new_poly.end());
	}
	if (polynomial.degree) {
		if (new_poly[0].multiplier) {
			if (new_poly[0].multiplier > 0) {
				stream << new_poly[0] << ' ';
			}
			else {
				stream << "- " << Term(-new_poly[0].multiplier, new_poly[0].power) << ' ';
			}
		}
		for (size_t i = 1; i < polynomial.degree; ++i) {
			if (new_poly[i].multiplier > 0) {
				stream << "+ " << new_poly[i] << ' ';
			}
			else if (new_poly[i].multiplier < 0) {
				stream << "- " << Term(-new_poly[i].multiplier, new_poly[i].power) << ' ';
			}
		}
	}
	else {
		stream << '0';
	}

	return stream;
}