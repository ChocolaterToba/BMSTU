#include "massive_manip.h"

void copy_massive(char* original, char* result, int start, int end) // Копирование элементов char из массива original[start:end] в массив result.
{
	int i;
	for (i = start; i < end; i++)
	{
		result[i - start] = original[i];
	}
}
