#include <iostream>
#include <iomanip>
#include <cstring>

#include "FlatTesting.h"
#include "windows.h"

const int Size = 100;

int main() {
	setlocale(LC_CTYPE, ".1251");
	char* file_name = (char *)"database.txt";
	Flat flats_database[Size];
	int n_flats = 0;
	int ind;
	while (true) {
		switch (menu())
		{
		case 1:
			n_flats = read_db(file_name, flats_database, Size);
			break;
		case 2:
			write_db(file_name, flats_database, n_flats);
			break;
		case 3:
			if ((ind = find(flats_database, n_flats)) >= 0) {
				cout << "Квартира готова к изменению." << endl;
				flats_database[ind].edit();
				cout << endl;
			}
			else {
				cout << "Квартиры с этим адресом нет" << endl << endl;
			}
			break;
		case 4:
			if ((ind = find(flats_database, n_flats)) >= 0) {
				cout << "Квартира удалена." << endl;
				delete_flat(flats_database, ind, n_flats);
				cout << endl;
			}
			else {
				cout << "Квартиры с этим адресом нет" << endl << endl;
			}
			break;
		case 5:
			add_flat(flats_database, n_flats, Size);
			cout << endl;
			break;
		case 6:
			print_db(flats_database, n_flats);
			break;
		case 7:
			int result;
	        cout << "      Сортировать по:" << endl
		         << "Адресу: 1" << endl
		         << "Площади: 2" << endl
		         << "Числу комнат: 3" << endl
		         << "Цене: 4" << endl
		         << "Введите номер желаемой опции: ";
	        cin >> result;
	        cout << endl;
			if (result > 0 && result < 5) {
			    qsort(flats_database, 0, n_flats - 1, result);
			}
			else {
				cout << "Такой опции сортировки нет!" << endl;
			}
			cout << endl;
			break;
		case 8:
			return 0;
		default:
			cout << "Неправильный ввод" << endl;
			break;
		}
	}
	return 0;
}

int read_db(char* file_name, Flat* flats, const int flats_size) {
	int n_flats;
	int i;
	ifstream infile(file_name);
	if (infile.fail()) {
		cout << "Ошибка при чтении файла " << file_name << endl;
		system("pause");
		infile.clear();
		infile.close();
		return 0;
	}
	infile >> n_flats;
	if (n_flats > flats_size) {
		n_flats = flats_size - 1;
	}
	for (i = 0; i < n_flats; i++) {
		infile >> flats[i];
	}
	infile.close();
	return n_flats;
}
void write_db(char* file_name, Flat* flats, int n_flats) {
	ofstream outfile(file_name);
	int i;
	outfile << n_flats << endl;
	for (i = 0; i < n_flats; i++) {
		outfile << flats[i];
	}
	outfile.close();
}
int find(Flat* flats, int n_flats) {
	int i, a;
	const int word_len = 100;
	char address[word_len];
	char* flat_address;
	cout << "Введите адрес квартиры: ";
	cin >> address;
	for (i = 0; i < n_flats; i++) {
		flat_address = flats[i].get_address();
		for (a = 0; flat_address[a] && address[a] && flat_address[a] == address[a]; a++);
		if (flat_address[a] == address[a]) {
			return i;
		}
	}
	return -1;
}
void delete_flat(Flat* flats, int index, int& n_flats) {
    flats[index] = flats[n_flats - 1];
	flats[n_flats - 1].update("\0", 1, 1, 1);
	n_flats--;
}
void add_flat(Flat* flats, int& n_flats, const int flats_size) {
	const int address_len = 100;
	char new_address[address_len];
	int new_floor_area, new_room_amount, new_price;
	if (n_flats == flats_size) {
		cout << "Невозможно добавить квартиру - база данных заполнена" << endl;
	}
	else {
        cout << "Введите адрес, площадь, количество комнат и цену квартиры через пробел:" << endl;
	    cin >> new_address >> new_floor_area >> new_room_amount >> new_price;
	    cout << endl;
		flats[n_flats].update(new_address, new_floor_area, new_room_amount, new_price);
		n_flats++;
	}
}
void print_db(Flat* flats, int n_flats) {
	cout << setw(20) << "Адрес квартиры"
		 << setw(15) << "Площадь"
		 << setw(15) << "Кол-во комнат"
		 << setw(15) << "Цена" << endl;
	int i;
	for (i = 0; i < n_flats; i++) {
		cout << setw(20) << flats[i].get_address()
			 << setw(15) << flats[i].get_floor_area()
			 << setw(15) << flats[i].get_room_amount()
			 << setw(15) << flats[i].get_price() << endl;
	}
}

int  menu() {
	int result;
	cout << "      Меню:" << endl
		<< "Чтение БД из файла: 1" << endl
		<< "Запись БД в файл: 2" << endl
		<< "Изменение существующей квартиры: 3" << endl
		<< "Удаление квартиры: 4" << endl
		<< "Добавление квартиры: 5" << endl
		<< "Печать БД: 6" << endl
		<< "Сортировка БД: 7" << endl
		<< "Выход: 8" << endl
		<< "Введите номер желаемой опции: ";
	cin >> result;
	cout << endl;
	return result;
}

void qsort(Flat* arr, int start, int end, int type) { // Quick sort from start to end including both.
	Flat* pivot = arr + end; // Element to be placed at the right position
	int i = start - 1, j;
	switch (type) {
	case 1:
	    for (j = start; j < end; j++) {
		    if (strcmp(arr[j].get_address(), (*pivot).get_address()) < 0) {
		    	i++;
			    swap(arr[i], arr[j]);
		    }
	    }
		break;

    case 2:
	    for (j = start; j < end; j++) {
		    if (arr[j].get_floor_area() < (*pivot).get_floor_area()) {
		    	i++;
			    swap(arr[i], arr[j]);
		    }
	    }
		break;

	case 3:
	    for (j = start; j < end; j++) {
		    if (arr[j].get_room_amount() < (*pivot).get_room_amount()) {
		    	i++;
			    swap(arr[i], arr[j]);
		    }
	    }
		break;

	case 4:
	    for (j = start; j < end; j++) {
		    if (arr[j].get_price() < (*pivot).get_price()) {
		    	i++;
			    swap(arr[i], arr[j]);
		    }
	    }
		break;

	default:
		return;
    }
	swap(arr[i + 1], arr[end]);

	if (i > start) {
		qsort(arr, start, i, type); // Sorting "less than pivot" and "more than pivot" arrays.
	}
	if (end > i + 2) {
	    qsort(arr, i + 2, end, type);
	}
}

void swap(Flat& first, Flat& second) {
	Flat temp;
	temp = first;
	first = second;
	second = temp;
}