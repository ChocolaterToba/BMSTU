#include <iostream>
#include <Windows.h>

#include "..\Vector\vector.h"
#include "check.h"

using namespace std;

const size_t WORD_LEN = 200;

int main() {
	MyVector vector = MyVector("first");
	vector.add_element("second");
	cout << "Initial vector:" << endl;
	for (size_t i = 0; i < vector.Size(); ++i) {
		cout << vector[i] << endl;
	}

	cout << "Enter the third string that you want to add:" << endl;
	char word[WORD_LEN];
	cin.getline(word, WORD_LEN);
	vector.add_element(word);
	cout << "Resulting vector:" << endl;
	for (size_t i = 0; i < vector.Size(); ++i) {
		cout << vector[i] << endl;
	}

	cout << "And this is what we get by deleting second string:" << endl;
	vector.delete_element("second");
	for (size_t i = 0; i < vector.Size(); ++i) {
		cout << vector[i] << endl;
	}
	system("pause");
	return 1;
}