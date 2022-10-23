#pragma once

#ifndef BITSARRAY_H
#define BITSARRAY_H

#include "./PhimObject.h"

namespace objects {
    
    struct ByteOperation {

        static void getByteRepresentation(unsigned char, char*);
        
        static bool getBit(unsigned char, int);

        static bool setBit(unsigned char*, int, bool);

        static unsigned char addBytes(unsigned char, unsigned char, bool&);
        
        static unsigned char subBytes(unsigned char, unsigned char, bool&);

    };
    
    struct PhimBitsArray {

        unsigned char* bytes;
        int bytesLenght;

        ~PhimBitsArray();

        PhimBitsArray();

        void clean();

        void copyBytes(unsigned char*);

        // size_t getFullSize();

        unsigned char operator[](int);

        unsigned char getByteInverted(int);

        bool getBitOfByte(int, int);

        bool getBit(int);

        bool getBitOfByteInverted(int, int);

        bool getBitInverted(int);

        char* getBytesRepresentation();

        char* toString();

        void addNewByte(unsigned char);

        bool setByte(int, unsigned char);

        bool setBitOfByte(int, int, bool);

        bool setBit(int, bool);

        bool setByteInverted(int, unsigned char);

        bool setBitOfByteInverted(int, int, bool);

        bool setBitInverted(int, bool);

        bool isOdd();

        bool isZero();

        bool operator<(PhimBitsArray&);
        bool operator>(PhimBitsArray&);
        bool operator<=(PhimBitsArray&);
        bool operator>=(PhimBitsArray&);

        bool operator==(PhimBitsArray&);
        bool operator!=(PhimBitsArray&);

        PhimBitsArray operator&(PhimBitsArray&);
        PhimBitsArray operator|(PhimBitsArray&);
        PhimBitsArray operator^(PhimBitsArray&);
        objects::PhimBitsArray operator~();
        void operator&=(PhimBitsArray&);
        void operator|=(PhimBitsArray&);
        void operator^=(PhimBitsArray&);

        PhimBitsArray operator<<(int);
        PhimBitsArray operator>>(int);
        void operator<<=(int);
        void operator>>=(int);

        PhimBitsArray operator+(PhimBitsArray&);
        PhimBitsArray operator-(PhimBitsArray&);
        void operator+=(PhimBitsArray&);
        void operator-=(PhimBitsArray&);

        PhimBitsArray operator*(PhimBitsArray&);
        PhimBitsArray operator/(PhimBitsArray&);
        PhimBitsArray operator%(PhimBitsArray&);
        void operator*=(PhimBitsArray&);
        void operator/=(PhimBitsArray&);

    };

}

#endif