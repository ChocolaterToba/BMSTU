#include <cmath>
#include "fraction.h"

Fractions::Fractions(int new_numerator, int new_denominator) {
	representation = cut("1");
	denominator = 1;
	change_numden(new_numerator, new_denominator);
}
Fractions::Fractions(char* new_representation) {
	representation = cut("1");
	numerator = 1; denominator = 1;
	change_representation(new_representation);
}
Fractions::Fractions(double new_double, int N_DEC) {
	representation = cut("1");
	numerator = round(new_double * pow(10, N_DEC));
	denominator = pow(10, N_DEC);
	normalise();
	update_representation();
}

Fractions::~Fractions() {
	if (representation == nullptr) {
        delete[] representation;
	}
}

void Fractions::change_numden(int new_numerator, int new_denominator) {
	numerator = new_numerator;
	if (denominator) {
		denominator = new_denominator;
	}
	else {
		cout << "Denominator can't be 0! Leaving denominator as it is (1 by default)." << endl;
	}
	normalise();
	update_representation();
}

void Fractions::change_representation(char* new_representation) {
	int space_pos = -1;
	int slash_pos = -1;
	int i, whole = 0, new_numerator = 0, new_denominator = 1;
	char character = ' ';
	bool negative = false;

	if (new_representation[0] == '-') {
		negative = true;
		new_representation++;
	}

	for (i = 0; new_representation[i]; i++) { // Checking for disallowed symbols.
		character = new_representation[i];
		if ((character != ' ') && (character < '/' || character > '9')) {
			cout << "Disallowed symbols! Representation remains unchanged ('1' by default)." << endl;
			return;
		}
	}
	if (new_representation[0] == ' ' || character == ' ' ||
		new_representation[0] == '/' || character == '/') {
		cout << "Error when parsing end of representation! Representation remains unchanged ('1' by default)." << endl;
		return;
	}

	for (i = 1; i < strlen(new_representation); i++) {  // Finding where space(s) and slash(es) are.
		if (new_representation[i] == ' ') {
			if (space_pos != -1) {
				cout << "There can't be 2 spaces! Representation remains unchanged ('1' by default)." << endl;
				return;
			}
			space_pos = i;
		}
		else if (new_representation[i] == '/') {
			if (slash_pos != -1) {
				cout << "There can't be 2 slashes! Representation remains unchanged ('1' by default)." << endl;
				return;
			}
			slash_pos = i;
		}
	}

	if (space_pos != -1) { // In this case we have both whole part and a fraction.
		if (slash_pos < space_pos) {
			cout << "Something is wrong with slash! Representation remains unchanged ('1' by default)." << endl;
			return;
		}
		whole = chars_to_int(new_representation, 0, space_pos - 1);
		new_numerator = chars_to_int(new_representation, space_pos + 1, slash_pos - 1);
		new_denominator = chars_to_int(new_representation, slash_pos + 1, strlen(new_representation) - 1);
	}
	else {
		if (slash_pos != -1) { // Only fraction.
			new_numerator = chars_to_int(new_representation, 0, slash_pos - 1);
			new_denominator = chars_to_int(new_representation, slash_pos + 1, strlen(new_representation) - 1);
		}
		else { // Only whole part.
			whole = chars_to_int(new_representation, 0, strlen(new_representation) - 1);
		}
	}

	if (!new_denominator) {
		cout << "Denominator can't be 0! Representation remains unchanged ('1' by default)." << endl;
		return;
	}

	denominator = new_denominator;
	numerator = new_numerator + whole * denominator;

	if (negative) {
		numerator *= -1;
	}
	normalise();
	update_representation();
}

void Fractions::update_representation() {
	int whole;
	int repr_numerator;
	char new_repr[100];
	char* p_new_repr = new_repr;
	if (numerator) {
		whole = abs(numerator) / denominator;
		repr_numerator = abs(numerator) % denominator;
		if (numerator < 0) {
			new_repr[0] = '-';
			p_new_repr++;
		}

		if (whole) {
			p_new_repr = ints_to_char(p_new_repr, whole);
			p_new_repr[0] = ' ';
			p_new_repr[1] = '\0';
			p_new_repr++;
		}

		if (repr_numerator) {
			p_new_repr = ints_to_char(p_new_repr, repr_numerator);
			p_new_repr[0] = '/';
			p_new_repr++;
			ints_to_char(p_new_repr, denominator);
		}
	}
	else {
		new_repr[0] = '0';
		new_repr[1] = '\0';
	}
	delete[] representation;
	representation = cut(new_repr);
}

void Fractions::normalise() {
	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}
	int gcf = greatest_common_factor(abs(numerator), denominator); // Denominator is already bigger than 0, numerator is not guaranteed to be.
	numerator /= gcf;
	denominator /= gcf;
}

int chars_to_int(char* input, int start, int end) { // Turn input from start to end inclusive into integer.
	int output;
	int i;
	for (i = start; i < end && input[i] - '0' == 0; i++); // Get index of first non-0 char or end, if all of the chars before ending one are 0.
	output = (input[i] - '0');
	i++;
	for (i; i <= end; i++) {
		output = output * 10 + (input[i] - '0');
	}
	return output;
}
char* ints_to_char(char* output, int input) {  // Turn int into char* and return pointer to '\0' character of that char*.
	int i, shift, as_numbers[100];
	if (input != 0) {
		for (i = 0; input; i++) {
			as_numbers[i] = input % 10;
			input /= 10;
		}
	}
	else {
		i = 1;
		as_numbers[0] = 0;
	}
	shift = i;
	output[i] = '\0';
	i--;
	for (i; i >= 0; i--) {
		output[shift - 1 - i] = as_numbers[i] + '0';
	}
	return output + shift;
}

char* cut(char* inp) {
	char* result = new char[strlen(inp) + 1];
	int i;
	for (i = 0; inp[i]; i++) {
		result[i] = inp[i];
	}
	result[i] = inp[i];
	return result;
}

int greatest_common_factor(int first, int second) {  // Euclid's algorythm.
	if (first == second || !second) {
		return first;
	}
	return greatest_common_factor(second, first % second);
}

double round(double x) {
	return floor(x + 0.5);
}