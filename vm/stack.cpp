#include "./stack.h"

#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"

#include <iostream>

vm::Stack::~Stack() {}

vm::Stack::Stack() : stackData(NULL) {}

void vm::Stack::add(objects::PhimObject* _toAdd) {

    std::cout << "Added new value to stack" << std::endl;
    
    utils::LinkedList<objects::PhimObject>* _stackData = (utils::LinkedList<objects::PhimObject>*) malloc(sizeof(utils::LinkedList<objects::PhimObject>));
    new (_stackData) utils::LinkedList<objects::PhimObject>();

    if (stackData == NULL) {

        stackData = _stackData;

        stackData->object = _toAdd;

    }

    else {

        _stackData->next = stackData;

        stackData = _stackData;

    }

}

objects::PhimObject* vm::Stack::pop(int _n) {

    objects::PhimObject* _rtr = stackData->object;

    stackData = stackData->next;

    return _rtr;

}