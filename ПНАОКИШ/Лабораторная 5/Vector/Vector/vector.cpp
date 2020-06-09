#include <cstring>
#include <algorithm>
#include <iostream>

#include "vector.h"

using namespace std;

const size_t WORD_LEN = 200;
const size_t DEFAULT_SIZE = 8;

MyVector::MyVector(char* element) {
	maxsize = DEFAULT_SIZE;
	size = 1;
	pdata = new char*[maxsize];
	for (size_t i = 0; i < maxsize; i++) {
		pdata[i] = nullptr;
	}
	pdata[0] = new char[WORD_LEN];
	strcpy_s(pdata[0], WORD_LEN, element);
}

MyVector::MyVector(const MyVector& vector) {
	maxsize = vector.maxsize;
	size = vector.size;
	pdata = new char*[maxsize];
	for (size_t i = 0; i < size; i++) {
		pdata[i] = new char[WORD_LEN];
		strcpy_s(pdata[i], WORD_LEN, vector.pdata[i]);
	}
}

MyVector::~MyVector() {
	size_t i = 0;
	while (i < size && pdata[i] != nullptr) {
		delete[] pdata[i];
		pdata[i] = nullptr;
		i++;
	}
	pdata = nullptr;
}

void MyVector::resize() {
	if (size == maxsize) {
		maxsize = maxsize * 3 / 2;
		pdata = copy_data(pdata, maxsize, size);
	}
	else if (size < maxsize / 2) {
		if (maxsize * 2 / 3 > DEFAULT_SIZE) {
			maxsize = maxsize * 2 / 3;
			pdata = copy_data(pdata, maxsize, size);
		}
	}
}


void MyVector::add_element(char* element) {
	pdata[size] = new char[WORD_LEN];
	strcpy_s(pdata[size], WORD_LEN, element);
	size++;
	sort();
	resize();
}

void MyVector::delete_element(char* element) {
	size_t i = find(element);
	if (i != -1) {
		delete[] pdata[i];
		for (i; i < size - 1; i++) {
			pdata[i] = pdata[i + 1];
		}
		pdata[size - 1] = nullptr;
		size--;
		resize();
		cout << "Successfully deleted an element" << endl;
	}
	cout << endl;
}

int MyVector::find(char* element) {
	for(size_t i = 0; i < size; i++) {
		if (strcmp(pdata[i], element) == 0) {
			return i;
		}
	}
	cout << "That element was not found" << endl;
	return -1;
}

void MyVector::sort() {
	qsort(pdata, 0, size - 1);
}

char* MyVector::operator[] (size_t i) {
	if (i < size) {
		return pdata[i];
	}
	cout << "Index Error" << endl << endl;
	return nullptr;
}

void MyVector::operator= (MyVector source) {
	maxsize = source.maxsize;
	size = source.size;
	pdata = new char*[maxsize];
	for (size_t i = 0; i < size; i++) {
		pdata[i] = new char[WORD_LEN];
		strcpy_s(pdata[i], size, source.pdata[i]);
	}
}

size_t MyVector::Size() {
	return size;
}
size_t MyVector::Maxsize() {
	return maxsize;
}

void qsort(char** arr, size_t start, size_t end) { // Quick sort from start to end including both.
	char** pivot = arr + end; // Element to be placed at the right position
	size_t i = start, j;
	for (j = start; j < end; j++) {
		if (strcmp(arr[j], *pivot) < 0) {
			swap(arr[i], arr[j]);
			++i;
		}
	}
	swap(arr[i], arr[end]);
	if (i - 1 > start) {
		qsort(arr, start, i - 1); // Sorting "less than pivot" and "more than pivot" arrays.
	}
	if (end > i + 1) {
	    qsort(arr, i + 1, end);
	}
}

void swap(char*& first, char*& second) {
	char* temp = first;
	first = second;
	second = first;
}

char** copy_data(char** source, size_t length, size_t source_length) {
	char** result = new char*[length];
	for (size_t i = 0; i < length; i++) {
		result[i] = nullptr;
	}
	size_t i = 0;
	while (i < min(length, source_length)) {
		result[i] = new char[WORD_LEN];
		strcpy_s(result[i], WORD_LEN, source[i]);
		i++;
	}
	return result;
}
