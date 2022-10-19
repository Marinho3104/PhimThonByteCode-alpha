#pragma once

#ifndef PHIMINTEGER_H
#define PHIMINTEGER_H

#include "./PhimObject.h"

namespace objects {

    struct PhimInteger : public PhimObject {

        int data;

        ~PhimInteger();

        PhimInteger(int);

        int getType();

        void print();

    };
    
}


#endif