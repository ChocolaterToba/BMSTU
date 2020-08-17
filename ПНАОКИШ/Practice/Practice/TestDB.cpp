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
	cout<<"\t5 - Удаление записи из таблицы (по значению в ключевом столбце)\n";
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
	DBMSFuncs::DBTableSet library("Library");
	library.ReadDB("..\\Library\\");  // 2 backslashes due to '\' being an escape character.
	library.WriteDB("..\\Library\\");
	library.ReadDB("..\\Library\\");
	library.PrintDB1(80);
	system("pause");

	//TODO: Write functions that use DBTableSet to  add students/ababonements/books and do otheher essential/cool stuff.
	return 0;
}
