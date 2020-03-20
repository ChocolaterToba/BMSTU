#include <iostream>
#include <iomanip>
#include "PlanetTesting.h"
#include "windows.h"

const int Size = 12;

int main() {
    setlocale(LC_CTYPE, ".1251");
    char* file_name = (char *)"database.txt";
    Planet solar_system[Size];
    int n_planet = 0;
    int ind;
    while (true) {
        switch (menu())
        {
        case 1:
            n_planet = read_db(file_name, solar_system, Size);
            break;
        case 2:
            write_db(file_name, solar_system, n_planet);
            break;
        case 3:
            if ((ind = find(solar_system, n_planet)) >= 0) {
                cout << "����� ������� ����" << endl;
                solar_system[ind].edit();
            }
            else {
                cout << "����� ������� ���" << endl << endl;
            }
            break;
        case 4:
            if ((ind = find(solar_system, n_planet)) >= 0) {
                cout << "����� ������� ���� � ����� �������" << endl;
                delete_planet(solar_system, ind, n_planet);
                cout << endl;
            }
            else {
                cout << "����� ������� ���" << endl << endl;
            }
            break;
        case 5:
            add_planet(solar_system, n_planet, Size);
            cout << endl;
            break;
        case 6:
            print_db(solar_system, n_planet);
            break;
        case 7:
            qsort(solar_system, 0, n_planet - 1);
            break;
        case 8:
            return 0;
        default:
            cout << " ������������ ����" << endl;
            break;
        }
    }
    return 0;
}

int read_db(char* file_name, Planet* planets, const int planets_size) {
    int n_planet;
    int i;
    ifstream infile(file_name);
    if (infile.fail()) {
        cout << "������ ��� ������ ����� " << file_name << endl;
        system("pause");
        infile.clear();
        infile.close();
        return 0;
    }
    infile >> n_planet;
    if (n_planet > planets_size) {
        n_planet = planets_size - 1;
    }
    for (i = 0; i < n_planet; i++) {
        infile >> planets[i];
    }
    infile.close();
    return n_planet;
}
void write_db(char* file_name, Planet* planets, int n_planet) {
    ofstream outfile(file_name);
    int i;
    outfile << n_planet << endl;
    for (i = 0; i < n_planet; i++) {
        outfile << planets[i];
    }
    outfile.close();
}
int find(Planet* planets, int n_planet) {
    int i, a;
    const int word_len = 100;
    char name[word_len], * planet_name;
    cout << "������� ��� �������: ";
    cin >> name;
    for (i = 0; i < n_planet; i++) {
        planet_name = planets[i].get_name();
        for (a = 0; planet_name[a] && name[a] && planet_name[a] == name[a]; a++);
        if (planet_name[a] == name[a]) {
            return i;
        }
    }
    return -1;
}
void delete_planet(Planet* planets, int index, int& n_planet) {
    planets[index] = planets[n_planet - 1];
    planets[n_planet - 1].update((char*)"", 1, 0, 0);
    n_planet--;
}
void add_planet(Planet* planets, int& n_planet, const int planets_size) {
    const int name_len = 100;
    char new_name[name_len];
    int new_diameter, new_life, new_satellites;
    if (n_planet == planets_size) {
        cout << "���������� �������� ������� - ������ ��������" << endl;
    }
    else {
        cout << "������� ��������, �������, ������� ����� (0 ���� 1), ���������� � ��������� ����� ������" << endl;
        cin >> new_name >> new_diameter >> new_life >> new_satellites;
        cout << endl;
        planets[n_planet].update(new_name, new_diameter, new_life, new_satellites);
        n_planet++;
    }
}
void print_db(Planet* planets, int n_planet) {
    cout << setw(20) << "�������� �������"
         << setw(15) << "�������"
         << setw(15) << "������� �����"
         << setw(25) << "���������� ���������" << endl;
    for (int i = 0; i < n_planet; i++) {
        cout << setw(20) << left << planets[i].get_name()
             << setw(15) << right << planets[i].get_diameter()
             << setw(15) << planets[i].get_life()
             << setw(25) << planets[i].get_satellites() << endl;
    }
}

int  menu() {
    int result;
    cout << "      ����:" << endl
        << "������ �� �� �����: 1" << endl
        << "������ �� � ����: 2" << endl
        << "��������� ������������ �������: 3" << endl
        << "�������� �������: 4" << endl
        << "���������� �������: 5" << endl
        << "������ ��: 6" << endl
        << "���������� ��: 7" << endl
        << "�����: 8" << endl
        << "������� ����� �������� �����: ";
    cin >> result;
    cout << endl;
    return result;
}

void qsort(Planet* arr, int start, int end) { // Quick sort from start to end including both.
    Planet* pivot = arr + end; // Element to be placed at the right position
    int i = start - 1, j;
    for (j = start; j < end; j++) {
        if (arr[j] < *pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    if (i > start) {
        qsort(arr, start, i); // Sorting "less than pivot" and "more than pivot" arrays.
    }
    if (end > i + 2) {
        qsort(arr, i + 2, end);
    }
}

void swap(Planet& first, Planet& second) {
    Planet temp;
    temp = first;
    first = second;
    second = temp;
}