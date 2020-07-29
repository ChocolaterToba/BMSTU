#include <iomanip>
#include "dbmsLib_v1.h"
#include "TypeAndStringUtils.h"


void DBMSFuncs::WriteDBTableTxt1(DBTableTxt& tab, string fileName) {
	ofstream outfile(fileName, ios_base::out);
	if (!outfile) {
		return;
	}
	outfile << tab.tableName << '|' << tab.primaryKey << endl;
	for (const auto& it : tab.GetHeader()) {
	    outfile << it.first << '|' << typeToString(it.second.colType)
			    << '|' << it.second.length << '|';
	}
	outfile.seekp(-1, ios_base::cur);
	outfile << endl;  //  Replacing '|' with linebreak.

	for (int i = 0; i < tab.GetSize(); ++i) {
		for (const auto& it : tab.GetHeader()) {
			outfile << setw(it.second.length) << tab.valueToString(tab[i], it.first) << '|';
		}
		outfile.seekp(-1, ios_base::cur);
	    outfile << endl;
	}
	outfile.close();
}
