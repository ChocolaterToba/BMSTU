#include <string>
#include "dbmsLib_v1.h"

void DBMSFuncs::DBTableTxt::RemoveRow(int rowIndex) {
	if (rowIndex < GetSize()) {
		data.erase(data.begin() + rowIndex);
	}
}

void DBMSFuncs::DBTableTxt::EditRow(int rowIndex, const string& columnName, string& value) {
	if (rowIndex < GetSize()) {  //  Just in case.
		delete (*this)[rowIndex][columnName];
		(*this)[rowIndex][columnName] = GetValue(value, columnName, GetHeader());
	}
}