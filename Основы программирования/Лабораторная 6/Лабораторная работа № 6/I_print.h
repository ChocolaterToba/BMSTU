#ifndef __I_print_H__
#define __I_print_H__

#include <iostream>
#include <iomanip>

struct I_print {	//������ ��� ������ ����������� ��������������
	const char* name;//�������� �������
	double i_sum;	//�������� ������������ �����
	double i_toch;	//������ �������� ���������
	int n;	//����� ��������� ������� �������������� 
			//��� ������� ���������� ��������� ��������
};

void PrintTabl(I_print[], int);

#endif //__I_print_H__