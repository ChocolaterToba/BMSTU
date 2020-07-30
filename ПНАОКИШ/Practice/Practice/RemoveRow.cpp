#include "dbmsLib_v1.h"

void DBMSFuncs::DBTableTxt::RemoveRow(int rowIndex) {
	if (rowIndex < GetSize()) {
		data.erase(data.begin() + rowIndex);
	}
}