#include <iostream>
#include <iomanip>
#include"dbmsLib_v1.h"
using namespace std;
int menu(){
	cout<<"================= ����� ���� ===================\n";
	cout<<"\t1 - ������ ������� �� �����\n";
	cout<<"\t2 - ������ �������\n";
	cout<<"\t3 - ������ ������� � ����\n";
	cout<<"\t4 - ���������� ������ � �������\n";
	cout<<"\t5 - �������� ������ �� ������� (�� �������� � �������� �������)\n";
	cout<<"\t6 - ����������� ������� ��������, StudentID �������� ����� 3\n";
	cout<<"\t7 - ��������� �� 1 ���������� ����������� ���� ���� � ���������� \n";
	cout<<"\t8 - ������������\n";
	cout<<"\t10 - �����\n";

	int choice;
	cout<<"�������� ��������\n";
	cin>>choice;
	while(cin.fail()){
	    cout<<"������ �����. ��������� ����\n";	
	    cin.clear();
	    cin.ignore(10,'\n');
	    cin>>choice;
	}
	return choice;
}

//=================================================
int main(){
	system("chcp 1251>nul");
	DBMSFuncs::DBTableSet library("Library");
	library.ReadDB("..\\Library\\");
	library.OutputTables();
	system("pause");
	library.PrintDB(80);
	system("pause");
	return 0;
}
