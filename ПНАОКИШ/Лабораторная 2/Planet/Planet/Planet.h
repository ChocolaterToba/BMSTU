#ifndef __PLANET_H__
#define __PLANET_H__
#include <fstream>

using namespace std;

char* cut(char*);

class Planet {
private:
	static int total;
	int id;

	char* name;
	int diameter;
	bool life;
	int satellites;

public:
	Planet(char* new_name = (char*)"\0", int new_diameter = 1, bool new_life = false, int new_satellites = 0);
	~Planet();

	void update(char*, int, bool, int);
	void set_name(char*);
	void set_diameter(int);
	void set_life(bool);
	void set_satellites(int);

	char* get_name();
	int get_diameter();
	bool get_life();
	int get_satellites();

	void out();
	void edit();

	friend ofstream& operator<< (ofstream&, Planet&);
	friend ifstream& operator>> (ifstream&, Planet&);

	void operator= (Planet&);

	bool operator< (Planet&);
	bool operator== (Planet&);
	bool operator> (Planet&);
	bool operator<= (Planet&);
	bool operator>= (Planet&);

};

#endif //__PLANET_H__