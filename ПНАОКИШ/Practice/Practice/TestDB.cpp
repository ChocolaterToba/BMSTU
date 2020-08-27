#include <iostream>
#include <iomanip>
#include"dbmsLib_v1.h"

using namespace std;

const size_t SCREENSIZE = 80;

int MainMenu() {
    cout << "================= ����� ���� ===================\n";
    cout << "\t1 - ������ ������� ������ �� �����\n";
    cout << "\t2 - ������ ������� ������\n";
    cout << "\t3 - ������ ������� ������ � �����\n";
    cout << "\t4 - ���������� ������ � �������\n";
    cout << "\t5 - �������� ������ �� ������� (�� �������� � �������� �������)\n";
    cout << "\t6 - ������������\n";  //  DELETE
    cout << "\t10 - �����\n";

    int choice;
    cout << "�������� ��������\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "������ �����. ��������� ����\n";    
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
    return choice;
}

int AdditionMenu() {
    cout << "================= ����� ��� ������ ��������� ��������? ===================\n";
    cout << "\t1 - �������\n";
    cout << "\t2 - �����\n";
    cout << "\t3 - ���������\n";
    cout << "\t10 - �����\n";

    int choice;
    cout << "�������� ��������\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "������ �����. ��������� ����\n";    
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  //  Skipping the rest of incorrect line.
        cin >> choice;
    }
    return choice;
}

int DeletionMenu() {
    cout << "================= ����� ��� ������ ��������� �������? ===================\n";
    cout << "��������! �������� �������� ���� ����� �������� �� ����� �������� ��������� �����������!/n";
    cout << "\t1 - �������\n";
    cout << "\t2 - �����\n";
    cout << "\t3 - ���������\n";
    cout << "\t10 - �����\n";

    int choice;
    cout << "�������� ��������\n";
    cin >> choice;
    while (cin.fail()) {
        cout << "������ �����. ��������� ����\n";    
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
                switch (AdditionMenu()) {
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
								cout << "��������� � ������ ���������� StudentID � BookID ��� ����������" << endl;
							}
						} else {
							cout << "�������� �/��� �����, ���������� � ����������, �� �������" << endl;
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

						cout << "������� ID ��������, ����������� ��������: ";
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
							cout << "�������� � ����� ID �� �������" << endl;
						}
						break;
                    }
                    case 2: {
						DBMSFuncs::PrintDBTable1(library["Books"], SCREENSIZE);

						cout << "������� ID �����, ���������� ��������: ";
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
							cout << "����� � ����� ID �� �������" << endl;
						}
						break;
                    }
					case 3: {
                        DBMSFuncs::PrintDBTable1(library["Abonements"], SCREENSIZE);

						cout << "������� (����� ������ ���� � ��������� ������) ID �������� � ����� �� ����������, ����������� ��������: ";
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
								cout << "�� ������� ���������� � ����� ����������� ID �������� � �����" << endl;
							}
						} else {
							cout << "�� ������� �������� �/��� ����� � ��������������� ID" << endl;
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
