#include "main.h"
#include "IntRect.h"
#include "IntTrap.h"
#include "functions.h"
#include "I_print.h"

using namespace std;

int main()
{
	double a; // ������ ������ ��������������.
	double b; // ������� ������ ��������������.
	double precision; // ��������, � ������� ���������� ������� ��������.
	int n; // ���-�� ��������, �� ������� ����������� ����������� ������� ��� ��������������.
	I_print i_prn[4]; // ������ ��������, � ������� �������� ���������� � ����������� ����������.
	double (*functions[4]) (double) = { line, sinus, parabola, arctangens }; // ������ � �������� �� �������.
	int i, counter; // ���������� - ��������.
	char answer; // ���������� ��� ������������ ���������.

	i_prn[0].name = "y=x ";
	i_prn[1].name = "y=sin(22x)";
	i_prn[2].name = "y=x^4 ";
	i_prn[3].name = "y=arctg(x)";
	for (;;)
	{
		cout << "Input left limit a" << endl;
		cin >> a;
		cout << "Input right limit b" << endl;
		cin >> b;
		if (a > b) // �������� ������������ �������� ��������������.
		{
			cout << "a is bigger than b! Incorrect limits!" << endl << endl;
			continue;
		}
		cout << endl;
		i_prn[0].i_toch = (b * b - a * a) / 2; // ���������� i_prn ������� ���������� ����������.
		i_prn[1].i_toch = (cos(a * 22) - cos(b * 22)) / 22;
		i_prn[2].i_toch = (pow(b, 5) - pow(a, 5)) / 5;
		i_prn[3].i_toch = b * atan(b) - a * atan(a) - (log(b * b + 1) - log(a * a + 1)) / 2;
		cout << "                         Rectangle method" << endl << endl;
		precision = 1;
		for (i = 1; i < 7; i++) // ���������� � ����� �������� ����������, ����������� ������� ���������������.
		{
			precision *= 0.1;
			cout << "              Current precision = " << precision << endl;
			for (counter = 0; counter < 4; counter++)
			{
				i_prn[counter].i_sum = IntRect(*functions[counter], a, b, precision, n);
				i_prn[counter].n = n;
			}
			PrintTabl(i_prn, 4);
		}
		cout << endl;
		cout << "                       Trapezium method" << endl << endl;
		precision = 1;
		for (i = 1; i < 7; i++) // ���������� � ����� �������� ����������, ����������� ������� ��������.
		{
			precision *= 0.1;
			cout << "              Current precision = " << precision << endl;
			for (counter = 0; counter < 4; counter++)
			{
				i_prn[counter].i_sum = IntTrap(*functions[counter], a, b, precision, n);
				i_prn[counter].n = n;
			}
			PrintTabl(i_prn, 4);
		}
		cout << "Continue? (y/n) ";
		cin >> answer;
		if (answer != 'y')
		{
			break;
		}
		cout << endl;
	}
}
