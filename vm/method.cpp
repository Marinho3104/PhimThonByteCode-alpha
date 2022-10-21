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

vm::Method::Method(objects::PhimObject* _classFather, utils::LinkedList<Instruction>* _instructions, utils::LinkedList<objects::PhimObject>* _constants,
        utils::LinkedList<AssignedVariable>* _assignedVariables, utils::LinkedList<VariableName>* _names) : 
            classFather(_classFather), instructions(_instructions), constants(_constants), 
                assignedVariables(_assignedVariables), names(_names), returnValue(NULL), currentInstruction(0) {

                    stack = (vm::Stack*) malloc(sizeof(vm::Stack));
                    new(stack) vm::Stack();

}

void vm::Method::runMethod() {

    while(currentInstruction != instructions->count) {

        (*instructions)[currentInstruction]->execute(this);

        ++currentInstruction;

    }

}






