#include "main.h"
#include "windows.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int len = 1000;
	char character, answer = 'y';
	unsigned char new_character;
	int* key; // Сселка на массив, в который преобразуется файл-ключ.
	int key_len; // Длина массива key.
	int i, a, b; // Переменные для итерации.
	int statistics[256][256]; // Массив статистических данных.
	for (i = 0; i < 256; i++) // Обнуление элементов массива статистических данных.
	{
		for(a = 0; a < 256; a++)
		{
			statistics[i][a] = 0;
		}
	}
	ifstream infile("input.txt", ios::binary); // Поток для считывания исходного файла.
	ofstream outfile("output.txt", ios::binary); // Поток для записи результата.
	if (!infile) // Проверка на наличие ошибок во входном потоке.
	{
		cout << "Error when opening input file!" << endl;
		system("pause");
		return 1;
	}
	key = get_key("key.txt", len, key_len); // Получение ключевого массива из соответствующего файла.
	if (key[0] == -1) // Проверка на наличие ошибок в "ключевом" потоке.
	{
		cout << "Error when opening key file!" << endl;
		system("pause");
		return 1;
	}
	for (b = 0; infile.get(character); b++) // Применение операции xor к каждому символу исходного файла.
	{
		b %= key_len;
		new_character = (unsigned char) (character ^ key[b]);
		outfile.put((char) new_character);
		statistics[(unsigned char) character][new_character] ++;
	}
	delete[] key;
	infile.close();
	outfile.close();
	while (answer == 'y') // Вывод статистики по введённому пользователем символу на экран.
	{
		cout << "Введите желаемый символ: ";
		cin >> answer;
		cout << answer << endl;
		output_stats(statistics[(unsigned char)answer]);
		cout << "Хотите продолжить? (y/n): ";
		cin >> answer;
		cout << endl << endl;
	}
    return 0; 
}


int* get_key(const char* name, int len, int& i) // Преобразование файла с названием name в ключевой массив.
{
	ifstream keyfile(name, ios::binary); // Поток для считывания кодового блокнота.
	int a; // Переменная для итерации.
	int sum; // Сумма кодов символов одной строки.
	int * key = new int[100]; // Массив для хранения ключа (100 чтоб наверняка).
	key[0] = -1;
	if (!keyfile) // Если при открытии файла произошла ошибка, выводится массив с нулевым элементом, равным -1 (своеобразный "код ошибки").
	{
		return key;
	}
	char* line = new char[len];
	for(i = 0; keyfile.getline(line, len); i++) // Считывание каждой строки файла.
	{
		sum = 0;
		for(a = 0; line[a] != '\0'; a++) // Суммирование кодов символов из строки.
		{
			sum += (unsigned char)line[a];
		}
		key[i] = sum % 256;
	}
	keyfile.close();
	delete[] line;
	int* return_key = new int[i];
	for(a = 0; a < i; a++) // Копирование старого массива в новый массив с нужной длиной.
	{
		return_key[a] = key[a];
		key[a] = 0;
	}
	delete[] key;
	return return_key;
}


void output_stats(int stats[]) // Вывод статистических данных для некоего символа.
{
	int i;
	int a;
	for (i = 0; i < 16; i++)
	{
		for(a = 0; a < 16; a++)
		{
			cout << setw(3) << left << stats[i * 16 + a];
		}
		cout << endl;
	}
	cout << endl;
}