#include "dbmsLib_v1.h"
#include "TypeAndStringUtils.h"

void DBMSFuncs::ReadDBTableTxt1(DBTableTxt& tab, const string& fileName) {
	tab.data.clear();
	tab.columnHeaders.clear();

	tab.fileName = fileName;  //  Legacy code, I don't need this in my implementation.
	ifstream infile(fileName, ios_base::in);
	if (!infile) {
		infile.close();
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
	    		row[columnName] = GetValue(ignoreBlanc(valueString), columnName, tab.columnHeaders);
	    	}
	    	tab.data.push_back(row);
		}
	}

	infile.close();
}
