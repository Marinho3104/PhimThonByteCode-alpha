#include "./linkedList.h"

#include "./../vm/assignedVariable.h"
#include "./../objects/PhimObject.h"
#include "./../vm/instruction.h"

#include <iostream>

template <typename type>
utils::LinkedListData<type>::~LinkedListData() {

    if (object != NULL) object->~type();

    free(object);

}

template <typename type>
utils::LinkedListData<type>::LinkedListData(type* _value) :
    object(_value), next(NULL), previous(NULL) {}


template <typename type>
utils::LinkedList<type>::~LinkedList() {

    utils::LinkedListData <type>* _ = frst;

    while(_ != NULL) {

        frst = frst->next;
        
        _->~LinkedListData();
        free(_);

        _ = frst;

    }

}

template <typename type>
utils::LinkedList<type>::LinkedList() : frst(NULL), last(NULL) {}

template <typename type>
void utils::LinkedList<type>::add(type* _newValue) {

    utils::LinkedListData <type>* _linkedListData = (utils::LinkedListData <type>*) malloc(sizeof(utils::LinkedListData <type>));
    new(_linkedListData) utils::LinkedListData <type>(_newValue);

    if (frst == NULL) { frst = _linkedListData; last = _linkedListData; }

    else { last->next = _linkedListData; last = _linkedListData; }

}

template <typename type>
void utils::LinkedList<type>::addFrst(type* _newValue) {

    utils::LinkedListData <type>* _linkedListData = (utils::LinkedListData <type>*) malloc(sizeof(utils::LinkedListData <type>));
    new(_linkedListData) utils::LinkedListData <type>(_newValue);

    if (frst == NULL) { frst = _linkedListData; last = _linkedListData; }

    else { _linkedListData->next = frst; frst = _linkedListData; }

}

template <typename type>
void utils::LinkedList<type>::remove(utils::LinkedListData <type>* _toRemove) {

    if (_toRemove == frst) {

        if (_toRemove == last) {

            frst = NULL;
            last = NULL;

        }

        else frst = frst->next;

    }

    else if (_toRemove == last) {

        last->previous->next = NULL;

        last = last->previous;

    }

    else {

        _toRemove->previous->next = _toRemove->next;
        _toRemove->next->previous = _toRemove->previous;

    }

    _toRemove->~LinkedListData();
    free(_toRemove);

}

template <typename type>
type* utils::LinkedList<type>::removeFrst() {

    if (frst == NULL) return NULL;

    utils::LinkedListData <type>* _ = frst;
    type* _rtr = _->object;

    if (frst == last) { frst = NULL; last = NULL; }

    else frst = frst->next;

    free(_);

    return _rtr;

}

template <typename type>
void utils::LinkedList<type>::clean() {

    while(removeFrst() != NULL);

}

template <typename type>
type* utils::LinkedList<type>::operator[](int _index) {

    utils::LinkedListData <type>* _rtr = frst;

    for (int _ = 0; _ < _index; _++) _rtr = _rtr->next;

    return _rtr->object;    

}


template class utils::LinkedListData<vm::AssignedVariable>;
template class utils::LinkedListData<objects::PhimObject>;
template class utils::LinkedListData<vm::VariableName>;
template class utils::LinkedListData<vm::Instruction>;

template class utils::LinkedList<vm::AssignedVariable>;
template class utils::LinkedList<objects::PhimObject>;
template class utils::LinkedList<vm::VariableName>;
template class utils::LinkedList<vm::Instruction>;

