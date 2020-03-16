#include "dict_manip.h"
#include "main.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

bool read_dict(Dictionary* dict, char* name, int& i)
{
	ifstream infile(name);
	if (!infile) // �������� �� ������� ������ �� ������� ������.
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
		if (i % 2) // ���� ����� ������ (������� � 0) �������� - ����� �������.
		{
			dict[i / 2].rus = cut(line);
		}
		else // ���� ����� ������ (������� � 0) ������ - ����� ����������.
		{
			dict[i / 2].eng = cut(line);
		}
	}
	i /= 2;
	sort_dict(dict, i); // ��������� ������� ��� ���������� ������ ���� � ����������.
	return true;
}

void add_word(Dictionary* dict, int& n)
{
	char eng_word[31], rus_word[31];
	cout << "������� ����� ��-���������: ";
	cin >> eng_word;
	cout << "������� ����� ��-������: ";
	cin >> rus_word;
	dict[n].eng = cut(eng_word); // �������� ������.
	dict[n].rus = cut(rus_word);
	n++;
	sort_dict(dict, n); // ��������� ������� ��� ���������� ������ ���� � ����������.
}

void delete_word(Dictionary* dict, int& n)
{
	char word[31];
	int i;
	bool found = false;
	cout << "������� ����� ��� �������� (�� ����� �����): ";
	cin >> word;
	char* cut_word = cut(word); // �������� ������.
	for (i = 0; i < n && !found; i++) // ������� ����� ���������.
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
		cout << "������ ����� � ������� ���." << endl;
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
	cout << "������� ����� ��� �������� � ����������� �� �������: ";
	cin >> word;
	char* cut_word = cut(word); // �������� ������.
	while (right != left) // �������� ����� ������ ��������� � �������.
	{
		middle = (right + left) / 2;
		if (strcmp(cut_word, dict[middle].eng) > 0) // ������, ����� ������� ��������� ��������� � ������ �������� �������.
		{
			left = middle + 1;
		}
		else // ������, ����� ������� ��������� ��������� � ����� �������� �������.
		{
			right = middle;
		}
	}
	if (!(strcmp(cut_word, dict[right].eng))) // ������, ����� ������� ����� �������.
	{
		cout << "�������: " << dict[right].rus << endl;
	}
	else // ������, ����� ������� �� �������.
	{
		cout << "������ ����� � ������� ���." << endl;
	}
}

void rus_to_eng(Dictionary* dict, int n)
{
	char word[31];
	int i;
	bool found = false;
	cout << "������� ����� ��� �������� � �������� �� ����������: ";
	cin >> word;
	char* cut_word = cut(word); // �������� ������.
	for (i = 0; i < n && !found; i++) // ������� ����� ���������.
	{
		if (!(strcmp(cut_word, dict[i].rus)))
		{
			found = true;
			cout << "�������: " << dict[i].eng << endl;
		}
	}
	if (!found)
	{
		cout << "������ ����� � ������� ���." << endl;
	}
}


void print_dict(Dictionary* dict, int n)
{
	int i;
	cout << setw(31) << left << "����������"
		 << setw(31) << left << "�������" << endl;;
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
		if (i < n - 1) // ������ endl ������ ������������, �.�. ��� ������� ������ ������ � ����� �����.
		{
			outfile << endl;
		}
	}
}

void sort_dict(Dictionary* dict, int n) // ���������� ������� dict �� ���������� ������ ��� ��������� (� �� ��������).
{
	int i, j; // ���������� ��� ��������.
	bool not_sorted = true; // ����������, ������������, ������������ �� ������.
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

char* cut(char original[]) // �������������� ���������� ������� char � ������ ������ �����.
{
	char* result = new char[strlen(original) + 1];
	int i;
	for (i = 0; i < (int) strlen(original) + 1; i++)
	{
		result[i] = original[i];
	}
	return result;
}