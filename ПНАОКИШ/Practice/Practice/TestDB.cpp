#include <iostream>
#include <iomanip>
#include"dbmsLib_v1.h"

using namespace std;

const size_t SCREENSIZE = 80;

int MainMenu() {
    cout << "================= МАКЕТ СУБД ===================\n";
    cout << "\t1 - Чтение системы таблиц из папки\n";
    cout << "\t2 - Печать системы таблиц\n";
    cout << "\t3 - Запись системы таблиц в папку\n";
    cout << "\t4 - Добавление записи в таблицу\n";
    cout << "\t5 - Удаление записи из таблицы (по значению в ключевом столбце)\n";
    cout << "\t6 - Тестирование\n";  //  DELETE
    cout << "\t10 - Выход\n";

    int choice;
    cout << "Выберите действие\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";    
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
    return choice;
}

int AdditionMenu() {
    cout << "================= Какой тип записи требуется добавить? ===================\n";
    cout << "\t1 - Студент\n";
    cout << "\t2 - Книга\n";
    cout << "\t3 - Абонемент\n";
    cout << "\t10 - Назад\n";

    int choice;
    cout << "Выберите действие\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";    
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
    return choice;
}

int DeletionMenu() {
    cout << "================= Какой тип записи требуется удалить? ===================\n";
    cout << "Внимание! Удаление студента либо книги повлечёт за собой удаление связанных абонементов!/n";
    cout << "\t1 - Студент\n";
    cout << "\t2 - Книга\n";
    cout << "\t3 - Абонемент\n";
    cout << "\t10 - Назад\n";

    int choice;
    cout << "Выберите действие\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод\n";    
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
    return choice;
}

//=================================================
int main(){
    system("chcp 1251>nul");
    DBMSFuncs::DBTableSet library("Library");
    while (true) {
        switch (MainMenu()) {
            case 1: {
                cout << "Введите путь до папки с базой данных:" << endl;
                string folderPath;
                cin >> folderPath;
                library.ReadDB(folderPath);
                break;
            }
            case 2:
                library.PrintDB(SCREENSIZE);  // TODO: make table_maket use size_t?
                break;
            case 3: {
                cout << "Введите путь до папки, в которую нужно записать базу данных:" << endl;
                string folderPath;
                cin >> folderPath;
                library.WriteDB(folderPath);
                break;
            }
            case 4:
                switch (AdditionMenu()) {
                    case 1: {
						DBMSFuncs::PrintDBTable1(library["Students"], SCREENSIZE);

                        DBMSFuncs::Row studentRow = library["Students"].CreateRow();
                        if ((library["Students"].FindValue("StudentID", studentRow["StudentID"]) == -1)) {
                            library["Students"].AddRow(studentRow);
                        } else {
							cout << "Студент с таким значением ключевого столбца уже есть в таблице" << endl;
						}
						break;
                    }
                    case 2: {
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);

                        DBMSFuncs::Row BookRow = library["Books"].CreateRow();
                        if ((library["Books"].FindValue("BooksID", BookRow["BooksID"]) == -1)) {
                            library["Books"].AddRow(BookRow);
                        } else {
							cout << "Книга с таким значением ключевого столбца уже есть в таблице" << endl;
						}
						break;
                    }
					case 3: {
						DBMSFuncs::PrintDBTable1(library["Students"], SCREENSIZE);
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);
						DBMSFuncs::PrintDBTable1(library["Abonements"], SCREENSIZE);

                        DBMSFuncs::Row abonementRow = library["Abonements"].CreateRow();
						int studentIndex = library["Students"].FindValue("StudentID", abonementRow["StudentID"]);
						int bookIndex = library["Books"].FindValue("BookID", abonementRow["BookID"]);
                        if (studentIndex != -1 && bookIndex != 1) {
							int abonementIndex = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
								                                                 "BookID", library["Books"][studentIndex]["BookID"]);
							if (abonementIndex != -1) {
							    library["Abonements"].AddRow(abonementRow);
							} else {
								cout << "Абонемент с такими значениями StudentID и BookID уже существует" << endl;
							}
						} else {
							cout << "Студента и/или книги, упомянутых в абонементе, не найдено" << endl;
						}
						break;
                    }
					case 10: default:
						break;
                }
				break;
            case 5:
                switch (DeletionMenu()) {
                    case 1: {
						DBMSFuncs::PrintDBTable1(library["Students"], SCREENSIZE);

						cout << "Введите ID студента, подлежащего удалению: ";
						string studentID;
						cin >> studentID;

						int index = library["Students"].FindValue("StudentID", studentID);
						if (index != -1) {
							library["Students"].RemoveRow(index);

							index = library["Abonements"].FindValue("StudentID", studentID);
							while (index != -1) {  //  Removing all abonements related to this student.
								library["Abonements"].RemoveRow(index);
								index = library["Abonements"].FindValue("StudentID", studentID);
							}
						} else {
							cout << "Студента с таким ID не найдено" << endl;
						}
						break;
                    }
                    case 2: {
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);

						cout << "Введите ID книги, подлежащей удалению: ";
						string bookID;
						cin >> bookID;

						int index = library["Books"].FindValue("BookID", bookID);
						if (index != -1) {
							library["Books"].RemoveRow(index);

							index = library["Abonements"].FindValue("BookID", bookID);
							while (index != -1) {  //  Removing all abonements related to this book.
								library["Abonements"].RemoveRow(index);
								index = library["Abonements"].FindValue("BookID", bookID);
							}
						} else {
							cout << "Книги с таким ID не найдено" << endl;
						}
						break;
                    }
					case 3: {
                        DBMSFuncs::PrintDBTable1(library["Abonements"], SCREENSIZE);

						cout << "Введите (через пробел либо с переводом строки) ID студента и книги из абонемента, подлежащего удалению: ";
						string studentID;
						string bookID;
						cin >> studentID >> bookID;

						int studentIndex = library["Students"].FindValue("StudentID", studentID);
						int bookIndex = library["Books"].FindValue("BookID", bookID);

						if (studentIndex != -1 && bookIndex != 1) {
							int abonementIndex = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
								                                                 "BookID", library["Books"][studentIndex]["BookID"]);
							if (abonementIndex != -1) {
								library["abonements"].RemoveRow(abonementIndex);
							} else {
								cout << "На найдено абонемента с такой комбинацией ID студента и книги" << endl;
							}
						} else {
							cout << "Не найдено студента и/или книги с соответствующем ID" << endl;
						}
                    }
					case 10: default:
						break;
                }
				break;
            case 6: {
                cout << DBMSFuncs::GetTabNameFromPath("../Library/Books.txt");
                break;
                }
            case 10:
                return 0;
        }
    }
    system("pause");
    return 0;
}
