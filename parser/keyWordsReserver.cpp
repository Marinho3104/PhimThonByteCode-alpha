#include "./keyWordsReserved.h"

#include "./../utils/commonFunctions.h"

#include <iostream>

int keyWordsReserved::checkIfWordIsVariableType(char* _toCheck) {

    if (
        utils::compareStrings(_toCheck, "int")
    ) return KEYWORD_INT;

}
