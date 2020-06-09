#include "Term.h"
#include <string>

using namespace std;

Term::Term(int multiplier, int power) {
	this->multiplier = multiplier;
	this->power = power;
}

Term::Term(string& line) {
	this->multiplier = 0;  // Default multiplier and power values.
	this->power = 0;

	size_t multiplier_end = 0;
	if (line.length()) {
		if (line[0] == '-') {
			++multiplier_end;  // This fixes bug occuring when reading negative terms.
		}
	}

	for (multiplier_end; multiplier_end < line.length(); ++multiplier_end) {
		if (!isdigit(line[multiplier_end])) {
			break;
		}
	}

	if (!multiplier_end) {
		if (line[0] == 'x') {
			this->multiplier = 1;
			if (line == "x") {
				this->power = 1;
				return;
			}
		}
		else {
			cerr << "Error: bad format" << endl;
			return;
		}
	}
	else if (multiplier_end == line.length()) {
		this->multiplier = stoi(line);
		return;
	}
	else if (multiplier_end > line.length() - 2) {
		if (multiplier_end == line.length() - 1 && line[multiplier_end] == 'x') {
			string multiplier(line, 0, multiplier_end);
			this->multiplier = stoi(multiplier);
			this->power = 1;
			return;
		}
		cerr << "Error: bad format" << endl;
		return;
	}
	else if (line[multiplier_end] != 'x' || line[multiplier_end + 1] != '^') {
		cerr << "Error: bad format" << endl;
		return;
	}
	else {
		string multiplier(line, 0, multiplier_end);
		this->multiplier = stoi(multiplier);
	}

	size_t power_ind = multiplier_end + 2;
	for (power_ind; power_ind < line.length(); ++power_ind) {
		if (!isdigit(line[power_ind])) {
			cerr << "Error: bad format" << endl;
			return;
		}
	}

	string power(line, multiplier_end + 2, string::npos);
	this->power = stoi(power);
}

Term operator+(const Term& first, const Term& second) {
	Term result;
	if (first.power != second.power) {
		return result;
	}
	result.multiplier = first.multiplier + second.multiplier;
	result.power = first.power;
	return result;
}

istream& operator>>(istream& stream, Term& term) {
	string line;
	stream >> line;

	term = Term(line);
	return stream;
}

ostream& operator<<(ostream& stream, const Term& term) {
    if (!term.power) {
		stream << term.multiplier;
		return stream;
	}
	
	switch (term.multiplier) {
	case 1:
		break;
	case 0:
		stream << 0;
		return stream;
	case -1:
		stream << '-';
		break;
	default:
		stream << term.multiplier;
		break;
	}

	stream << 'x';
	if (term.power != 1) {
		stream << '^' << term.power;
	}
	return stream;
}
