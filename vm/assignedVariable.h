#pragma once


#ifndef ASSIGNEDVARIABLE_H
#define ASSIGNEDVARIABLE_H

namespace objects { struct PhimObject; }

namespace vm {

    struct VariableName {

        unsigned char* name;
        int lenght;

        ~VariableName();

        VariableName(unsigned char*, int);

        VariableName(char*, int);

    };

    struct AssignedVariable {

        unsigned char name;
        objects::PhimObject* value;

        ~AssignedVariable();

        AssignedVariable(unsigned char, objects::PhimObject*);
        
    };


}

#endif