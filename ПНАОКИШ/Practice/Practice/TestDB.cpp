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
	cout<<"\t5 - ��������� �������� � ������ ������\n";
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
	DBMSFuncs::DBTableTxt tab("Student.txt");
	while(true){
		switch(menu()){
		    case 1: 
				tab.ReadTableTxt("Student");  // I have no idea why we need a string as an argument here, but whatever.
				break;
			case 2:
				tab.PrintTable(80);
				break;
			case 3:
				tab.WriteTableTxt("Student");
				break;
			case 4:
				{
					DBMSFuncs::Row newRow = tab.CreateRow();

					string primaryKey = tab.GetPrimaryKey();
					DBMSFuncs::TableDataType type = tab.GetHeader()[primaryKey].colType;
					bool similarKey = false;
					for (size_t i = 0; i < tab.GetSize(); ++i) {
						if (comparator(type, tab[i][primaryKey], DBMSFuncs::Equal, newRow[primaryKey])) {
							cout << "� ������� ��� ������������ ������ � ����� �� ��������� \
									 ���������� �����. ���������� �������� ������ ����������." << endl;
							similarKey = true;
							break;
						}
					}

					if (!similarKey) {
						tab.AddRow(newRow);
					}
				}
				break;
			case 5:
				break;
			case 6: 
				break;
			case 7: 
				break;
			case 8:
				cout << *(static_cast<string*>(tab[1]["StudentID"])) << endl;
				break;
			case 10:
				return 0;//���������� ������
			default:
				cout<<"������������ ��������. ��������� �����\n"; 
				break;
		}
	}
		return 0;
}
