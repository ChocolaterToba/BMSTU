#ifndef VECTOR_H
#define VECTOR_H

const int MAX_SIZE = 5;
class MyVector {
public:
    MyVector(char* element = nullptr, int maxsize = MAX_SIZE);
	MyVector(const MyVector& vector);
	~MyVector();

	void add_element(char* element);
	void delete_element(char* element);
	int find(char* element);

	void sort();

	char* operator[] (int index);
	void operator= (MyVector source);

	int Size();
	int Maxsize();

protected:
	int maxsize;
	int size;
	char** pdata;

private:
    void resize();
};

void qsort(char**, int, int);
void swap(char*&, char*&);

char** copy_data(char**, int, int);

#endif  //  VECTOR_H
