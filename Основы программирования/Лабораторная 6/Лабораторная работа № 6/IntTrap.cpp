#include "functions.h"
#include "IntTrap.h"

double IntTrap(double func(double), double a, double b, double eps, int& amount)
{
	double old_sum = (b - a) * (func(a) + func(b)) / 2;
	double new_sum = (b - a) * (func(a) + 2 * func((a + b) / 2) + func(b)) / 4;
	double delta_x;
	amount = 2;
	while (abs(new_sum - old_sum) >= eps * 3)
	{
		old_sum = new_sum;
		new_sum = 0;
		amount *= 2;
		delta_x = (b - a) / amount;
		for (int i = 0; i < amount; i++)
		{
			new_sum += func(a + delta_x * i) + func(a + delta_x * (i + 1));
		}
		new_sum *= delta_x / 2;
	}
	return new_sum;
}