#include <string>
#include "dbmsLib_v1.h"

DBMSFuncs::TableDataType DBMSFuncs::GetType(const string& columnName, Header& hdr) {
	return hdr[columnName].colType;
}
