#include "pch.h"
#include "framework.h"

#include <cstring>
#include <algorithm>
#include <iostream>

#include "MyVector.h"

using namespace std;

const int WORD_LEN = 200;
const int DEFAULT_SIZE = 5;

MyVector::MyVector(char* element, int maxsize) {
	this->maxsize = maxsize;
	pdata = new char* [maxsize];
	if (element == nullptr) {
		size = 0;
	}
	else {
		size = 1;
		pdata[0] = new char[WORD_LEN];
		strcpy_s(pdata[0], WORD_LEN, element);
	}
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
		delete[] pdata[i];
		i++;
	}
	delete[] pdata;
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
	int min = 0;
	int max = size - 1;
	int comparison = strcmp(pdata[(max + min) / 2], element);
	while (comparison != 0) {
		if (max == min) {
			cout << "That element was not found" << endl;
			return -1;
		}
		if (comparison > 0) {
			max = (max + min) / 2 - 1;
		}
		else {
			min = (max + min) / 2 + 1;
		}
		comparison = strcmp(pdata[(max + min) / 2], element);
	}
	cout << (max + min) / 2;
	return 0;
}

void MyVector::sort() {
	qsort(pdata, 0, size - 1);
}

char* MyVector::operator[] (int index) {
	if (index >= 0 || index < size) {
		return pdata[index];
	}
	cout << "Index Error" << endl;
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
		if (strcmp(arr[j], *pivot) < 0) {
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
	second = temp;
}

char** copy_data(char** source, int length, int source_length) {
	char** result = new char*[length];
	for (int i = 0; i < length; i++) {
		result[i] = nullptr;
	}
	int i = 0;
	while (i < min(length, source_length)) {
		result[i] = new char[WORD_LEN];
		strcpy_s(result[i], WORD_LEN, source[i]);
		i++;
	}
	return result;
}
