#ifndef __PLANETTESTING_H__
#define __PLANETTESTING_H__
#include "Flat.h"

using namespace std;

int main();
int read_db(char*, Flat*, const int);
void write_db(char*,Flat*, int);
int find(Flat*,int);
void delete_flat(Flat*, int, int&);
void add_flat(Flat*, int&, const int);
void print_db(Flat*, int); 
int  menu();

void qsort(Flat*, int, int, int);
void swap(Flat&, Flat&);
#endif