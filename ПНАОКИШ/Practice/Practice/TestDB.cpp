#include <iostream>
#include <iomanip>
#include"dbmsLib_v1.h"

using namespace std;

const size_t SCREENSIZE = 80;

template <typename T> T ChoiceGetter(const string& foreword = "�������� ��������");
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
        cout << "������ �����. ��������� ����" << endl;   
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
	return choice;
}

int MainMenu() {
    cout << "================= ���� '����������' ===================" << endl;
    cout << "1 - ������ ������� ������ �� �����" << endl;
    cout << "2 - ������ ������� ������" << endl;
    cout << "3 - ������ ������� ������ � �����" << endl;
    cout << "4 - ���������� ������ � �������" << endl;
	cout << "5 - ��������� ������ � ������� (������� �������� � ������ ������, ��������� �����������)" << endl;
    cout << "6 - �������� ������ �� ������� (�� �������� � �������� �������)" << endl;
    cout << "7 - ������������" << endl;  //  DELETE
    cout << "10 - �����" << endl;

	return ChoiceGetter <int> ();
}

int ActionMenu(const string& action) {
    if (action == "Addition") {
		cout << "================= ����� ��� ������ ��������� ��������? ===================" << endl;
	} else if (action == "Editing") {
		cout << "================= ����� ��� ������ ��������� ��������? ===================" << endl;
	} else if (action == "Deletion") {
		cout << "================= ����� ��� ������ ��������� �������? ===================" << endl;
        cout << "��������! �������� �������� ���� ����� �������� �� ����� �������� ��������� �����������!" << endl;
	} else {
		cout << "����� �������� �� ����������" << endl;
		return 10;
	}
	cout << "1 - �������" << endl;
    cout << "2 - �����" << endl;
    cout << "3 - ���������" << endl;
    cout << "10 - �����" << endl;

    return ChoiceGetter <int> ();
}

int StudentEditingMenu() {
	cout << "================= ��� ���������� ������� �� ���������? ===================" << endl;
    cout << "1 - �������� ���" << endl;
    cout << "2 - �������� ������" << endl;
    cout << "10 - �����" << endl;

	return ChoiceGetter <int> ();
}

int BookEditingMenu() {
	cout << "================= ��� ���������� ������� � ������? ===================" << endl;
    cout << "1 - �������� ��������" << endl;
    cout << "2 - �������� ������" << endl;
	cout << "3 - �������� ����� ����������" << endl;
    cout << "10 - �����" << endl;

	return ChoiceGetter <int> ();
}

int AbonementEditingMenu() {
	cout << "================= ��� ���������� ������� � �����������? ===================" << endl;
    cout << "1 - ��������" << endl;
    cout << "2 - �������� ���� ������" << endl;
    cout << "10 - �����" << endl;

	return ChoiceGetter <int> ();
}

//=================================================
int main(){
    system("chcp 1251>nul");
    DBMSFuncs::DBTableSet library("Library");
    while (true) {
        switch (MainMenu()) {
            case 1: {
                cout << "������� ���� �� ����� � ����� ������:" << endl;
                string folderPath;
                cin >> folderPath;
                library.ReadDB(folderPath);
                break;
            }
            case 2:
                library.PrintDB(SCREENSIZE);  // TODO: make table_maket use size_t?
                break;
            case 3: {
                cout << "������� ���� �� �����, � ������� ����� �������� ���� ������:" << endl;
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
							cout << "������� � ����� ��������� ��������� ������� ��� ���� � �������" << endl;
						}
						break;
                    }
                    case 2: {
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);

                        DBMSFuncs::Row BookRow = library["Books"].CreateRow();
                        if ((library["Books"].FindValue("BooksID", BookRow["BooksID"]) == -1)) {
                            library["Books"].AddRow(BookRow);
                        } else {
							cout << "����� � ����� ��������� ��������� ������� ��� ���� � �������" << endl;
						}
						break;
                    }
					case 3: {
						library.PrintDB(SCREENSIZE);

                        DBMSFuncs::Row abonementRow = library["Abonements"].CreateRow();
						int studentIndex = library["Students"].FindValue("StudentID", abonementRow["StudentID"]);
						int bookIndex = library["Books"].FindValue("BookID", abonementRow["BookID"]);
                        if (studentIndex == -1 || bookIndex == 1) {
							cout << "�������� �/��� �����, ���������� � ����������, �� �������" << endl;
							break;
						}

						if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Books"][bookIndex]["Rented"], DBMSFuncs::GreaterOrEqual,
							                      library["Books"][bookIndex]["Quantity"])) {
							cout << "��� ����� � ������ BookID ��� ������" << endl;
							break;
						}

                        int abonementIndex = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
							                                                 "BookID", library["Books"][studentIndex]["BookID"]);
					    if (abonementIndex == -1) {
						    cout << "���� ������� ��� ���� ������ �����" << endl;
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

						string studentID = ChoiceGetter <string> ("������� ID ��������, ������ � ������� ����� ��������");
						int index = library["Students"].FindValue("StudentID", studentID);
						if (index == -1) {
							cout << "�������� � ����� ID �� �������" << endl;
							break;
						}

						switch(StudentEditingMenu()) {
						    case 1: {
								string name = ChoiceGetter <string> ("������� ����� ���");
								library["Students"].EditRow(index, "Name", name);
								break;
							}
							case 2: {
							    string group = ChoiceGetter <string> ("������� ����� ������");
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

						string bookID = ChoiceGetter <string> ("������� ID �����, ������ � ������2 ����� ��������");
						int index = library["Books"].FindValue("BookID", bookID);
						if (index == -1) {
							cout << "����� � ����� ID �� �������" << endl;
							break;
						}

						switch(BookEditingMenu()) {
							case 1: {
								string title = ChoiceGetter <string> ("������� ����� ��������");
								library["Books"].EditRow(index, "Title", title);
								break;
							}
							case 2: {
							    string author = ChoiceGetter <string> ("������� ����� ��� ������");
								library["Books"].EditRow(index, "Author", author);
								break;
							}
							case 3: {
								string quantity = ChoiceGetter <string> ("������� ����� ����������");
								if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Books"][index]["Rented"], DBMSFuncs::LessOrEqual,
									                      DBMSFuncs::GetValue(quantity, "Quantity", library["Books"].GetHeader()))) {
									library["Books"].EditRow(index, "Quantity", quantity);
								} else {
									cout << "���������� �������� ���� �� ����� ��������� ���������� ���������" << endl;
								}
							}
							case 10: default:
								break;
						}
						break;
					}

					case 3: {
						DBMSFuncs::PrintDBTable1(library["Abonements"], SCREENSIZE);

						string studentID = ChoiceGetter <string> ("������� ID ��������, �� �������� ������� ���������, ���������� ���������");
						int studentIndex = library["Students"].FindValue("StudentID", studentID);
						if (studentIndex == -1) {
						    cout << "�������� � ����� ID �� �������" << endl;
							break;
						}

						string bookID = ChoiceGetter <string> ("������� ID ����� �� ����������, ����������� ���������");
						int bookIndex = library["Books"].FindValue("BookID", bookID);
						if (bookIndex == -1) {
						    cout << "����� � ����� ID �� �������" << endl;
							break;
						}

						int index = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
								                                    "BookID", library["Books"][bookIndex]["BookID"]);
						if (index == -1) {
							cout << "���� ������� �� ���� ��� �����" << endl;
							break;
						}

						switch(AbonementEditingMenu()) {
							case 1: {
								string dueDate = ChoiceGetter <string> ("������� ����� ���� ��������");
								if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Abonements"][index]["TakenDate"], DBMSFuncs::LessOrEqual,
										                  DBMSFuncs::GetValue(dueDate, "DueDate", library["Abonements"].GetHeader()))) {
									library["Abonements"].EditRow(index, "DueDate", dueDate);
								} else {
									cout << "���� �������� ����� �� ����� ���� ������ ���� ������" << endl;
								}
								break;
							}
							case 2: {
								string takenDate = ChoiceGetter <string> ("������� ����� ���� ������");
								if (DBMSFuncs::comparator(DBMSFuncs::Int32, library["Abonements"][index]["DueDate"], DBMSFuncs::GreaterOrEqual,
										                  DBMSFuncs::GetValue(takenDate, "TakenDate", library["Abonements"].GetHeader()))) {
									library["Abonements"].EditRow(index, "TakenDate", takenDate);
								} else {
									cout << "���� ������ ����� �� ����� ���� ������ ���� ��������" << endl;
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

						string studentID = ChoiceGetter <string> ("������� ID ��������, ����������� ��������");

						int index = library["Students"].FindValue("StudentID", studentID);
						if (index == -1) {
							cout << "�������� � ����� ID �� �������" << endl;
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

						string bookID = ChoiceGetter <string> ("������� ID �����, ����������� ��������");

						int index = library["Books"].FindValue("BookID", bookID);
						if (index == -1) {
							cout << "����� � ����� ID �� �������" << endl;
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

				        string studentID = ChoiceGetter <string> ("������� ID ��������, �� �������� ������� ���������, ���������� ��������");
						int studentIndex = library["Students"].FindValue("StudentID", studentID);
						if (studentIndex == -1) {
						    cout << "�������� � ����� ID �� �������" << endl;
							break;
						}

						string bookID = ChoiceGetter <string> ("������� ID ����� �� ����������, ����������� ��������");
						int bookIndex = library["Books"].FindValue("BookID", bookID);
						if (bookIndex == -1) {
						    cout << "����� � ����� ID �� �������" << endl;
							break;
						}

						int index = library["Abonements"].FindValue("StudentID", library["Students"][studentIndex]["StudentID"],
								                                    "BookID", library["Books"][bookIndex]["BookID"]);
						if (index == -1) {
							cout << "���� ������� �� ���� ��� �����" << endl;
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
