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
	library.ReadDB("..\\Library\\");  // 2 backslashes due to '\' being an escape character.
	library.WriteDB("..\\Library\\");
	library.ReadDB("..\\Library\\");
	library.PrintDB1(80);
	system("pause");

	//TODO: Write functions that use DBTableSet to  add students/ababonements/books and do otheher essential/cool stuff.
	return 0;
}
