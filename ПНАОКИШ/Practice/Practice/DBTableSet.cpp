#include <iostream>
#include <string>
#include "dbmsLib_v1.h"
#include "TypeAndStringUtils.h"

DBMSFuncs::DBTableSet::DBTableSet(const string& dbName) {
	this->dbName = dbName;
}

void DBMSFuncs::DBTableSet::ReadDB(const string& folderPath) {
	ifstream dbTables(folderPath + "DBTables.txt", ios_base::in);
	if (!dbTables) {
		cout << "Файл DBTables.txt не найден" << endl;
		dbTables.close();
		return;
	}

	string filenames;
	getline(dbTables, filenames);
	dbTables.close();

	string filename;
	while (!filenames.empty()) {
		splitString(filename, filenames, "|");
		DBTableTxt tab;
		ReadDBTableTxt1(tab, folderPath + filename);
		db[tab.GetTableName()] = tab;
	}
    
	relationsTable = DBTableTxt("Relations");
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

void DBMSFuncs::DBTableSet::PrintDB(const size_t screenwidth) {
	for (auto & it : db) {
		PrintDBTable1(it.second, screenwidth);
	}
}

void DBMSFuncs::DBTableSet::WriteDB(const string& folderPath) {
	ofstream dbTables(folderPath + "DBTables.txt", ios_base::in);
	if (!dbTables) {
		cout << "Не удалось открыть/создать файл DBTables.txt" << endl;
		dbTables.close();
		return;
	}

	for (auto & it : db) {
		dbTables << it.first + ".txt" << '|';
		WriteDBTableTxt1(it.second, folderPath + it.first + ".txt");
	}
	dbTables.seekp(-1, ios_base::cur);
	dbTables << endl;
	dbTables.close();

	WriteDBTableTxt1(relationsTable, folderPath + "TableRelations.txt");
}

DBMSFuncs::Relation DBMSFuncs::DBTableSet::GetRelation1(const string& relationName) {
	for (auto & it : relations) {
		if (it.first == relationName) {
			return it.second;
		}
	}

	cout << "Такой связи между таблицами не найдено" << endl;
	return Relation();
}

DBMSFuncs::Row DBMSFuncs::DBTableSet::ParentRow1(Relation& relation, Row& childRow) {
	return db[relation.parentTable][db[relation.parentTable].FindValue(relation.parentPrimaryKey,
		                                                               childRow[relation.childSecondaryKey])];
}
DBMSFuncs::DBTableTxt DBMSFuncs::DBTableSet::ChildRows1(Relation& relation,Row& parentRow) {
	return SelfRows1(db[relation.childTable], relation.childSecondaryKey, Equal, parentRow[relation.parentPrimaryKey]);
}
