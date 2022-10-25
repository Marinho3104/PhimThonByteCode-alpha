#include "./commonFunctions.h"

#include <iostream>

int utils::getSize(char* _) {
    int _rtr = 0;
    while(
        _[_rtr++]
    );
    return _rtr;
}

bool utils::compareStrings(char* _f, char* _s) {
    
    int _fs = utils::getSize(_f);
    int _ss = utils::getSize(_s);

    if (_fs != _ss) return false;

    for (int _ = 0; _ < _fs; _++) if (_f[_] != _s[_]) return false;

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



