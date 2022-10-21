#include "./byteCode.h"

#include "./byteCodeIdentification.h"
#include "./../vm/assignedVariable.h"
#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"
#include "./../vm/method.h"
#include "./../vm/stack.h"

#include <iostream>

byteCode::ByteCode::~ByteCode() {}

byteCode::ByteCode::ByteCode(unsigned char _code) :
    code(_code) {}

void byteCode::ByteCode::execute(unsigned char _arg, vm::Method* _method) {

    switch (code)
    {

        case BYTECODE_STACK_LOAD:

            STACK_LOAD(_arg, _method);

            break;

        case BYTECODE_STACK_NAME:

            STACK_NAME(_arg, _method);

            break;

        case BYTECODE_LOAD_NAME:

            LOAD_NAME(_arg, _method);

            break;

        case BYTECODE_GO_TO:

            GO_TO(_arg, _method);

            break;

        case BYTECODE_ADD:

            ADD(_arg, _method);

            break;

        case BYTECODE_SUB:

            SUB(_arg, _method);

            break;
        
        case BYTECODE_MUL:

            MUL(_arg, _method);

            break;

        case BYTECODE_DIV:

            DIV(_arg, _method);

            break;

        case BYTECODE_MOD:

            MOD(_arg, _method);

            break;

        case BYTECODE_BITWISE_AND:

            BITWISE_AND(_arg, _method);

            break;

        case BYTECODE_BITWISE_OR:

            BITWISE_OR(_arg, _method);

            break;

        case BYTECODE_BITWISE_XOR:

            BITWISE_XOR(_arg, _method);

            break;

        case BYTECODE_BITWISE_LEFT_SHIFT:

            BITWISE_LEFT_SHIFT(_arg, _method);

            break;

        case BYTECODE_BITWISE_RIGHT_SHIFT:

            BITWISE_RIGHT_SHIFT(_arg, _method);

            break;

        case BYTECODE_BITWISE_NOT:

            BITWISE_NOT(_arg, _method);

            break;

        case BYTECODE_PRINT:
            
            PRINT(_method);

            break;
        
        default:

            std::cout << "No byte code defined" << std::endl;

            break;
    }

}

void byteCode::ByteCode::STACK_LOAD(unsigned char _arg, vm::Method* _method) {

    _method->stack->add(
        (*_method->constants)[_arg]
    );

}

void byteCode::ByteCode::STACK_NAME(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _stackTopValue = _method->stack->pop();
    vm::VariableName* _variableName = (*_method->names)[_arg];
    
    vm::AssignedVariable* _assignedVariable = (vm::AssignedVariable*) malloc(sizeof(vm::AssignedVariable));
    new(_assignedVariable) vm::AssignedVariable(
        _arg, _stackTopValue
    );

    _method->assignedVariables->add(_assignedVariable);

}

void byteCode::ByteCode::LOAD_NAME(unsigned char _arg, vm::Method* _method) {

    utils::LinkedListData <vm::AssignedVariable>* _assignedVariable = _method->assignedVariables->frst;

    while(_assignedVariable != NULL) {

        if (
            _assignedVariable->object->name == _arg
        ) break;

        _assignedVariable = _assignedVariable->next;

    }

    if (_assignedVariable == NULL) return;

    _method->stack->add(
        _assignedVariable->object->value->getCopy()
    );

}

void byteCode::ByteCode::GO_TO(unsigned char _arg, vm::Method* _method) {

    _method->currentInstruction = _arg;

}

void byteCode::ByteCode::ADD(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->add(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::SUB(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->sub(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::MUL(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->mul(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::DIV(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->div(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::MOD(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->mod(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::BITWISE_AND(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->bitwiseAnd(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::BITWISE_OR(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->bitwiseOr(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::BITWISE_XOR(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->bitwiseXor(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::BITWISE_LEFT_SHIFT(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->bitwiseLeftShift(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::BITWISE_RIGHT_SHIFT(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();
    objects::PhimObject* _scnd = _method->stack->pop();

    _method->stack->add(
        _frst->bitwiseRightShift(_scnd)
    );

    _frst->~PhimObject();
    _scnd->~PhimObject();

    free(_frst);
    free(_scnd);  

}

void byteCode::ByteCode::BITWISE_NOT(unsigned char _arg, vm::Method* _method) {

    objects::PhimObject* _frst = _method->stack->pop();

    _method->stack->add(
        _frst->bitwiseNot()
    );

    _frst->~PhimObject();

    free(_frst);
    
}

void byteCode::ByteCode::PRINT(vm::Method* _method) {

    objects::PhimObject* _stackTopValue = _method->stack->pop();

    _stackTopValue->print();

    _stackTopValue->~PhimObject();
    free(_stackTopValue);

}