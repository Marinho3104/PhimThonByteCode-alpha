
#include "./../byteCode/byteCodeIdentification.h"
#include "./../vm/assignedVariable.h"
#include "./../objects/PhimInteger.h"
#include "./../objects/PhimBitsArray.h"
#include "./../objects/PhimObject.h"
#include "./../utils/linkedList.h"
#include "./../vm/instruction.h"
#include "./../vm/method.h"

#include <iostream>

utils::LinkedList<objects::PhimObject>* getConsts() {

    utils::LinkedList<objects::PhimObject>* _constants = (utils::LinkedList<objects::PhimObject>*) malloc(sizeof(utils::LinkedList<objects::PhimObject>));
    new(_constants) utils::LinkedList<objects::PhimObject>();

    int* _int1Value = (int*) malloc(sizeof(int)); *_int1Value = 100;
    int* _int2Value = (int*) malloc(sizeof(int)); *_int2Value = 10; 

    objects::PhimInteger* _int1 = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));
    new(_int1) objects::PhimInteger(_int1Value);
    objects::PhimInteger* _int2 = (objects::PhimInteger*) malloc(sizeof(objects::PhimInteger));
    new(_int2) objects::PhimInteger(_int2Value);

    _constants->add(_int1);
    _constants->add(_int2);

    return _constants;

}

utils::LinkedList<vm::Instruction>* getInstructions() {

    utils::LinkedList<vm::Instruction>* _instructions = (utils::LinkedList<vm::Instruction>*) malloc(sizeof(utils::LinkedList<vm::Instruction>));
    new(_instructions) utils::LinkedList<vm::Instruction>();

    vm::Instruction* _instruction = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction) vm::Instruction(
        BYTECODE_STACK_LOAD, 0
    );

    vm::Instruction* _instruction1 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction1) vm::Instruction(
        BYTECODE_STACK_NAME, 0
    );

    vm::Instruction* _instruction2 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction2) vm::Instruction(
        BYTECODE_STACK_LOAD, 1
    );

    vm::Instruction* _instruction3 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction3) vm::Instruction(
        BYTECODE_STACK_NAME, 1
    );

    vm::Instruction* _instruction4 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction4) vm::Instruction(
        BYTECODE_LOAD_NAME, 0
    );

    vm::Instruction* _instruction5 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction5) vm::Instruction(
        BYTECODE_LOAD_NAME, 1
    );

    vm::Instruction* _instruction6 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction6) vm::Instruction(
        BYTECODE_BITWISE_NOT, 0
    );

    vm::Instruction* _instruction7 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    new(_instruction7) vm::Instruction(
        BYTECODE_PRINT, 0
    );

    // vm::Instruction* _instruction8 = (vm::Instruction*) malloc(sizeof(vm::Instruction));
    // new(_instruction8) vm::Instruction(
    //     BYTECODE_GO_TO, 0
    // );

    _instructions->add(_instruction);
    _instructions->add(_instruction1);
    _instructions->add(_instruction2);
    _instructions->add(_instruction3);
    _instructions->add(_instruction4);
    _instructions->add(_instruction5);
    _instructions->add(_instruction6);
    _instructions->add(_instruction7);
    //_instructions->add(_instruction8);

}

utils::LinkedList<vm::VariableName>* getVariablesNames() {

    utils::LinkedList<vm::VariableName>* _names = (utils::LinkedList<vm::VariableName>*) malloc(sizeof(utils::LinkedList<vm::VariableName>));
    new(_names) utils::LinkedList<vm::VariableName>();

    vm::VariableName* _name1 = (vm::VariableName*) malloc(sizeof(vm::VariableName));
    new(_name1) vm::VariableName(
        (char*) "ola1", 4
    );

    vm::VariableName* _name2 = (vm::VariableName*) malloc(sizeof(vm::VariableName));
    new(_name2) vm::VariableName(
        (char*) "ola2", 4
    );

    _names->add(_name1);
    _names->add(_name2);

    return _names;

}

utils::LinkedList<vm::AssignedVariable>* getAssignedVariables() {

    utils::LinkedList<vm::AssignedVariable>* _assignedVariables = (utils::LinkedList<vm::AssignedVariable>*) 
        malloc(sizeof(utils::LinkedList<vm::AssignedVariable>));
    new(_assignedVariables) utils::LinkedList<vm::AssignedVariable>();

    return _assignedVariables;

}

int main() {

    objects::PhimBitsArray* _bytes = (objects::PhimBitsArray*) malloc(sizeof(objects::PhimBitsArray));
    new (_bytes) objects::PhimBitsArray();

    _bytes->addNewByte(54);
    _bytes->addNewByte(123);
    _bytes->addNewByte(50);
    _bytes->addNewByte(255);

    // std::cout << (int) (*_bytes)[3] << std::endl;

    // return 0;

    objects::PhimBitsArray* _bytes1 = (objects::PhimBitsArray*) malloc(sizeof(objects::PhimBitsArray));
    new (_bytes1) objects::PhimBitsArray();

    _bytes1->addNewByte(72);
    _bytes1->addNewByte(12);

    std::cout << _bytes->getFullSize() << std::endl;
    std::cout << _bytes1->getFullSize() << std::endl;

    // std::cout << _bytes->getBytesRepresentation() << std::endl;
    // std::cout << _bytes1->getBytesRepresentation() << std::endl;

    // *_bytes /= *_bytes1;

    // // std::cout << _bytes->getBytesRepresentation() << std::endl;

    // _bytes->~PhimBitsArray();
    // free(_bytes);

    // _bytes1->~PhimBitsArray();
    // free(_bytes1);

    // // _bytes1->addNewByte(50);
    // // _bytes1->addNewByte(111);

    // std::cout << _bytes1->getBytesRepresentation() << std::endl;
    // std::cout << _bytes->getBytesRepresentation() << std::endl;
    // std::cout << (*_bytes + *_bytes1).getBytesRepresentation() << std::endl;
    // *_bytes += *_bytes1;

    // std::cout << _bytes->getBytesRepresentation() << std::endl;

    // _bytes->~PhimBitsArray(); free(_bytes);
    // _bytes1->~PhimBitsArray(); free(_bytes1);

    // std::cout << _bytes->getBytesRepresentation() << std::endl;
    // std::cout << _bytes1->getBytesRepresentation() << std::endl;
    // std::cout << ()->getBytesRepresentation() << std::endl;

    // _bytes->setBit(0, 1);
    // _bytes->setBit(1, 1);

    // std::cout << _bytes->getBytesRepresentation() << std::endl;

    // for (int _ = 31; _ >= 0; _--) std::cout << (*_bytes)[_];

    // std::cout << std::endl;

    // _byte->setBit(2, 0);

    // _byte->~ByteData();
    // free(_byte);


    // for (int _ = 0; _ < 8; _++)
    //     std::cout << (*_byte)[_] << std::endl;

    // vm::Method* method = (vm::Method*) malloc(sizeof(vm::Method));
    // new (method) vm::Method(
    //     NULL,
    //     getInstructions(),
    //     getConsts(),
    //     getAssignedVariables(),
    //     getVariablesNames()
    // );

    // method->runMethod();

    // method->~Method();
    // free(method);

}