#include "./PhimInteger.h"

#include <iostream>

objects::PhimInteger::~PhimInteger() {}

objects::PhimInteger::PhimInteger(int _data) :
    data(_data) {}

int objects::PhimInteger::getType() { return 0; }

void objects::PhimInteger::print() { std::cout << data << std::endl; }




