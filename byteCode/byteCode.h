// #pragma once


// #ifndef BYTECODE_H
// #define BYTECODE_H

// namespace vm { struct Method; }

// namespace byteCode {

//     struct ByteCode {

//         unsigned char code;

//         ~ByteCode();

//         ByteCode(unsigned char);

//         void execute(unsigned char, vm::Method*);

//         void STACK_LOAD(unsigned char, vm::Method*);

//         void STACK_NAME(unsigned char, vm::Method*);

//         void LOAD_NAME(unsigned char, vm::Method*);

//         void GO_TO(unsigned char, vm::Method*);

//         void ADD(unsigned char, vm::Method*);

//         void SUB(unsigned char, vm::Method*);

//         void MUL(unsigned char, vm::Method*);

//         void DIV(unsigned char, vm::Method*);

//         void MOD(unsigned char, vm::Method*);

//         void BITWISE_AND(unsigned char, vm::Method*);

//         void BITWISE_OR(unsigned char, vm::Method*);

//         void BITWISE_XOR(unsigned char, vm::Method*);

//         void BITWISE_LEFT_SHIFT(unsigned char, vm::Method*);

//         void BITWISE_RIGHT_SHIFT(unsigned char, vm::Method*);
        
//         void BITWISE_NOT(unsigned char, vm::Method*);

//         void PRINT(vm::Method*);

//     };

// }

// #endif