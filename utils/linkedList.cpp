#include "./linkedList.h"

#include "./../vm/assignedVariable.h"
#include "./../objects/PhimObject.h"
#include "./../vm/instruction.h"

#include <iostream>

template <typename type>
utils::LinkedList<type>::~LinkedList() {


    
}

template <typename type>
utils::LinkedList<type>::LinkedList() {

    object = NULL;
    next = NULL;

}

template class utils::LinkedList<vm::AssignedVariable>;
template class utils::LinkedList<objects::PhimObject>;
template class utils::LinkedList<vm::VariableName>;
template class utils::LinkedList<vm::Instruction>;

