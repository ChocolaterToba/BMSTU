#ifndef __MASSIVE_MANIP_H__
#define __MASSIVE_MANIP_H__

void copy_massive(char*, char*, int, int);
template <class T>
T* change_length(T* original, int size, int change) // Изменение длины массива элементов класса T.
{
	T* result = new T[size + change];
	int i;
	for (i = 0; i < size && i < size + change; i++)
	{
		result[i] = original[i];
	}
	delete[] original;
	return result;
}

#endif //__MASSIVE_MANIP_H__