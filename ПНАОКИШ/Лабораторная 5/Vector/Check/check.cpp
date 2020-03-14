#include <iostream>

#include "vector.h"
#include "check.h"

using namespace std;

const int WORD_LEN = 80;

int main() {
	MyVector vector = MyVector("first");
	vector.add_element("second");
	cout << "Enter the string that you want to add:" << endl;
	char word[WORD_LEN];
	cin.getline(word, WORD_LEN);
}