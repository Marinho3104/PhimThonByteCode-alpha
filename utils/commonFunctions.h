#pragma once

#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

namespace utils {

    template <typename T>
    void copyTo(T* _cpy, T* _to, int _s) { for (int _ = 0; _ < _s; _++) _to[_] = _cpy[_]; }

    int getSize(char*);

    bool compareStrings(char*, char*);

    bool compareStrings(char*, char*, int);

    bool isNumber(char*);

}

#endif