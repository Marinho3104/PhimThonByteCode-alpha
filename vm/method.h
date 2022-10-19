#pragma once

#ifndef METHOD_H
#define METHOD_H

namespace utils { template <typename> struct LinkedList; }

namespace objects { struct PhimObject; }

namespace vm {

    struct AssignedVariable;
    struct VariableName;
    struct Instruction;
    struct Stack;

    struct Method {

        objects::PhimObject* classFather;
        utils::LinkedList<Instruction>* instructions;
        int instructionsLenght;
        utils::LinkedList<objects::PhimObject>* constants;
        utils::LinkedList<AssignedVariable>* assignedVariables;
        utils::LinkedList<VariableName>* names;
        objects::PhimObject* returnValue;

        Stack* stack;

        ~Method();

        Method(
            objects::PhimObject*,
           utils::LinkedList<Instruction>*,
            int,
            utils::LinkedList<objects::PhimObject>*,
            utils::LinkedList<AssignedVariable>*,
            utils::LinkedList<VariableName>*
        );

        void runMethod();

    };

}

#endif