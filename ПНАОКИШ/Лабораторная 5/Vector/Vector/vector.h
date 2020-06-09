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

	char* operator[] (size_t);
	void operator= (MyVector);

	size_t Size();
	size_t Maxsize();

protected:
	size_t maxsize;
	size_t size;
	char** pdata;

private:
    void resize();
};

void qsort(char**, size_t, size_t);
void swap(char*&, char*&);

char** copy_data(char**, size_t, size_t);

#endif  //  VECTOR_H
