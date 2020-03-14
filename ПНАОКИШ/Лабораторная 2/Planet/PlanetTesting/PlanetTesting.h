#ifndef __PLANETTESTING_H__
#define __PLANETTESTING_H__
#include "Planet.h"

using namespace std;

int main();
int read_db(char*, Planet*, const int);
void write_db(char*,Planet*, int);
int find(Planet*,int);
void delete_planet(Planet*, int, int&);
void add_planet(Planet*, int&, const int);
void print_db(Planet*, int); 
int  menu();

void qsort(Planet*, int, int);
void swap(Planet&, Planet&);
#endif