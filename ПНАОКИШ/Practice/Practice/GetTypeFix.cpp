#include <string>
#include "dbmsLib_v1.h"

DBMSFuncs::TableDataType DBMSFuncs::GetType(string& columnName, Header& hdr) {
	return hdr[columnName].colType;
}

void DBMSFuncs::DBTableSet::OutputTables() {
	for (auto & it: db) {
		PrintDBTable1(it.second, 80);
	}
	cout << "The End." << endl;
}

int DBMSFuncs::DBTableSet::GetSize() {
	return db.size();
}
