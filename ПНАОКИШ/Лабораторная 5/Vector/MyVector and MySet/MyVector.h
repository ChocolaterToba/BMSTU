#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

const int MAX_SIZE = 5;
class MyVector {
public:
    MyVector(char* element = nullptr, int maxsize = MAX_SIZE);
	MyVector(const MyVector& vector);
	~MyVector();

	void add_element(char* element);
	void delete_element(int i);
	int find(char* element);

	void sort();

	char* operator[](int index);
	void operator=(MyVector source);
	friend ostream& operator<<(ostream& out, MyVector& vector);

	int Size();
	int Maxsize();

protected:
	int maxsize;
	int size;
	char** pdata;

    void resize();
};

void qsort(char**, int, int);
void swap(char*&, char*&);

char** copy_data(char**, int, int);

#endif  //  VECTOR_H
