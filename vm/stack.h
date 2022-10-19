#pragma once

#ifndef STACK_H
#define STACK_H

namespace objects { struct PhimObject; }

namespace utils { template <typename> struct LinkedList; }

namespace vm {

    struct Stack {

        utils::LinkedList<objects::PhimObject>* stackData; // Inverted ( first in first out)

        ~Stack();

        Stack();

        void add(objects::PhimObject*);

        objects::PhimObject* pop(int _n = 1);

    };


}

#endif