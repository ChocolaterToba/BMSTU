#include "main.h"
#include "windows.h"
#include "conio.h"
#include "massive_manip.h"

using namespace std;

int main()
{
	char a; // �������� ������������� ������.
	int current_index = 0; // ���������� ��������� ��������.
	int text_size = 100; // ������ ������� text.
	int words_size = 1; // ����� ������� words.
	int i, b; // ���������� - ��������.
	char* text = new char[text_size]; // ������, � ������� ������������ ���������������� ������.
	char** words = new char*[words_size]; // ������ �� ������� �� �������� ������.
	do // ���� ������ � ����������, ��� ������ � ���� 1 ������.
	{
		a = _getch();
		if (a == '\b' && current_index) // ������ � Backspace.
		{
			_putch('\b');
			_putch('\0');
			_putch('\b');
			current_index--;
		}
		else if ((a >= 97 && a <= 122) || a == 32)
		// ������ � ������� � ������ �������� � ��������.
		{
			_putch(a);
			text[current_index] = a;
			current_index++;
			if (current_index == text_size)
			{
				text = change_length(text, text_size, 100);
				text_size += 100;
			}
		}
	}
	while (a != '.');

	text = change_length(text, current_index, 0); // ��������� ������������ ������� ����� ������� text.
	i = 0;
	while (i < current_index) // �������������� ������ � ������ ����.
	{
		if (text[i] == ' ')
		{
			i++;
		}
		else // ������ �����.
		{
			for (b = i + 1; b < current_index; b++) // b - ������ ����� �����.
			{
				if (text[b] == ' ')
				{
					break;
				}
			};
			words = change_length(words, words_size, 1); // ����������� ����� words �� 1.
			words[words_size - 1] = new char[b - i + 1]; // �������� ����� � words.
			copy_massive(text, words[words_size - 1], i, b); // �������� ����� �� text � words.
			words[words_size - 1][b - i] = '\0';
			words_size ++;
			i = b + 1; // + 1 �.�. text[b] - ��� ���� ������, ���� �����.
		}
	}
	
	words_size--; // �������� ����� ������� words.
	for (i = 0; i < words_size; i++)
	// �������� ��������� ����� �� ����, ������������ �� ����������.
	// � �������� ����, �� �������� �� ����������.
	{
		if (!strcmp(words[i], words[words_size - 1]))
		{
			words[i] = change_length(words[i], 1, 0);
			words[i][0] = '\0';
		}
		else
		{
			for (b = 0; words[i][b + 1] != '\0'; b++);
			words[i] = change_length(words[i], b + 2, -1);
			words[i][b] = '\0';
		}
	}

	for (i = current_index; i; i--)
	// ������� �������.
	{
		_putch('\b');
		_putch('\0');
		_putch('\b');
	}

	for (i = 0; i < words_size; i++) // ����� ���� �� �����
	{
		for (b = 0; words[i][b] != '\0'; b++)
		{
			_putch(words[i][b]);
		}
		if (b) // ���� ����� ���� �� ������, ��������� ������.
		{
		    _putch(' ');
		}
	}
	_putch('\b');
	_putch('.');
	_putch('\n');
	system("pause");
	return 1;
}


