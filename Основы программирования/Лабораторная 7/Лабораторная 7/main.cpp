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
	int* key; // ������ �� ������, � ������� ������������� ����-����.
	int key_len; // ����� ������� key.
	int i, a, b; // ���������� ��� ��������.
	int statistics[256][256]; // ������ �������������� ������.
	for (i = 0; i < 256; i++) // ��������� ��������� ������� �������������� ������.
	{
		for(a = 0; a < 256; a++)
		{
			statistics[i][a] = 0;
		}
	}
	ifstream infile("input.txt", ios::binary); // ����� ��� ���������� ��������� �����.
	ofstream outfile("output.txt", ios::binary); // ����� ��� ������ ����������.
	if (!infile) // �������� �� ������� ������ �� ������� ������.
	{
		cout << "Error when opening input file!" << endl;
		system("pause");
		return 1;
	}
	key = get_key("key.txt", len, key_len); // ��������� ��������� ������� �� ���������������� �����.
	if (key[0] == -1) // �������� �� ������� ������ � "��������" ������.
	{
		cout << "Error when opening key file!" << endl;
		system("pause");
		return 1;
	}
	for (b = 0; infile.get(character); b++) // ���������� �������� xor � ������� ������� ��������� �����.
	{
		b %= key_len;
		new_character = (unsigned char) (character ^ key[b]);
		outfile.put((char) new_character);
		statistics[(unsigned char) character][new_character] ++;
	}
	delete[] key;
	infile.close();
	outfile.close();
	while (answer == 'y') // ����� ���������� �� ��������� ������������� ������� �� �����.
	{
		cout << "������� �������� ������: ";
		cin >> answer;
		cout << answer << endl;
		output_stats(statistics[(unsigned char)answer]);
		cout << "������ ����������? (y/n): ";
		cin >> answer;
		cout << endl << endl;
	}
    return 0; 
}


int* get_key(const char* name, int len, int& i) // �������������� ����� � ��������� name � �������� ������.
{
	ifstream keyfile(name, ios::binary); // ����� ��� ���������� �������� ��������.
	int a; // ���������� ��� ��������.
	int sum; // ����� ����� �������� ����� ������.
	int * key = new int[100]; // ������ ��� �������� ����� (100 ���� ���������).
	key[0] = -1;
	if (!keyfile) // ���� ��� �������� ����� ��������� ������, ��������� ������ � ������� ���������, ������ -1 (������������ "��� ������").
	{
		return key;
	}
	char* line = new char[len];
	for(i = 0; keyfile.getline(line, len); i++) // ���������� ������ ������ �����.
	{
		sum = 0;
		for(a = 0; line[a] != '\0'; a++) // ������������ ����� �������� �� ������.
		{
			sum += (unsigned char)line[a];
		}
		key[i] = sum % 256;
	}
	keyfile.close();
	delete[] line;
	int* return_key = new int[i];
	for(a = 0; a < i; a++) // ����������� ������� ������� � ����� ������ � ������ ������.
	{
		return_key[a] = key[a];
		key[a] = 0;
	}
	delete[] key;
	return return_key;
}


void output_stats(int stats[]) // ����� �������������� ������ ��� ������� �������.
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