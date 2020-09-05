#include <iostream>
#include <iomanip>
#include"dbmsLib_v1.h"

using namespace std;

const size_t SCREENSIZE = 80;

template <typename T> T ChoiceGetter(const string& foreword = "Выберите действие");
template <> string ChoiceGetter(const string& foreword) {
	string choice;
	cout << foreword << ":" << endl;
	if (cin.peek() == '\n') {
		cin.ignore();  //  Skipping linebreak added during input
	}
    getline(cin, choice);
	return choice;
}

template <> int ChoiceGetter(const string& foreword) {
	int choice;
	cout << foreword << ":" << endl;
    cin >> choice;
    while (cin.fail()) {
        cout << "Ошибка ввода. Повторите ввод" << endl;   
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
	return choice;
}

int MainMenu() {
    cout << "================= СУБД 'Библиотека' ===================" << endl;
    cout << "1 - Чтение системы таблиц из папки" << endl;
    cout << "2 - Печать системы таблиц" << endl;
    cout << "3 - Запись системы таблиц в папку" << endl;
    cout << "4 - Добавление записи в таблицу" << endl;
	cout << "5 - Изменение записи в таблице (Перевод студента в другую группу, продление абонементов)" << endl;
    cout << "6 - Удаление записи из таблицы (по значению в ключевом столбце)" << endl;
    cout << "7 - Тестирование" << endl;  //  DELETE
    cout << "10 - Выход" << endl;

	return ChoiceGetter <int> ();
}

int ActionMenu(const string& action) {
    if (action == "Addition") {
		cout << "================= Какой тип записи требуется добавить? ===================" << endl;
	} else if (action == "Editing") {
		cout << "================= Какой тип записи требуется изменить? ===================" << endl;
	} else if (action == "Deletion") {
		cout << "================= Какой тип записи требуется удалить? ===================" << endl;
        cout << "Внимание! Удаление студента либо книги повлечёт за собой удаление связанных абонементов!" << endl;
	} else {
		cout << "Такое действие не определено" << endl;
		return 10;
	}
	cout << "1 - Студент" << endl;
    cout << "2 - Книга" << endl;
    cout << "3 - Абонемент" << endl;
    cout << "10 - Назад" << endl;

    return ChoiceGetter <int> ();
}

int StudentEditingMenu() {
	cout << "================= Что необходимо сделать со студентом? ===================" << endl;
    cout << "1 - Изменить имя" << endl;
    cout << "2 - Изменить группу" << endl;
    cout << "10 - Выход" << endl;

	return ChoiceGetter <int> ();
}

int BookEditingMenu() {
	cout << "================= Что необходимо сделать с книгой? ===================" << endl;
    cout << "1 - Изменить название" << endl;
    cout << "2 - Изменить автора" << endl;
	cout << "3 - Изменить общее количество" << endl;
    cout << "10 - Выход" << endl;

	return ChoiceGetter <int> ();
}

int AbonementEditingMenu() {
	cout << "================= Что необходимо сделать с абонементом? ===================" << endl;
    cout << "1 - Продлить" << endl;
    cout << "2 - Изменить дату выдачи" << endl;
    cout << "10 - Выход" << endl;

	return ChoiceGetter <int> ();
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
				switch (ActionMenu("Addition")) {
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
						library.PrintDB(SCREENSIZE);

                        DBMSFuncs::Row abonementRow = library["Abonements"].CreateRow();
						int studentIndex = library["Students"].FindValue("StudentID", abonementRow["StudentID"]);
						int bookIndex = library["Books"].FindValue("BookID", abonementRow["BookID"]);
                        if (studentIndex == -1 || bookIndex == 1) {
							cout << "Студента и/или книги, упомянутых в абонементе, не найдено" << endl;
							break;
						}

						if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Books"][bookIndex]["Rented"], DBMSFuncs::GreaterOrEqual,
							                      library["Books"][bookIndex]["Quantity"])) {
							cout << "Все книги с данным BookID уже выданы" << endl;
							break;
						}

                        int abonementIndex = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
							                                                 "BookID", library["Books"][studentIndex]["BookID"]);
					    if (abonementIndex == -1) {
						    cout << "Этот студент уже взял данную книгу" << endl;
							break;
					    }

						library["Abonements"].AddRow(abonementRow);

						int booksRented = stoi(library["Books"].valueToString(library["Books"][bookIndex], "Rented"));
						library["Books"].EditRow(bookIndex, "Rented", to_string(++booksRented));  //  Adding 1 to the amount of books rented.
						break;
                    }
					case 10: default:
						break;
				}
				break;

			case 5:
				switch(ActionMenu("Editing")) {
				    case 1: {
						DBMSFuncs::PrintDBTable1(library["Students"], SCREENSIZE);

						string studentID = ChoiceGetter <string> ("Введите ID студента, запись о котором нужно изменить");
						int index = library["Students"].FindValue("StudentID", studentID);
						if (index == -1) {
							cout << "Студента с таким ID не найдено" << endl;
							break;
						}

						switch(StudentEditingMenu()) {
						    case 1: {
								string name = ChoiceGetter <string> ("Введите новое имя");
								library["Students"].EditRow(index, "Name", name);
								break;
							}
							case 2: {
							    string group = ChoiceGetter <string> ("Введите новую группу");
								library["Students"].EditRow(index, "Group", group);
								break;
							}
							case 10: default:
								break;
						}
						break;
					}

					case 2: {
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);

						string bookID = ChoiceGetter <string> ("Введите ID книги, запись о которо2 нужно изменить");
						int index = library["Books"].FindValue("BookID", bookID);
						if (index == -1) {
							cout << "Книги с таким ID не найдено" << endl;
							break;
						}

						switch(BookEditingMenu()) {
							case 1: {
								string title = ChoiceGetter <string> ("Введите новое название");
								library["Books"].EditRow(index, "Title", title);
								break;
							}
							case 2: {
							    string author = ChoiceGetter <string> ("Введите новое имя автора");
								library["Books"].EditRow(index, "Author", author);
								break;
							}
							case 3: {
								string quantity = ChoiceGetter <string> ("Введите новое количество");
								if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Books"][index]["Rented"], DBMSFuncs::LessOrEqual,
									                      DBMSFuncs::GetValue(quantity, "Quantity", library["Books"].GetHeader()))) {
									library["Books"].EditRow(index, "Quantity", quantity);
								} else {
									cout << "Количество выданных книг не может превышать количество имеющихся" << endl;
								}
							}
							case 10: default:
								break;
						}
						break;
					}

					case 3: {
						DBMSFuncs::PrintDBTable1(library["Abonements"], SCREENSIZE);

						string studentID = ChoiceGetter <string> ("Введите ID студента, на которого выписан абонемент, подлежащий изменению");
						int studentIndex = library["Students"].FindValue("StudentID", studentID);
						if (studentIndex == -1) {
						    cout << "Студента с таким ID не найдено" << endl;
							break;
						}

						string bookID = ChoiceGetter <string> ("Введите ID книги из абонемента, подлежащего изменению");
						int bookIndex = library["Books"].FindValue("BookID", bookID);
						if (bookIndex == -1) {
						    cout << "Книги с таким ID не найдено" << endl;
							break;
						}

						int index = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
								                                    "BookID", library["Books"][bookIndex]["BookID"]);
						if (index == -1) {
							cout << "Этот студент не брал эту книгу" << endl;
							break;
						}

						switch(AbonementEditingMenu()) {
							case 1: {
								string dueDate = ChoiceGetter <string> ("Введите новую дату возврата");
								if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Abonements"][index]["TakenDate"], DBMSFuncs::LessOrEqual,
										                  DBMSFuncs::GetValue(dueDate, "DueDate", library["Abonements"].GetHeader()))) {
									library["Abonements"].EditRow(index, "DueDate", dueDate);
								} else {
									cout << "Дата возврата книги не может быть меньше даты выдачи" << endl;
								}
								break;
							}
							case 2: {
								string takenDate = ChoiceGetter <string> ("Введите новую дату выдачи");
								if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Abonements"][index]["DueDate"], DBMSFuncs::GreaterOrEqual,
										                  DBMSFuncs::GetValue(takenDate, "TakenDate", library["Abonements"].GetHeader()))) {
									library["Abonements"].EditRow(index, "TakenDate", takenDate);
								} else {
									cout << "Дата выдачи книги не может быть больше даты возврата" << endl;
								}
								break;
							}
							case 10: default:
								break;
						}
						break;
					}
				    default:
					    break;
				}
				break;

            case 6:
                switch (ActionMenu("Deletion")) {
                    case 1: {
						DBMSFuncs::PrintDBTable1(library["Students"], SCREENSIZE);

						string studentID = ChoiceGetter <string> ("Введите ID студента, подлежащего удалению");

						int index = library["Students"].FindValue("StudentID", studentID);
						if (index == -1) {
							cout << "Студента с таким ID не найдено" << endl;
							break;
						}

						library["Students"].RemoveRow(index);

						index = library["Abonements"].FindValue("StudentID", studentID);
						while (index != -1) {  //  Removing all abonements related to this student.
							library["Abonements"].RemoveRow(index);
							index = library["Abonements"].FindValue("StudentID", studentID);
						}
						break;
                    }
                    case 2: {
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);

						string bookID = ChoiceGetter <string> ("Введите ID книги, подлежащего удалению");

						int index = library["Books"].FindValue("BookID", bookID);
						if (index == -1) {
							cout << "Книги с таким ID не найдено" << endl;
							break;
						}

						library["Books"].RemoveRow(index);

						index = library["Abonements"].FindValue("BookID", bookID);
						while (index != -1) {  //  Removing all abonements related to this book.
							library["Abonements"].RemoveRow(index);
							index = library["Abonements"].FindValue("BookID", bookID);
						}
						break;
                    }
					case 3: {
                        DBMSFuncs::PrintDBTable1(library["Abonements"], SCREENSIZE);

				        string studentID = ChoiceGetter <string> ("Введите ID студента, на которого выписан абонемент, подлежащий удалению");
						int studentIndex = library["Students"].FindValue("StudentID", studentID);
						if (studentIndex == -1) {
						    cout << "Студента с таким ID не найдено" << endl;
							break;
						}

						string bookID = ChoiceGetter <string> ("Введите ID книги из абонемента, подлежащего удалению");
						int bookIndex = library["Books"].FindValue("BookID", bookID);
						if (bookIndex == -1) {
						    cout << "Книги с таким ID не найдено" << endl;
							break;
						}

						int index = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
								                                    "BookID", library["Books"][bookIndex]["BookID"]);
						if (index == -1) {
							cout << "Этот студент не брал эту книгу" << endl;
							break;
						}
						
						library["abonements"].RemoveRow(index);

						int booksRented = stoi(library["Books"].valueToString(library["Books"][bookIndex], "Rented"));
						library["Books"].EditRow(bookIndex, "Rented", to_string(--booksRented));  //  Substracting 1 from the amount of books rented.
                    }
					case 10: default:
						break;
				}	
				break;
            case 7: {
                library.ReadDB("..\\library\\");
                break;
                }
            case 10:
                return 0;
        }
		cout << endl;
    }
    system("pause");
    return 0;
}
