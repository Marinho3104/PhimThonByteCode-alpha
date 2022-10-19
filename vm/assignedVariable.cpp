#include "./assignedVariable.h"

#include <iostream>

vm::VariableName::~VariableName() {}

vm::VariableName::VariableName(unsigned char* _name, int _lenght) :
    name(_name), lenght(_lenght) {}



vm::AssignedVariable::~AssignedVariable() {}

vm::AssignedVariable::AssignedVariable(VariableName* _variableName, objects::PhimObject* _value) :
    name(_variableName), value(_value) {}




