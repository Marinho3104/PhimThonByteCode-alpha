#pragma once


#ifndef INSTRUCTION_H
#define INSTRUCTION_h

namespace byteCode { struct ByteCode; }

namespace vm {

    struct Method;

    struct Instruction {

        byteCode::ByteCode* byteCode;
        unsigned char arg;

        ~Instruction();

        Instruction(unsigned char, unsigned char);

        void execute(vm::Method*);

    };

}

#endif