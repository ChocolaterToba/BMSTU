#include "massive_manip.h"

void copy_massive(char* original, char* result, int start, int end) // ����������� ��������� char �� ������� original[start:end] � ������ result.
{
	int i;
	for (i = start; i < end; i++)
	{
		result[i - start] = original[i];
	}
}
