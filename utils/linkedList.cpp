#include "./linkedList.h"

#include "./../parser/convertToAst.h"
#include "./../parser/token.h"

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
utils::LinkedList<type>::LinkedList() : frst(NULL), last(NULL), count(0) {}

template <typename type>
int utils::LinkedList<type>::add(type* _newValue) {

    utils::LinkedListData <type>* _linkedListData = (utils::LinkedListData <type>*) malloc(sizeof(utils::LinkedListData <type>));
    new(_linkedListData) utils::LinkedListData <type>(_newValue);

    if (frst == NULL) { frst = _linkedListData; last = _linkedListData; }

    else { last->next = _linkedListData; last = _linkedListData; }

    return count++;

}

template <typename type>
void utils::LinkedList<type>::addFrst(type* _newValue) {

    utils::LinkedListData <type>* _linkedListData = (utils::LinkedListData <type>*) malloc(sizeof(utils::LinkedListData <type>));
    new(_linkedListData) utils::LinkedListData <type>(_newValue);

    if (frst == NULL) { frst = _linkedListData; last = _linkedListData; }

    else { _linkedListData->next = frst; frst = _linkedListData; }

    ++count;

}

template <typename type>
void utils::LinkedList<type>::join(utils::LinkedList <type>* _toJoin) {

    int _  = 0;

    if (!frst) {

        frst = _toJoin->frst;
        last = frst;
        ++_;

    }

    for (; _ < _toJoin->count; _++) add( (*_toJoin)[_] );

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

    --count; 

}

template <typename type>
type* utils::LinkedList<type>::removeFrst() {

    if (frst == NULL) return NULL;

    utils::LinkedListData <type>* _ = frst;
    type* _rtr = _->object;

    if (frst == last) { frst = NULL; last = NULL; }

    else frst = frst->next;

    free(_);
    --count;

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

template <typename type>
int utils::LinkedList<type>::getObjectPosition(type* _c, bool (*func) (type*, type*)) {

    for (int _ = 0; _ < count; _++)

        if (func(operator[](_), _c)) return _;

    return -1;

}


template class utils::LinkedListData<parser::convertToAst::Node>;
template class utils::LinkedListData<token::Token>;
template class utils::LinkedListData<int>;
template class utils::LinkedListData<char>;

template class utils::LinkedList<parser::convertToAst::Node>;
template class utils::LinkedList<token::Token>;
template class utils::LinkedList<int>;
template class utils::LinkedList<char>;

// template class utils::LinkedListData<vm::AssignedVariable>;
// template class utils::LinkedListData<objects::PhimObject>;
// template class utils::LinkedListData<vm::VariableName>;
// template class utils::LinkedListData<vm::Instruction>;

// template class utils::LinkedList<vm::AssignedVariable>;
// template class utils::LinkedList<objects::PhimObject>;
// template class utils::LinkedList<vm::VariableName>;
// template class utils::LinkedList<vm::Instruction>;

