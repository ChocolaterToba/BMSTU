#include <cstring>
#include <algorithm>
#include <iostream>

#include "vector.h"

using namespace std;

const int WORD_LEN = 80;
const int DEFAULT_SIZE = 8;

MyVector::MyVector(char* element) {
	maxsize = DEFAULT_SIZE;
	size = 1;
	pdata = new char*[maxsize];
	pdata[0] = new char[WORD_LEN];
	strcpy_s(pdata[0], WORD_LEN, element);
}

MyVector::MyVector(const MyVector& vector) {
	maxsize = vector.maxsize;
	size = vector.size;
	pdata = new char*[maxsize];
	for (int i = 0; i < size; i++) {
		pdata[i] = new char[WORD_LEN];
		strcpy_s(pdata[i], WORD_LEN, vector.pdata[i]);
	}
}

MyVector::~MyVector() {
	for (int i = 0; i < size; i++) {
		if (pdata[i] != nullptr) {
			delete[] pdata[i];
		}
	}
	pdata = nullptr;
}

void MyVector::resize() {
	if (size == maxsize) {
		maxsize *= 1.5;
		pdata = copy_data(pdata, maxsize);
	}
	else if (size < maxsize / 2) {
		maxsize = max(maxsize * 2 / 3, DEFAULT_SIZE);
		pdata = copy_data(pdata, maxsize);
	}
}


void MyVector::add_element(char* element) {
	strcpy_s(pdata[size], WORD_LEN, element);
	size++;
	sort();
	resize();
}

void MyVector::delete_element(char* element) {
	int i = find(element);
	if (i != -1) {
		delete[] pdata[i];
		for (i; i < size - 1; i++) {
			pdata[i] = pdata[i + 1];
		}
		pdata[size - 1] = nullptr;
		size--;
		resize();
		cout << "Удаление произошло успешно" << endl;
	}
	cout << endl;
}

int MyVector::find(char* element) {
	for(int i = 0; i < size; i++) {
		if (strcpy_s(pdata[i], size, element) == 0) {
			return i;
		}
	}
	cout << "That element was not found" << endl;
	return -1;
}

void MyVector::sort() {
	qsort(pdata, 0, size - 1);
}

char* MyVector::operator[] (int i) {
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
	for (int i = 0; i < size; i++) {
		pdata[i] = new char[WORD_LEN];
		strcpy_s(pdata[i], size, source.pdata[i]);
	}
}

int MyVector::Size() {
	return size;
}
int MyVector::Maxsize() {
	return maxsize;
}

void qsort(char** arr, int start, int end) { // Quick sort from start to end including both.
	char** pivot = arr + end; // Element to be placed at the right position
	int i = start - 1, j;
	for (j = start; j < end; j++) {
		if (strcpy_s(arr[j], WORD_LEN, *pivot) < 0) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[end]);
	if (i > start) {
		qsort(arr, start, i); // Sorting "less than pivot" and "more than pivot" arrays.
	}
	if (end > i + 2) {
	    qsort(arr, i + 2, end);
	}
}

void swap(char*& first, char*& second) {
	char* temp = first;
	first = second;
	second = first;
}

char** copy_data(char** source, int length) {
	char** result = new char*[length];
	int i = 0;
	while (source[i] != nullptr) {
		result[i] = source[i];
		i++;
	}
	return result;
}
