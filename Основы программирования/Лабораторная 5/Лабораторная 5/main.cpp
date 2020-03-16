#include "main.h"
#include "sorts.h"
#include "massive_manip.h"

using namespace std;

int main() {
	setlocale(0, "Russian");
	int size; // ������ ������������� �������.
	char answer; // ���������� ��� ������������ ���������.
	int comparisons; // ���������� ���������.
	int changes; // ���������� ������������.
	int i; // ����������-�������
	int* a, * b, * c, * d; // ��������� �� ��������� ������������ �������
	for (;;) {
		// ��������� ������������ ������������������ �������.
		cout << "������� �������� ����� �������: ";
		cin >> size;
		cout << endl;
		if (size <= 0) {
			cout << "�������� ����� �������!" << endl << endl;
			continue;
		}
		a = new int[size]; // ������������� ������������� �������.
		fill_massive(a, size);
		cout << "����������������� ������:" << endl;
		print_massive(a, size);
		b = selection_sort(a, size, comparisons, changes); // ��������� �������, ���������������� ������� ������������� ��������.
		cout << "��������������� ������:" << endl;
		print_massive(b, size);
		cout << "      ���������� ��� ������������ �������:" << endl << endl;
		cout << "  ����� ������������� ��������:" << endl;
		print_massive(b, size);
		cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		delete[] b;
		cout << "  ����� ��������:" << endl;
		b = bubble_sort(a, size, comparisons, changes); // ��������� �������, ���������������� ������� ��������.
		print_massive(b, size);
		cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		delete[] a;

		cout << "      ���������� ��� ��� ���������������� �������:" << endl << endl;
		cout << "  ����� ������������� ��������:" << endl;
		c = selection_sort(b, size, comparisons, changes);
		cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		delete[] c;
		cout << "  ����� ��������:" << endl;
		c = bubble_sort(b, size, comparisons, changes);
		cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		delete[] c;

		c = reverse_massive(b, size);
		delete[] b;
		cout << "      ���������� ��� ���������������� �������:" << endl << endl;
		cout << "  ����� ������������� ��������:" << endl;
		d = selection_sort(c, size, comparisons, changes); // ��������� �������, ���������������� ������� ������������� ��������.
		print_massive(d, size);
		cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		delete[] d;
		cout << "  ����� ��������:" << endl;
		d = bubble_sort(c, size, comparisons, changes); // ��������� �������, ���������������� ������� ��������.
		print_massive(d, size);
		cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		delete[] d;
		delete[] c;
		for (i = 5; i <= 500; i *= 10)
		{
			a = new int[i];
			fill_massive(a, i);
			cout << "      ���������� ��� ������� ������ " << i << ":" << endl << endl;
			cout << "  ����� ������������� ��������:" << endl;
			b = selection_sort(a, i, comparisons, changes); // ��������� �������, ���������������� ������� ������������� ��������.
			cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
			delete[] b;
			cout << "  ����� ��������:" << endl;
			b = bubble_sort(a, i, comparisons, changes); // ��������� �������, ���������������� ������� ��������.
			delete[] b;
			cout << "���������: " << comparisons << " ������������:" << changes << endl << endl;
		}
		cout << "������ ����������? (y/n) ";
		cin >> answer;
		if (answer != 'y') {
			break;
		}
		cout << endl;
	}
}
