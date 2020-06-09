#ifndef __FRACTION_H__
#define __FRACTION_H__
#include <iostream>

using namespace std;

class Fractions {
private:
	char* representation;
	int numerator;
	int denominator;

	void normalise();
	void update_representation();

public:
	Fractions(int new_numerator = 0, int new_denominator = 1);
	Fractions(char*);
	Fractions(double, int N_DEC = 4);
	~Fractions();

	void change_numden(int, int);
	void change_representation(char*);

	friend ostream& operator<< (ostream&, const Fractions&);
	friend istream& operator>> (istream&, Fractions&);
	void operator= (const Fractions&);

	Fractions operator+(Fractions&);
	Fractions operator+(double);
	Fractions operator+(int);
	friend Fractions operator+(double, Fractions&);
	friend Fractions operator+(int, Fractions&);
	void operator+=(Fractions&);
	void operator+=(double);
	void operator+=(int);
	friend void operator+=(double&, Fractions&);
	friend void operator+=(int&, Fractions&);
};

int chars_to_int(char*, int, int);
char* ints_to_char(char*, int);
char* cut(char*);
int greatest_common_factor(int, int);
double round(double);

#endif //__FRACTION_H__