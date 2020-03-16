#include "three_methods.h"
#include "sami_methody.h"

using namespace std;

int main() {
	setlocale(0, "Russian");
	char answer;
	cout << "Корни уравнения x - cos(x) = 0 c погрешностью 0.000001:" << endl;
	half_div(1, 6);
	newton(1, 6);
	simple_iter(1, 6);
	cout << endl;
	cout << "Корни уравнения x - cos(x) = 0 c погрешностью 0.00000001:" << endl;
	half_div(1, 8);
	newton(1, 8);
	simple_iter(1, 8);
	cout << endl;
	cout << "Корни уравнения x - 10cos(x) = 0 c погрешностью 0.000001:" << endl;
	half_div(10, 6);
	newton(10, 6);
	simple_iter(10, 6);
	cin >> answer;
}