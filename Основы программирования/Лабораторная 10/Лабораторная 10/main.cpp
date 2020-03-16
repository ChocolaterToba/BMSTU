#include "main.h"
#include "dict_manip.h"
#include <iostream>
#include "windows.h"

using namespace std;

int menu();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Dictionary dict[100];
	int n;
	if (!(read_dict(dict, (char *) "in_dict.txt", n)))
	{
		return 0;
	}
	for(;;)
	{
		switch (menu())
		{
		case 1: // ���������� ���� � �������.
			add_word(dict, n);
			break;
		case 2: // �������� ���� �� �������.
			delete_word(dict, n);
			break;
		case 3: // ������� � ����������� �� �������.
			eng_to_rus(dict, n);
			break;
		case 4: // ������� � �������� �� ����������.
			rus_to_eng(dict, n);
			break;
		case 5: // �������� �������.
			print_dict(dict, n);
			break;
		case 6: // ����� ������� � ����.
			write_dict(dict, n, (char*) "out_dict.txt");
			break;
		case 7: // �����.
			return 1;
		default: // �������� ����.
			cout << "���� ������� ����� �� 1 �� 7" << endl;
			cin.clear(); // ������� ������ ����� �� ����� ������.
			cin.ignore(80, '\n'); // ������� ������ ����� �� �������� ������.
			break;
		}
		cout << endl;
	}
}

int menu()
{
	int answer;
	cout << "1) ���������� ���� � �������." << endl;
	cout << "2) �������� ���� �� �������." << endl;
	cout << "3) ������� � ����������� �� �������." << endl;
	cout << "4) ������� � �������� �� ����������." << endl;
	cout << "5) �������� �������." << endl;
	cout << "6) ����� ������� � ����." << endl;
	cout << "7) �����." << endl;
	cin >> answer;
	return answer;
}