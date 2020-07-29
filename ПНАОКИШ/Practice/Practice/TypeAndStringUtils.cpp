#include <string>
#include "dbmsLib_v1.h"
#include "TypeAndStringUtils.h"

string DBMSFuncs::typeToString(const DBMSFuncs::TableDataType& type) {
	switch(type) {
	    case Int32:
		    return "Int32";
		case Double:
			return "Double";
		case String:
			return "String";
		case Date:
			return "Date";
		case NoType:
			return "NoType";
		default:
			return "UnknownType";
	}
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
	//  Split string so that everything before delim goes to target, after - to origin.
    size_t delimPos = origin.find(delim);
	target = origin.substr(0, delimPos);

	if (delimPos != string::npos) {
		origin = origin.substr(delimPos + delim.length());
	} else {
		origin.clear();
	}
}
