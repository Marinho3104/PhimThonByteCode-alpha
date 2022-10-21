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

    int* _value = (int*) _toAdd->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt + *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::sub(objects::PhimObject* _toSub) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _toSub->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt - *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::mul(objects::PhimObject* _toMul) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _toMul->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt * *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::div(objects::PhimObject* _toDiv) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _toDiv->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt / *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::mod(objects::PhimObject* _toMod) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _toMod->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt % *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::bitwiseAnd(objects::PhimObject* _bitwiseAnd) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _bitwiseAnd->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt & *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::bitwiseOr(objects::PhimObject* _bitwiseOr) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _bitwiseOr->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt | *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::bitwiseXor(objects::PhimObject* _bitwiseXor) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _bitwiseXor->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt ^ *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::bitwiseLeftShift(objects::PhimObject* _bitwiseLeftShift) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _bitwiseLeftShift->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt << *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::bitwiseRightShift(objects::PhimObject* _bitwiseRightShift) {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _value = (int*) _bitwiseRightShift->getData();
    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = (*data_crrnt >> *_value);

    new(_rtr) objects::PhimInteger(
        _rslt
    );

    return _rtr;

}

objects::PhimObject* objects::PhimInteger::bitwiseNot() {

    objects::PhimInteger* _rtr = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));

    int* _rslt = (int*) malloc(sizeof(int));
    
    *_rslt = ~(*data_crrnt);

    new(_rtr) objects::PhimInteger(
        _rslt
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

