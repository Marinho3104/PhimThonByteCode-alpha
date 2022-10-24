#include "./commonFunctions.h"

bool utils::compareStrings(char* _f, char* _s) {

    if (*_f == 0 && *_s == 0) return true; 

    do if (*(_f++) != *(_s++)) return false; while(*_f != 0);

    return true;

}
