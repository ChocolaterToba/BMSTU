#include "PrintDBTable1.h"
#include "WriteDBTableTxt1.h"

void DBMSFuncs::PrintDBTable1(DBMSFuncs::DBTableTxt& tab, int screenSize) {
	Strip* strips = nullptr;
	int nStrips = 0;
	tab.CreateTableMaket(strips, nStrips, screenSize);
	vector<string> columnNames;  // Vector of all column names - allows to get them by index.
	for (const auto & it : tab.GetHeader()) {
		columnNames.push_back(it.first);
	}

	int columnShift = 0;  //  Amount of columns that were displayed already.
	for (int i = 0; i < nStrips; ++i) {  //  Different strips.
		//  Outputting table name.
		cout << endl;
		if (!i) {
			cout << "Таблица " << tab.GetTableName();
		} else {
			cout << "Продолжение таблицы " << tab.GetTableName();
		}
		cout << endl << string(screenSize, '=') << endl;

		//  Outputting columns' headers and types.
		for (int k = 0; k < strips[i].nField; ++k) {  //  Different columns in header.
			cout << setw(strips[i].fieldWidth[k]) << columnNames[columnShift + k];
		}
		cout << endl;
		for (int k = 0; k < strips[i].nField; ++k) {
			cout << setw(strips[i].fieldWidth[k]) << typeToString(tab.GetHeader()[columnNames[columnShift + k]].colType);
		}
		cout << endl << string(screenSize, '-') << endl;

		//  Outputting actual data.
		for (int j = 0; j < tab.GetSize(); ++j) {  //  Different rows in strips.
			for (int k = 0; k < strips[i].nField; ++k) {  //  Different columns in rows.
				cout << setw(strips[i].fieldWidth[k])
				     << tab.valueToString(tab[j], columnNames[columnShift + k]);
			}
			cout << endl;
		}
		columnShift += strips[i].nField;
		cout << string(screenSize, '=') << endl;
	}
}