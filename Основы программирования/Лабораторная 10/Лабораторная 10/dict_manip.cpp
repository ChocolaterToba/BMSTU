#include "dict_manip.h"
#include "main.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

bool read_dict(Dictionary* dict, char* name, int& i)
{
	ifstream infile(name);
	if (!infile) // Проверка на наличие ошибок во входном потоке.
	{
		cout << "Error when opening input file!" << endl;
		system("pause");
		return false;
	}
	char line[31];
	for(i = 0; infile.getline(line, 31); i++)
	{
		if (!strlen(line))
		{
			break;
		}
		if (i % 2) // Если номер строки (начиная с 0) нечётный - слово русское.
		{
			dict[i / 2].rus = cut(line);
		}
		else // Если номер строки (начиная с 0) чётный - слово английское.
		{
			dict[i / 2].eng = cut(line);
		}
	}
	i /= 2;
	sort_dict(dict, i); // Сортируем словарь для облегчения поиска слов в дальнейшем.
	return true;
}

void add_word(Dictionary* dict, int& n)
{
	char eng_word[31], rus_word[31];
	cout << "Введите слово по-английски: ";
	cin >> eng_word;
	cout << "Введите слово по-русски: ";
	cin >> rus_word;
	dict[n].eng = cut(eng_word); // Обрезаем лишнее.
	dict[n].rus = cut(rus_word);
	n++;
	sort_dict(dict, n); // Сортируем словарь для облегчения поиска слов в дальнейшем.
}

void delete_word(Dictionary* dict, int& n)
{
	char word[31];
	int i;
	bool found = false;
	cout << "Введите слово для удаления (на любом языке): ";
	cin >> word;
	char* cut_word = cut(word); // Обрезаем лишнее.
	for (i = 0; i < n && !found; i++) // Простой поиск перебором.
	{
		if (!(strcmp(cut_word, dict[i].eng) & strcmp(cut_word, dict[i].rus)))
		{
			found = true;
			swap(dict[i], dict[n - 1]);
			delete[] dict[n-1].eng;
			delete[] dict[n-1].rus;
			n--;
		}
	}
	if (!found)
	{
		cout << "Такого слова в словаре нет." << endl;
	}
	else
	{
		sort_dict(dict, n);
	}
}

void eng_to_rus(Dictionary* dict, int n)
{
	char word[31];
	int left = 0;
	int right = n - 1;
	int middle;
	cout << "Введите слово для перевода с английского на русский: ";
	cin >> word;
	char* cut_word = cut(word); // Обрезаем лишнее.
	while (right != left) // Двоичный поиск нужной структуры в массиве.
	{
		middle = (right + left) / 2;
		if (strcmp(cut_word, dict[middle].eng) > 0) // Случай, когда искомая структура находится в правой половине массива.
		{
			left = middle + 1;
		}
		else // Случай, когда искомая структура находится в левой половине массива.
		{
			right = middle;
		}
	}
	if (!(strcmp(cut_word, dict[right].eng))) // Случай, когда перевод слова нашёлся.
	{
		cout << "Перевод: " << dict[right].rus << endl;
	}
	else // Случай, когда перевод не нашёлся.
	{
		cout << "Такого слова в словаре нет." << endl;
	}
}

void rus_to_eng(Dictionary* dict, int n)
{
	char word[31];
	int i;
	bool found = false;
	cout << "Введите слово для перевода с русского на английский: ";
	cin >> word;
	char* cut_word = cut(word); // Обрезаем лишнее.
	for (i = 0; i < n && !found; i++) // Простой поиск перебором.
	{
		if (!(strcmp(cut_word, dict[i].rus)))
		{
			found = true;
			cout << "Перевод: " << dict[i].eng << endl;
		}
	}
	if (!found)
	{
		cout << "Такого слова в словаре нет." << endl;
	}
}


void print_dict(Dictionary* dict, int n)
{
	int i;
	cout << setw(31) << left << "Английский"
		 << setw(31) << left << "Русский" << endl;;
	for (i = 0; i < n; i++)
	{
		cout << setw(31) << left << dict[i].eng
		     << setw(31) << left << dict[i].rus << endl;
	}
}

void write_dict(Dictionary* dict, int n, char* name)
{
	ofstream outfile(name);
	int i;
	for (i = 0; i < n; i++)
	{
		outfile << dict[i].eng << endl << dict[i].rus;
		if (i < n - 1) // Просто endl писать нежелательно, т.к. это создаст пустую строку в конце файла.
		{
			outfile << endl;
		}
	}
}

void sort_dict(Dictionary* dict, int n) // Сортировка массива dict по английским частям его элементов (и по алфавиту).
{
	int i, j; // Переменные для итерации.
	bool not_sorted = true; // Переменная, показывающая, отсортирован ли массив.
	for (i = 0; i < n - 1 && not_sorted; i++)
	{
		not_sorted = false;
		for (j = n - 1; j > i; j--)
		{
			if (strcmp(dict[j].eng, dict[j - 1].eng) < 0)
			{
				swap(dict[j - 1], dict[j]);
				not_sorted = true;
			}
		}
	}
}

char* cut(char original[]) // Преобразование статичного массива char в строку нужной длины.
{
	char* result = new char[strlen(original) + 1];
	int i;
	for (i = 0; i < (int) strlen(original) + 1; i++)
	{
		result[i] = original[i];
	}
	return result;
}