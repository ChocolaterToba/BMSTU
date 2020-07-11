#include <iostream>
#include <iomanip>
#include"dbmsLib_v1.h"
using namespace std;
int menu(){
	cout<<"================= МАКЕТ СУБД ===================\n";
	cout<<"\t1 - Чтение таблицы из файла\n";
	cout<<"\t2 - Печать таблицы\n";
	cout<<"\t3 - Запись таблицы в файл\n";
	cout<<"\t4 - Добавление записи в таблицу\n";
	cout<<"\t5 - Перевести студента в другую группу\n";
	cout<<"\t6 - Распечатать фамилию студента, StudentID которого равен 3\n";
	cout<<"\t7 - Увеличить на 1 количество экземпляров всех книг в библиотеке \n";
	cout<<"\t8 - Тестирование\n";
	cout<<"\t10 - Выход\n";

	int choice;
	cout<<"Выберите действие\n";
	cin>>choice;
	while(cin.fail()){
	    cout<<"Ошибка ввода. Повторите ввод\n";	
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
							cout << "В таблице уже присутствует запись с таким же значением \
									 первичного ключа. Добавление введённой записи невозможно." << endl;
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
				return 0;//завершение работы
			default:
				cout<<"Недопустимое действие. Повторите выбор\n"; 
				break;
		}
	}
		return 0;
}
