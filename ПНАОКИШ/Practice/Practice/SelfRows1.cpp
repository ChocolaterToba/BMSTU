#include <string>
#include "dbmsLib_v1.h"

DBMSFuncs::DBTableTxt DBMSFuncs::SelfRows1(DBTableTxt& tab, string columnName, Condition cond, void* value) {
	DBTableTxt newTab;
	newTab.tableName = tab.tableName;
	newTab.primaryKey = tab.primaryKey;
	newTab.fileName = tab.fileName;
	newTab.columnHeaders = tab.columnHeaders;
	TableDataType compType = GetType(columnName, tab.GetHeader());
	for (int i = 0; i < tab.GetSize(); ++i) {
		if (comparator(compType, value, Equal, tab[i][columnName])) {
			Row newRow;
			for (const auto & it : tab[i]) {
				newRow[it.first] = GetValue(tab.valueToString(tab[i], it.first), it.first, tab.GetHeader());
			}
			newTab.data.push_back(newRow);
		}
	}
	return newTab;
}
