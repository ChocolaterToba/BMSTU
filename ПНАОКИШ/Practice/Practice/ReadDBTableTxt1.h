#pragma once

#include <string>
#include "dbmsLib_v1.h"

namespace DBMSFuncs {
	TableDataType stringToType(const string& typeName);
}

void splitString(string& target, string& origin, const string& delim);