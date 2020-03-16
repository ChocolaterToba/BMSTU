#include "functions.h"
#include "IntRect.h"

double IntRect(double func(double), double a, double b, double eps, int& amount)
{
	double delta_x;
	double old_sum = (b - a) * func((a + b) / 2);
	double new_sum = (b - a) / 2 * (func((a + b) / 4) + func((a + b) * 3 / 4));
	amount = 2;
	while (abs(new_sum - old_sum) >= eps * 3)
	{
		old_sum = new_sum;
		new_sum = 0;
		amount *= 2;
		delta_x = (b - a) / amount;
		for (int i = 0; i < amount; i++)
		{
			new_sum += func(a + delta_x * (i + 0.5));
		}
		new_sum *= delta_x;
	}
	return new_sum;
}