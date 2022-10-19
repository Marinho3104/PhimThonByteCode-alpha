#include "./stack.h"

#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"

#include <iostream>

vm::Stack::~Stack() {

    free(stack);

}

vm::Stack::Stack() {

    stack = (utils::LinkedList <objects::PhimObject>*) malloc(sizeof(utils::LinkedList <objects::PhimObject>));
    new(stack) utils::LinkedList <objects::PhimObject>();

}

void vm::Stack::add(objects::PhimObject* _toAdd) {
    
    stack->addFrst(_toAdd);

}

objects::PhimObject* vm::Stack::pop(int _n) {

    objects::PhimObject* _rtr = stack->removeFrst();

    return _rtr;

}