//файл DBMSFuncsLib.h
#pragma once
#ifndef _DBMSFuncsLib_
#define _DBMSFuncsLib_
#include <iostream>
#include <strstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;
namespace DBMSFuncs
{
  //-----------------класс DBDate----------------------------
  class DBDate
  {    
        static const int arrDays[13];
        friend string DateToStr(DBDate& date);
        friend ostream& operator<<(ostream& out,DBDate& date);
        int day, month, year;
    public:
        DBDate(string date);  //  Формат строки: dd.mm.yyyy
        DBDate(int d,int m,int y);
        DBDate():day(0),month(0),year(0){};  //  Конструктор по умолчанию
        DBDate(DBDate& dat):day(dat.day),month(dat.month),year(dat.year){}

        int GetDay();
        int GetMonth();
        int GetYear();

        bool IsLeapYear (int year);  //  Год высокосный?
        int GetDaysInMonth(int month,int year);  //  Количество дней в месяце
        int DaysInCurYear();  //  Количество дней от начала года до текущей даты

        bool operator==(DBDate& date);
        bool operator<(DBDate& date); 
        bool operator>(DBDate& date);
        bool operator<= (DBDate& date);
        bool operator>= (DBDate& date);
        bool operator!= (DBDate& date);

        DBDate& operator+=(int days);  //  Прибавляет к текущей дате days дней
        DBDate& operator-=(int days);  //  Вычитает из текущей даты days дней
        int operator-(DBDate& date);  //  Количество дней между текущей датой и date
                                      //  Если текущая дата > date, результат < 0.
  };

//======TableDataType-перечисление типов полей таблиц БД====== 
enum TableDataType {
 NoType,
 Int32,
 Double,
 String,
 Date
};

const int LENGTH = 24;  //  Размер полей для имени таблицы и имени столбца. 
//  Для выравнивания длин имён используются ведущие пробелы.
//  ColumnDesc - описание данных в столбце таблицы 
//  данные типа string имеют одинаковую длину (length) внутри одного столбца, 
//  но в разных столбцах их длина может отличаться. 
  struct ColumnDesc { 
    char colName[LENGTH];  //  Имя столбца
    TableDataType colType;  //  Тип данных в столбце таблицы
    int length;  //  Максимальное число символов в текстовом представлении 
                 //  данных столбца, включая обязятельный '\0' для типа String
    ColumnDesc(){};
    ColumnDesc( char * name, TableDataType type, int len){ 
        strcpy_s(colName,name);
        colType=type;
        length=len; 
    } 
};

  struct Strip{  //  Полоса распечатки таблицы
    int nField;  //  Число полей 
    int* fieldWidth;  //  Ширина полей в столбцах полосы  
  };                  //  с учетом интервалов и длины имени столбца

  typedef map<string, void*> Row;
  typedef map<string, ColumnDesc> Header;

  enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};

  TableDataType GetType(const string& columnName, Header& hdr);  //  Не работает, фикс в файле GetTypeFix.cpp.

  string GetTabNameFromPath(string path);  //  idk что это такое.
  string ignoreBlanc(const string str);  //  Убирает пробелы из начала строки.

  void* GetValue(string value, string columnName, Header hdr);
  bool comparator(TableDataType type, void *obj1, Condition condition, void *obj);

  //--------------------класс DBTableTxt-----------------------------
  class DBTableTxt
  {
    private:
        string tableName;
        string primaryKey;  //  Имя столбца, являющегося первичным ключом (значения полей
    //  в этом столбце должны быть уникальными). Необходим только в "основных" таблицах.
    //  Во "вспомогательных" таблицах, включаемых в реляционные БД для создания связей
    //  между таблицами типа "многие-ко-многим", он не используется (в файле его нет). 
    //  Примеры "вспомогательных" таблиц: Abonements, OrderDetails. В них записи 
    //  идентифицируются комбинацией ключей связываемых таблиц. 
    //  Значение по умолчанию "NoPrimaryKey" будем использовать как признак того, что объект
    //  DBTableTxt связан с вспомогательной таблицей. 
    //  Имя таблицы и имя первичного ключа таблицы будем хранить в первой строке
    //  табличного файла. Вторая строка табличного файла содержит заголок таблицы.
    //  В файле "DBTables" будем хранить имена файлов с таблицами БД.
        string fileName;
        Header columnHeaders;
        vector<Row> data;
    public:
        DBTableTxt(){}
        DBTableTxt(string tabName): tableName(tabName){}
        ~DBTableTxt(){}

        string valueToString(Row& row, string columnName);

        void ReadTableTxt(string tabName);  //  tabName=path+tableName
        void ReadTableBin(string tabName);  //  Чтение таблицы из бинарного файла
        void PrintTable(int screenWidth);  //  Печать таблицы
        void WriteTableTxt(string tabName);  //  tabName=path+tableName    
        void WriteTableBin(string tabName);  //  Запись таблицы в бинарный файл

        int GetSize();
        Row& operator[](int ind);
        string GetTableName();
        string GetPrimaryKey(){return primaryKey;}
        Header GetHeader();
        string GetFileName(){return fileName;}

        void SetHeader(Header& hdr);
        void SetFileName(string path){fileName=path+"//"+tableName+".txt";}

        Row CreateRow();
        void AddRow(Row row);  //  При добавлении строки копируются не ссылки, а сами значения.
        void RemoveRow(int rowIndex);
		void EditRow(int rowIndex, const string& columnName, string& value);  //  Замена значения с индексами [rowIndex][columnName].
		int FindValue(const string& columnName, void* value);  //  Нахождение самой первой строчки с нужным значением столбца.
		int FindValue(const string& columnName, const string& value);  //  Использовать строку зачастую удобнее.
		int FindValue(const string& columnName, void* value, const string& columnName2, void* value2);  //  Поиск по 2 столбцам за раз.
		int FindValue(const string& columnName, const string& value, const string& columnName2, const string& value2);
        DBTableTxt SelfRows(string columnName, Condition cond, void* value);  //  Запросы к БД.

        //  Макет распечатки таблицы:
        //  screenWidth - ширина экрана (входной параметр)
        //  nStrips - число полос в распечатке (выходной параметр)
        //  strips[nStrips] - описание полос таблицы: 
        //  число столбцов и ширина каждого столбца в полосе (выходной параметр)
        void CreateTableMaket(Strip*& strips, int& nStrips, int screenWidth);

        friend void WriteDBTableTxt1(DBTableTxt& tab, const string& fileName);
        friend void WriteDBTableBin1(DBTableTxt& tab, const string& fileName);
        friend void PrintDBTable1(DBTableTxt& tab, const int screenSize);
        friend void ReadDBTableTxt1(DBTableTxt& tab, const string& fileName);
        friend void ReadDBTableBin1(DBTableTxt& tab, const string& fileName);
        friend DBTableTxt SelfRows1(DBTableTxt& tab, string& columnName, Condition cond, void* value);
		friend DBTableTxt SelfRows1(DBTableTxt& tab, string& columnName, Condition cond, string& value);
  };

  //-----------------------класс Relation----------------------
  class Relation  //  описывает связь двух таблиц
  {
    public:
        Relation();
        string relationName;
        string parentTable;
        string parentPrimaryKey;
        string childTable;
        string childSecondaryKey;
  };

  //-------------------------класс DBTableSet---------------------
  class DBTableSet
  {
    private:
        string dbName;
        map<string, DBTableTxt> db;
        DBTableTxt relationsTable;
        map<string, Relation> relations;
    public: 
        DBTableSet(const string& dbName = "");

        void ReadDB(const string& folderPath);
        void PrintDB(const size_t screenWidth);
        void WriteDB(const string& folderPath);

        string GetDBName(){return dbName;}
        DBTableTxt& operator[](string tableName) { return db[tableName]; }
        Relation GetRelation1(const string& relationName);

        Row ParentRow1(Relation& relation,Row& childRow);
        DBTableTxt ChildRows1(Relation& relation,Row& parentRow);
  };
}

#endif //_DBMSFuncsLib_
