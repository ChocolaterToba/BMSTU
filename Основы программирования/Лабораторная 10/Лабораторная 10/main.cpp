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
		case 1: // Добавление слов в словарь.
			add_word(dict, n);
			break;
		case 2: // Удаление слов из словаря.
			delete_word(dict, n);
			break;
		case 3: // Перевод с английского на русский.
			eng_to_rus(dict, n);
			break;
		case 4: // Перевод с русского на английский.
			rus_to_eng(dict, n);
			break;
		case 5: // Просмотр словаря.
			print_dict(dict, n);
			break;
		case 6: // Вывод словаря в файл.
			write_dict(dict, n, (char*) "out_dict.txt");
			break;
		case 7: // Выход.
			return 1;
		default: // Неверный ввод.
			cout << "Надо вводить число от 1 до 7" << endl;
			cin.clear(); // Очистка потока ввода от флага ошибки.
			cin.ignore(80, '\n'); // Очистка потока ввода от неверных данных.
			break;
		}
		cout << endl;
	}
}

int menu()
{
	int answer;
	cout << "1) Добавление слов в словарь." << endl;
	cout << "2) Удаление слов из словаря." << endl;
	cout << "3) Перевод с английского на русский." << endl;
	cout << "4) Перевод с русского на английский." << endl;
	cout << "5) Просмотр словаря." << endl;
	cout << "6) Вывод словаря в файл." << endl;
	cout << "7) Выход." << endl;
	cin >> answer;
	return answer;
}