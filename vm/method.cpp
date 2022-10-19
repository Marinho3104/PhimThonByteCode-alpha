#include "./method.h"

#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"
#include "./assignedVariable.h"
#include "./instruction.h"
#include "./stack.h"

#include <iostream>

vm::Method::~Method() {

    if (classFather != NULL) classFather->~PhimObject();
    if (instructions != NULL) instructions->~LinkedList();
    if (constants != NULL) constants->~LinkedList();
    if (assignedVariables != NULL) assignedVariables->~LinkedList();
    if (names != NULL) names->~LinkedList();
    if (returnValue != NULL) returnValue->~PhimObject();
    if (stack != NULL) stack->~Stack();

    free(classFather);
    free(instructions);
    free(constants);
    free(assignedVariables);
    free(names);
    free(returnValue);
    free(stack);

}

vm::Method::Method(objects::PhimObject* _classFather, utils::LinkedList<Instruction>* _instructions, int _instructionsLenght, utils::LinkedList<objects::PhimObject>* _constants,
        utils::LinkedList<AssignedVariable>* _assignedVariables, utils::LinkedList<VariableName>* _names) : 
            classFather(_classFather), instructions(_instructions), instructionsLenght(_instructionsLenght), constants(_constants), 
                assignedVariables(_assignedVariables), names(_names), returnValue(NULL) {

                    stack = (vm::Stack*) malloc(sizeof(vm::Stack));
                    new(stack) vm::Stack();

}

void vm::Method::runMethod() {

    int _index = 0;

    while(_index != instructionsLenght) {

        (*instructions)[_index]->execute(this);

        ++_index;

    }

}






