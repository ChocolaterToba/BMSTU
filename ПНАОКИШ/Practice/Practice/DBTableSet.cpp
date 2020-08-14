#include <iostream>
#include <string>
#include "dbmsLib_v1.h"
#include "TypeAndStringUtils.h"

DBMSFuncs::DBTableSet::DBTableSet(const string& dbName) {
	this->dbName = dbName;
}

void DBMSFuncs::DBTableSet::ReadDB(const string& folderPath) {
	ifstream dbTableFile(folderPath + "DBTables.txt", ios_base::in);
	if (!dbTableFile) {
		cout << "Файл DBTables.txt не найден" << endl;
		return;
	}

	ifstream dbRelationsFile(folderPath + "TableRelations.txt", ios_base::in);
	if (!dbRelationsFile) {
		cout << "Файл TableRelations.txt не найден" << endl;
		return;
	}
	dbRelationsFile.close();  //  There might be a better way.

	this->folderPath = folderPath;

	string filenames;
	getline(dbTableFile, filenames);
	dbTableFile.close();

	string filename;
	while (!filenames.empty()) {
		splitString(filename, filenames, "|");
		DBTableTxt tab;
		ReadDBTableTxt1(tab, folderPath + filename);
		db[tab.GetTableName()] = tab;
	}
    
	DBTableTxt relationsTable("Relations");
	ReadDBTableTxt1(relationsTable, folderPath + "\\TableRelations.txt");
	for (int i = 0; i < relationsTable.GetSize(); ++i) {
		Relation relation;
		relation.relationName = relationsTable.valueToString(relationsTable[i], "RelationName");
		relation.childSecondaryKey= relationsTable.valueToString(relationsTable[i], "ChildSecondaryKey");
		relation.childTable= relationsTable.valueToString(relationsTable[i], "ChildTable");
		relation.parentPrimaryKey = relationsTable.valueToString(relationsTable[i], "ParentPrimaryKey");
		relation.parentTable = relationsTable.valueToString(relationsTable[i], "ParentTable");
		relations[relation.relationName] = relation;
	}
}

void DBMSFuncs::DBTableSet::PrintDB(int screenwidth) {
	for (auto & it : db) {
		PrintDBTable1(it.second, screenwidth);
	}
}
