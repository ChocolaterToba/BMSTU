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
				{
					cout << "Введите ID студента, которого необходимо перевести:" << endl;
					int studentID;
					cin >> studentID;
					bool studentFound = false;
					// Should be size_t but dumbos who made the lib chose to use int.
					for (int i = 0; i < tab.GetSize(); ++i) {
						if (*(static_cast<int*>(tab[i]["StudentID"])) == studentID) {
						    cout << "Студент найден. Введите группу, в которую его нужно перевести:" << endl;
							cin >> *(static_cast<string*>(tab[i]["Group"]));
							studentFound = true;
							break;
						}
					}

					if (!studentFound) {
						cout << "Студент не найден." << endl;
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
				return 0;//завершение работы
			default:
				cout<<"Недопустимое действие. Повторите выбор\n"; 
				break;
		}
	}
		return 0;
}
