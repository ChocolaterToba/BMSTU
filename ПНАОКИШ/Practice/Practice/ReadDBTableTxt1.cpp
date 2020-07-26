#include "dbmsLib_v1.h"
#include "ReadDBTableTxt1.h"

void DBMSFuncs::ReadDBTableTxt1(DBTableTxt& tab,string fileName) {
	tab.data.clear();
	tab.columnHeaders.clear();

	tab.fileName = fileName;
	ifstream infile(fileName, ios_base::in);
	if (!infile) {
		return;
	}

	string tableTop;
	getline(infile, tableTop);
	splitString(tab.tableName, tableTop, "|");
	tab.primaryKey = tableTop;

	string tableHeaders;
	getline(infile, tableHeaders);

	vector<string> columnNames;  //  A vector of column names in order they appear in file.
	while (!tableHeaders.empty()) {
		string columnName;
	    splitString(columnName, tableHeaders, "|");
		columnNames.push_back(columnName);

	    char columnNameChar[LENGTH];
	    strcpy_s(columnNameChar, LENGTH, columnName.c_str());

	    string columnType;
	    splitString(columnType, tableHeaders, "|");

	    string length;
	    splitString(length, tableHeaders, "|");

		tab.columnHeaders[columnName] = ColumnDesc(columnNameChar, stringToType(columnType), stoi(length));
	}
	
	while (infile.peek() != EOF) {
	    string tableRowString;
		getline(infile, tableRowString);
	    while (!tableRowString.empty()) {
	    	Row row;
	    	for (const string& columnName : columnNames) {
	    		string valueString;
	    		splitString(valueString, tableRowString, "|");
	    		row[columnName] = GetValue(valueString, columnName, tab.columnHeaders);
	    	}
	    	tab.data.push_back(row);
		}
	}

	infile.close();
}

DBMSFuncs::TableDataType DBMSFuncs::stringToType(const string& typeName) {
    TableDataType result;
	if (typeName == "Int32") {
		result = Int32;
	} else if (typeName == "Double") {
		result = Double;
	} else if (typeName == "String") {
		result = String;
	} else if (typeName == "Date") {
		result = Date;
	} else {  // NoType can also be used as default case.
		result = NoType;
	}
	return result;
}

void splitString(string& target, string& origin, const string& delim) {
    size_t delimPos = origin.find(delim);
	target = origin.substr(0, delimPos);

	if (delimPos != string::npos) {
		origin = origin.substr(delimPos + delim.length());
	} else {
		origin.clear();
	}
}