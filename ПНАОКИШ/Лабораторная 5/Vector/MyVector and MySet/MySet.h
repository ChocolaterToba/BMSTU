#ifndef MYSET_H
#define MYSET_H

#include <iostream>
#include "MyVector.h"


using namespace std;

class MySet :public MyVector
{
public:
	MySet(char* el = NULL) :MyVector(el) {};

	friend ostream& operator<<(ostream& out, MySet& s);
	friend MySet operator+(MySet& s1, MySet& s2);
	friend MySet operator-(MySet& s1, MySet& s2);
	friend MySet operator*(MySet& s1, MySet& s2);

	bool operator==(MySet& s);
	MySet& operator+=(MySet& s);
	MySet& operator-=(MySet& s);
	MySet& operator*=(MySet& s);
	void add_element(char* el);
	void delete_element(char* el);
	bool is_element(char* el);
};

#endif  // MYSET_H
