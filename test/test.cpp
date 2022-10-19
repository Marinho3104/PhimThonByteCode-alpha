
#include "./../objects/PhimInteger.h"
#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"
#include "./../vm/instruction.h"
#include "./../vm/method.h"

#include <iostream>

int main() {

    objects::PhimInteger* _int = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));
    new(_int) objects::PhimInteger(123456);

    vm::Instruction* _instruction = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction) vm::Instruction(
        0, 0
    );

    vm::Instruction* _instruction1 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction1) vm::Instruction(
        1, 0
    );

    vm::Instruction* _instructions = (vm::Instruction*) malloc(sizeof(vm::Instruction) * 2);
    
    _instructions[0] = *_instruction;
    _instructions[1] = *_instruction1;

    vm::Method* method = (vm::Method*) malloc(sizeof(vm::Method));
    new (method) vm::Method(
        NULL,
        _instructions,
        2,
        _int,
        NULL,
        NULL
    );

    method->runMethod();

}