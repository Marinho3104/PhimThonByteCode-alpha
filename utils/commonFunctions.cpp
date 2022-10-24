#include "./commonFunctions.h"

#include <iostream>

bool utils::compareStrings(char* _f, char* _s) {

    if (*_f == 0 && *_s == 0) return true; 

    do if (*(_f++) != *(_s++)) return false; while(*_f != 0);

    return true;

}

bool utils::compareStrings(char* _f, char* _s, int _l) {

    for (int _ = 0; _ < _l; _++) if (*(_f++) != *(_s++)) return false;

    return true;

}

bool utils::isNumber(char* _) {

    while(*_) { if ( *_ < 48 || *_ > 57) return false; _++; }

    return true;

}



