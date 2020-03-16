#ifndef __I_print_H__
#define __I_print_H__

#include <iostream>
#include <iomanip>

struct I_print {	//данные для печати результатов интегрирования
	const char* name;//название функции
	double i_sum;	//значение интегральной суммы
	double i_toch;	//точное значение интеграла
	int n;	//число разбиений области интегрирования 
			//при котором достигнута требуемая точность
};

void PrintTabl(I_print[], int);

#endif //__I_print_H__