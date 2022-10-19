#include "./PhimInteger.h"

#include <iostream>

objects::PhimInteger::~PhimInteger() { free(data_crrnt); }

objects::PhimInteger::PhimInteger(void* _data) {

    data_crrnt = (int*) _data;

}

void* objects::PhimInteger::destructor() { this->~PhimInteger(); }

void* objects::PhimInteger::getData() { return data_crrnt; }

objects::PhimObject* objects::PhimInteger::add(objects::PhimObject* _toAdd) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _toAddValue = (int*) _toAdd->getData();
    int* _sumRslt = (int*) malloc(sizeof(int));
    
    *_sumRslt = (*_toAddValue + *data_crrnt);

    new(_rtr) objects::PhimInteger(
        _sumRslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::getCopy() {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _cpy = (int*) malloc(sizeof(int));

    *_cpy = *data_crrnt;

    new (_rtr) objects::PhimInteger(
        _cpy
    );

    return _rtr;

}

void objects::PhimInteger::print() { std::cout << *data_crrnt << std::endl; }

