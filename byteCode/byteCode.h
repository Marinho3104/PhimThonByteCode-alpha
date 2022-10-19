#pragma once


#ifndef BYTECODE_H
#define BYTECODE_H

namespace vm { struct Method; }

namespace byteCode {

    struct ByteCode {

        unsigned char code;

        ~ByteCode();

        ByteCode(unsigned char);

        void execute(unsigned char, vm::Method*);

        void LOAD_STACK(unsigned char, vm::Method*);

        void PRINT(vm::Method*);

    };

}

#endif