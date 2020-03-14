#include "fraction.h"

ostream& operator<< (ostream& out, const Fractions& fraction) {
	return out << fraction.representation << endl;
}
istream& operator>> (istream& in, Fractions& fraction) {
	const int fraction_len = 100;
	char result[fraction_len];
	in.getline(result, strlen(result));
	fraction.change_representation(result);
	return in;
}

void Fractions::operator=(const Fractions& fraction_to_copy) {
	numerator = fraction_to_copy.numerator;
	denominator = fraction_to_copy.denominator;
	delete[] representation;
	representation = cut(fraction_to_copy.representation);
}

Fractions Fractions::operator+(Fractions& term) {
	return Fractions(term.denominator * numerator + denominator * term.numerator,
		             denominator * term.denominator);
}
Fractions Fractions::operator+(double term) {
	Fractions result(term);
	return *this + result;
}
Fractions Fractions::operator+(int term) {
	Fractions result(term);
	return *this + result;
}
Fractions operator+(double first_term, Fractions& second_term) {
	Fractions result(first_term);
	return result + second_term;
}
Fractions operator+(int first_term, Fractions& second_term) {
	Fractions result(first_term);
	return result + second_term;
}

void Fractions::operator+=(Fractions& term) {
	*this = *this + term;
}
void Fractions::operator+=(double term) {
	Fractions result(term);
	*this = *this + result;
}
void Fractions::operator+=(int term) {
	Fractions result(term);
	*this = *this + result;
}
void operator+=(double &first_term, Fractions& second_term) {
	double result = round((double) second_term.numerator / second_term.denominator * pow(10, 4)) / pow(10, 4);
	first_term += result;
}
void operator+=(int &first_term, Fractions& second_term) {
	first_term += second_term.denominator / second_term.denominator;
}