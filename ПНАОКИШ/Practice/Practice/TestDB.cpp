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
				ReadDBTableTxt1(tab, "Student.txt");
				break;
			case 2:
				PrintDBTable1(tab, 80);
				break;
			case 3:
				WriteDBTableTxt1(tab, "Student.txt");
				break;
			case 4:
				{
					DBMSFuncs::Row newRow = tab.CreateRow();

					string primaryKey = tab.GetPrimaryKey();
					DBMSFuncs::TableDataType type = tab.GetHeader()[primaryKey].colType;  // type is datatype of primary column.
					bool similarKey = false;  // shows if there's a row with same value in the key column.
					// Should be size_t but dumbos who made the lib chose to use int.
					for (int i = 0; i < tab.GetSize(); ++i) {
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
				{
					cout << "������� ID ��������, �������� ���������� ���������:" << endl;
					int studentID;
					cin >> studentID;
					bool studentFound = false;
					// Should be size_t but dumbos who made the lib chose to use int.
					for (int i = 0; i < tab.GetSize(); ++i) {
						if (*(static_cast<int*>(tab[i]["StudentID"])) == studentID) {
						    cout << "������� ������. ������� ������, � ������� ��� ����� ���������:" << endl;
							cin >> *(static_cast<string*>(tab[i]["Group"]));
							studentFound = true;
							break;
						}
					}

					if (!studentFound) {
						cout << "������� �� ������." << endl;
					}
				}
				break;
			case 6: 
				break;
			case 7: 
				break;
			case 8:
				PrintDBTable1(tab, 80);
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
