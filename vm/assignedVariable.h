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

    };

    struct AssignedVariable {

        VariableName* name;
        objects::PhimObject* value;

        ~AssignedVariable();

        AssignedVariable(VariableName*, objects::PhimObject*);
        
    };


}

#endif