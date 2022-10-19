#include "./assignedVariable.h"

#include <iostream>

vm::VariableName::~VariableName() {

    free(name);

}

vm::VariableName::VariableName(unsigned char* _name, int _lenght) :
    name(_name), lenght(_lenght) {}

vm::VariableName::VariableName(char* _name, int _lenght) :
    lenght(_lenght) {

        name = (unsigned char*) malloc(sizeof(unsigned char) * lenght);

        for (int _ = 0; _ < lenght; _++) *name = (int) (unsigned char) _name[_];

}

vm::AssignedVariable::~AssignedVariable() {}

vm::AssignedVariable::AssignedVariable(unsigned char _name, objects::PhimObject* _value) :
    name(_name), value(_value) {}




