#ifndef __PLANET_H__
#define __PLANET_H__
#include <fstream>

using namespace std;

char* cut(char*);

class Flat {
private:
	static int total;
	int id;

	char* address;
	int floor_area;
	int room_amount;
	int price;

public:
	Flat(char* address = (char*)"\0", int new_floor_area = 1, int new_room_amount = 1, int new_price = 1);
	~Flat();

	void update(char*, int, int, int);
	void set_address(char*);
	void set_floor_area(int);
	void set_room_amount(int);
	void set_price(int);

	char* get_address();
	int get_floor_area();
	int get_room_amount();
	int get_price();

	void out();
	void edit();

	friend ofstream& operator<< (ofstream&, Flat&);
	friend ifstream& operator>> (ifstream&, Flat&);

	void operator= (Flat&);

	bool operator< (Flat&);
	bool operator== (Flat&);
	bool operator> (Flat&);
	bool operator<= (Flat&);
	bool operator>= (Flat&);

};

#endif //__PLANET_H__