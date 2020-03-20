#ifndef VECTOR_H
#define VECTOR_H

class MyVector {
public:
    MyVector(char* element = (char*) "a");
	MyVector(const MyVector&);
	~MyVector();

	void add_element(char* element);
	void delete_element(char* element);
	int find(char* element);

	void sort();

	char* operator[] (int);
	void operator= (MyVector);

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
