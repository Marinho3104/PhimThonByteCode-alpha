#include "./instruction.h"

#include "./../byteCode/byteCode.h"
#include "./method.h"

#include <iostream>

vm::Instruction::~Instruction() {

}

vm::Instruction::Instruction(unsigned char _byteCodeValue, unsigned char _arg) :
    arg(_arg) {

        byteCode = (byteCode::ByteCode*) malloc(sizeof(byteCode::ByteCode)); 
        new (byteCode) byteCode::ByteCode(_byteCodeValue);

    }

void vm::Instruction::execute(vm::Method* _method) {

    byteCode->execute(arg, _method);

}
