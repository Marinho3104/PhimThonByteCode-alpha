#include "./byteCode.h"

#include "./byteCodeIdentification.h"
#include "./../objects/PhimObject.h"
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

            LOAD_STACK(_arg, _method);

            break;

        case BYTECODE_PRINT:
            
            PRINT(_method);

            break;
        
        default:

            std::cout << "No byte code defined" << std::endl;

            break;
    }

}

void byteCode::ByteCode::LOAD_STACK(unsigned char _arg, vm::Method* _method) {

    _method->stack->add(
        _method->constants + _arg
    );

}

void byteCode::ByteCode::PRINT(vm::Method* _method) {

    objects::PhimObject* _stackTopValue = _method->stack->pop();

    _stackTopValue->print();

}