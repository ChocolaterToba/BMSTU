#include "pch.h"
#include <iostream>
#include "Planet.h"

int Planet::total = 0;

Planet::Planet(char* new_name, int new_diameter, bool new_life, int new_satellites) {
    name = nullptr;
    diameter = 1;
    new_life = false;
    satellites = 0;
    total++;
    id = total;
    update(new_name, new_diameter, new_life, new_satellites);
}

Planet::~Planet() {
    total--;
    if (name != nullptr) {
        delete[] name;
    }
}

void Planet::update(char* new_name, int new_diameter, bool new_life, int new_satellites) {
    set_name(new_name);
    set_diameter(new_diameter);
    set_life(new_life);
    set_satellites(new_satellites);
}
void Planet::set_name(char* new_name) {
    if (name != nullptr) {
        delete[] name;
    }
    name = cut(new_name);
}
void Planet::set_diameter(int new_diameter) {
    if (new_diameter > 0) {
        diameter = new_diameter;
    }
    else {
        cout << "Некорректный диаметр: " << new_diameter
             << " Сохраняется прежнее значение (1 по умолчанию)" << endl;
    }
}
void Planet::set_life(bool new_life) {
    life = new_life;
}
void Planet::set_satellites(int new_satellites) {
    if (new_satellites >= 0) {
        satellites = new_satellites;
    }
    else {
        cout << "Некорректное число спутников: " << new_satellites
             << " Сохраняется прежнее значение (1 по умолчанию)" << endl;
    }
}
void Planet::edit() {
    const int name_len = 100;
    int answer;
    cout << "Что бы вы хотели изменить?" << endl
         << "Название: 1" << endl
         << "Диаметр: 2" << endl
         << "Жизнь: 3" << endl
         << "Количество спутников: 4" << endl
         << "Введите номер желаемой опции: ";
    cin >> answer;
    cout << endl;
    switch (answer) {
    case 1:
        char new_name[name_len];
        cout << "Введите новое название: ";
        cin >> new_name;
        cout << endl;
        set_name(new_name);
        break;
    case 2:
        int new_diameter;
        cout << "Введите новый диаметр: ";
        cin >> new_diameter;
        cout << endl;
        set_diameter(new_diameter);
        break;
    case 3:
        bool new_life;
        cout << "Введите новый статус жизни (0, если жизни нет и 1, если есть): ";
        cin >> new_life;
        cout << endl;
        set_life(new_life);
        break;
    case 4:
        int new_satellites;
        cout << "Введите новое количество спутников: ";
        cin >> new_satellites;
        cout << endl;
        set_satellites(new_satellites);
        break;
    default:
        cout << "Такой опции нет! Планета останется неизменной" << endl;
    }
}

void Planet::out() {
    cout << "Planet: " << name << endl
        << "Diameter: " << diameter << endl
        << "Has it life?: " << life << endl
        << "Sattelites count: " << satellites << endl << endl;
}

ofstream& operator<< (ofstream& out, Planet& planet) {
    out << planet.name << " "
        << planet.diameter << " "
        << planet.life << " "
        << planet.satellites << endl;
    return out;
}
ifstream& operator>> (ifstream& in, Planet& planet) {
    const int name_len = 100;
    char new_name[name_len];
    int new_diameter, new_life, new_satellites;
    in >> new_name >> new_diameter >> new_life >> new_satellites;
    planet.update(new_name, new_diameter, new_life, new_satellites);
    return in;
}

void Planet::operator= (Planet& planet) {
    if (name != nullptr) {
        delete[] name;
    }
    name = cut(planet.name);
    diameter = planet.diameter;
    life = planet.life;
    satellites = planet.satellites;
    id = planet.id;
}

bool Planet::operator< (Planet& other) {
    int i;
    char* other_name = other.name;
    for (i = 0; name[i] && other_name[i] && name[i] == other_name[i]; i++);
    return name[i] < other_name[i];
}
bool Planet::operator== (Planet& other) {
    int i;
    char* other_name = other.name;
    for (i = 0; name[i] && other_name[i] && name[i] == other_name[i]; i++);
    return name[i] == other_name[i];
}
bool Planet::operator> (Planet& other) {
    int i;
    char* other_name = other.name;
    for (i = 0; name[i] && other_name[i] && name[i] == other_name[i]; i++);
    return name[i] > other_name[i];
}
bool Planet::operator<= (Planet& other) {
    int i;
    char* other_name = other.name;
    for (i = 0; name[i] && other_name[i] && name[i] <= other_name[i]; i++);
    return name[i] <= other_name[i];
}
bool Planet::operator>= (Planet& other) {
    int i;
    char* other_name = other.name;
    for (i = 0; name[i] && other_name[i] && name[i] >= other_name[i]; i++);
    return name[i] >= other_name[i];
}

char* Planet::get_name() {
    return name;
}
int Planet::get_diameter() {
    return diameter;
}
bool Planet::get_life() {
    return life;
}
int Planet::get_satellites() {
    return satellites;
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