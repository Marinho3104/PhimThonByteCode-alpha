#include "./method.h"

#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"
#include "./assignedVariable.h"
#include "./instruction.h"
#include "./stack.h"

#include <iostream>

vm::Method::~Method() {}

vm::Method::Method(objects::PhimObject* _classFather, Instruction* _instructions, int _instructionsLenght, objects::PhimObject* _constants,
        utils::LinkedList<AssignedVariable>* _assignedVariables, utils::LinkedList<VariableName>* _names) : 
            classFather(_classFather), instructions(_instructions), instructionsLenght(_instructionsLenght), constants(_constants), 
                assignedVariables(_assignedVariables), names(_names) {

                    stack = (vm::Stack*) malloc(sizeof(vm::Stack));
                    new(stack) vm::Stack();

}

void vm::Method::runMethod() {

    int _index = 0;

    while(_index != instructionsLenght) {

        instructions[_index].execute(this);

        ++_index;

    }

}






