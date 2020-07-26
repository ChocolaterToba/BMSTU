#include "pch.h"
#include "framework.h"

#include <cstring>

#include "MySet.h"

const int WORD_LEN = 200;

ostream& operator<<(ostream& out, MySet& set) {
	for (int i = 0; i < set.size; i++) {
		out << set[i] << " ";
	}
	out << endl;
	return out;
}

MySet operator+(MySet& first, MySet& second) {
	MySet newSet = first;
	for (int i = 0; i < second.size; i++) {
		newSet.add_element(second[i]);
	}
	return newSet;
}

MySet operator-(MySet& first, MySet& second) {
	MySet newSet = first;
	for (int i = 0; i < second.size; i++) {
		newSet.delete_element(second[i]);
	}
	return newSet;
}

MySet operator*(MySet& first, MySet& second) {
	MySet newSet;
	for (int i = 0; i < first.size; i++) {
		if (second.is_element(first[i])) {
			newSet.add_element(first[i]);
		}
	}
	return newSet;
}

bool MySet::operator==(MySet& set) {
	if (size != set.size) {
		return false;
	}

	for (int i = 0; i < size; i++) {
		if (!set.is_element((*this)[i])) {
			return false;
		}
	}
	return true;
}

MySet& MySet::operator+=(MySet& set) {
	for (int i = 0; i < set.size; i++) {
		add_element(set[i]);
	}
	return *this;
}

MySet& MySet::operator-=(MySet& set) {
	for (int i = 0; i < set.size; i++) {
		delete_element(set[i]);
	}
	return *this;
}

MySet& MySet::operator*=(MySet& set) {
	for (int i = 0; i < set.size; i++) {
		if (!is_element(set[i])) {
			delete_element(set[i]);
		}
	}
	return *this;
}

void MySet::add_element(char* element) {
	if (!is_element(element)) {
		pdata[size] = new char[WORD_LEN];
		strcpy_s(pdata[size], WORD_LEN, element);
		size++;
		sort();
		resize();
	}
}

void MySet::delete_element(char* element) {
	int i = find(element);
	if (i != -1) {
		delete[] pdata[i];
		for (i; i < size - 1; i++) {
			pdata[i] = pdata[i + 1];
		}
		pdata[size - 1] = nullptr;
		size--;
		resize();
	}
}

bool MySet::is_element(char* element) {
	return (find(element) != -1);
}