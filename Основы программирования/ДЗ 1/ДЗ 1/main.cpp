#include "main.h"
#include "windows.h"
#include "conio.h"
#include "massive_manip.h"

using namespace std;

int main()
{
	char a; // Вводимый пользователем символ.
	int current_index = 0; // Количество считанных символов.
	int text_size = 100; // Размер массива text.
	int words_size = 1; // Длина массива words.
	int i, b; // Переменные - счётчики.
	char* text = new char[text_size]; // Массив, в который записывается пользовательская строка.
	char** words = new char*[words_size]; // Массив со словами из введённой строки.
	do // Ввод текста с клавиатуры, его запись в виде 1 строки.
	{
		a = _getch();
		if (a == '\b' && current_index) // Случай с Backspace.
		{
			_putch('\b');
			_putch('\0');
			_putch('\b');
			current_index--;
		}
		else if ((a >= 97 && a <= 122) || a == 32)
		// Случай с буквами в нижнем регистре и пробелом.
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

	text = change_length(text, current_index, 0); // Обрезание заполненного мусором конца массива text.
	i = 0;
	while (i < current_index) // Преобразование строки в массив слов.
	{
		if (text[i] == ' ')
		{
			i++;
		}
		else // Начало слова.
		{
			for (b = i + 1; b < current_index; b++) // b - индекс конца слова.
			{
				if (text[b] == ' ')
				{
					break;
				}
			};
			words = change_length(words, words_size, 1); // Увеличиваем длину words на 1.
			words[words_size - 1] = new char[b - i + 1]; // Создание слова в words.
			copy_massive(text, words[words_size - 1], i, b); // Копируем слово из text в words.
			words[words_size - 1][b - i] = '\0';
			words_size ++;
			i = b + 1; // + 1 т.к. text[b] - это либо пробел, либо мусор.
		}
	}
	
	words_size--; // Поправка длины массива words.
	for (i = 0; i < words_size; i++)
	// Удаление последней буквы из слов, отличающихся из последнего.
	// И удаление слов, не отличных от последнего.
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
	// Очистка консоли.
	{
		_putch('\b');
		_putch('\0');
		_putch('\b');
	}

	for (i = 0; i < words_size; i++) // Вывод слов на экран
	{
		for (b = 0; words[i][b] != '\0'; b++)
		{
			_putch(words[i][b]);
		}
		if (b) // Если слово было не пустое, выводится пробел.
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


