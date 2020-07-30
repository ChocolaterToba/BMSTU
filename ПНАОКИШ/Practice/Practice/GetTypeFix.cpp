#include <string>
#include "dbmsLib_v1.h"

DBMSFuncs::TableDataType DBMSFuncs::GetType(string columnName, Header hdr) {
	return hdr[columnName].colType;
}

void DBMSFuncs::DBTableSet::OutputTableNames() {
	for (const auto & it: db) {
		cout << it.first << endl;
	}
	cout << "The End." << endl;
}

int DBMSFuncs::DBTableSet::GetSize() {
	return db.size();
}
