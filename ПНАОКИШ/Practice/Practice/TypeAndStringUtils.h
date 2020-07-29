#pragma once

#include <string>
#include "dbmsLib_v1.h"

namespace DBMSFuncs {
	string typeToString(const DBMSFuncs::TableDataType& type);
    TableDataType stringToType(const string& typeName);
}

void splitString(string& target, string& origin, const string& delim);
