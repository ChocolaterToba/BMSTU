#include <string>
#include "dbmsLib_v1.h"

int DBMSFuncs::DBTableTxt::FindValue(const string& columnName, void* value) {
	TableDataType compType = GetType(columnName, GetHeader());
	for (int i = 0; i < GetSize(); ++i) {
		if (comparator(compType, value, Equal, (*this)[i][columnName])) {
			return i;
		}
	}
	return -1;
}

int DBMSFuncs::DBTableTxt::FindValue(const string& columnName, const string& value) {
	return FindValue(columnName, GetValue(value, columnName,  GetHeader()));
}

int DBMSFuncs::DBTableTxt::FindValue(const string& columnName, void* value, const string& columnName2, void* value2) {
	TableDataType compType = GetType(columnName, GetHeader());
	TableDataType compType2 = GetType(columnName2, GetHeader());
	for (int i = 0; i < GetSize(); ++i) {
		if (comparator(compType, value, Equal, (*this)[i][columnName]) && comparator(compType2, value2, Equal, (*this)[i][columnName2])) {
			return i;
		}
	}
	return -1;
}

int DBMSFuncs::DBTableTxt::FindValue(const string& columnName, const string& value, const string& columnName2, const string& value2) {
	return FindValue(columnName, GetValue(value, columnName,  GetHeader()),
		             columnName2, GetValue(value2, columnName2,  GetHeader()));
}
