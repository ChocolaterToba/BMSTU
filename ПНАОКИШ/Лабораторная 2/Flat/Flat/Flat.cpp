#include "Flat.h"
#include <iostream>


int Flat::total = 0;

Flat::Flat(char* new_address, int new_floor_area, int new_room_amount, int new_price) {
	address = nullptr;
	floor_area = 1;
	room_amount = 1;
	price = 1;
	total++;
	id = total;
	update(new_address, new_floor_area, new_room_amount, new_price);
}

Flat::~Flat() {
	total--;
	if (address != nullptr) {
	    delete[] address;
	}
}

void Flat::update(char* new_address, int new_floor_area, int new_room_amount, int new_price) {
	set_address(new_address);
	set_floor_area(new_floor_area);
	set_room_amount(new_room_amount);
	set_price(new_price);
}
void Flat::set_address(char new_address[]) {
	if (address != nullptr) {
	    delete[] address;
	}
	address = cut(new_address);
}
void Flat::set_floor_area(int new_floor_area) {
	if (new_floor_area > 0) {
		floor_area = new_floor_area;
	}
	else {
		cout << "������������ �������: " << new_floor_area
			 << " ����������� ������� �������� (1 �� ���������)" << endl;
	}
}
void Flat::set_room_amount(int new_room_amount) {
	if (new_room_amount > 0) {
		room_amount = new_room_amount;
	}
	else {
		cout << "������������ ����� ������: " << new_room_amount
			 << " ����������� ������� �������� (1 �� ���������)" << endl;
	}
}
void Flat::set_price(int new_price) {
	if (new_price > 0) {
		price = new_price;
	}
	else {
		cout << "������������ ����: " << new_price
			 << " ����������� ������� �������� (1 �� ���������)" << endl;
	}
}
void Flat::edit() {
	const int addressLen = 100;
	int answer;
	cout << "��� �� �� ������ ��������?" << endl
		 << "�����: 1" << endl
		 << "�������: 2" << endl
		 << "���������� ������: 3" << endl
		 << "����: 4" << endl
		 << "������� ����� �������� �����: ";
	cin >> answer;
	cout << endl;
	switch (answer) {
	case 1:
		char new_address[addressLen];
		cout << "������� ����� �����: ";
		cin >> new_address;
		cout << endl;
		set_address(new_address);
		break;
	case 2:
		int new_floor_area;
		cout << "������� ����� �������: ";
		cin >> new_floor_area;
		cout << endl;
		set_floor_area(new_floor_area);
		break;
	case 3:
		int new_room_amount;
		cout << "������� ����� ���������� ������: ";
		cin >> new_room_amount;
		cout << endl;
		set_room_amount(new_room_amount);
		break;
	case 4:
		int new_price;
		cout << "������� ����� ����: ";
		cin >> new_price;
		cout << endl;
		set_price(new_price);
		break;
	default:
		cout << "����� ����� ���! �������� ��������� ����������" << endl;
	}
}

void Flat::out() {
	cout << "�����: " << address << endl
		<< "�������: " << floor_area << endl
		<< "���������� ������: " << room_amount << endl
		<< "����: " << price << endl << endl;
}

ofstream& operator<< (ofstream& out, Flat& flat) {
	out << flat.address << " "
		<< flat.floor_area << " "
		<< flat.room_amount << " "
		<< flat.price << endl;
	return out;
}
ifstream& operator>> (ifstream& in, Flat& flat) {
	const int addressLen = 100;
	char new_address[addressLen];
	int new_floor_area, new_room_amount, new_price;
	in >> new_address >> new_floor_area >> new_room_amount >> new_price;
	flat.update(new_address, new_floor_area, new_room_amount, new_price);
	return in;
}

void Flat::operator= (Flat& flat) {
	if (address != nullptr) {
	    delete[] address;
	}
	address = cut(flat.address);
	floor_area = flat.floor_area;
	room_amount = flat.room_amount;
	price = flat.price;
	id = flat.id;
}

bool Flat::operator< (Flat& other) {
	int i;
	char* other_address = other.address;
	for (i = 0; address[i] && other_address[i] && address[i] == other_address[i]; i++);
	return address[i] < other_address[i];
}
bool Flat::operator== (Flat& other) {
	int i;
	char* other_address = other.address;
	for (i = 0; address[i] && other_address[i] && address[i] == other_address[i]; i++);
	return address[i] == other_address[i];
}
bool Flat::operator> (Flat& other) {
	int i;
	char* other_address = other.address;
	for (i = 0; address[i] && other_address[i] && address[i] == other_address[i]; i++);
	return address[i] > other_address[i];
}
bool Flat::operator<= (Flat& other) {
	int i;
	char* other_address = other.address;
	for (i = 0; address[i] && other_address[i] && address[i] <= other_address[i]; i++);
	return address[i] <= other_address[i];
}
bool Flat::operator>= (Flat& other) {
	int i;
	char* other_address = other.address;
	for (i = 0; address[i] && other_address[i] && address[i] >= other_address[i]; i++);
	return address[i] >= other_address[i];
}

char* Flat::get_address() {
	return address;
}
int Flat::get_floor_area() {
	return floor_area;
}
int Flat::get_room_amount() {
	return room_amount;
}
int Flat::get_price() {
	return price;
}


char* cut(char* old_str) {
	char* new_str = new char[strlen(old_str) + 1];
	int i;
	for (i = 0; old_str[i]; i++)
	{
		new_str[i] = old_str[i];
	}
	new_str[i] = '\0';
	return new_str;
}