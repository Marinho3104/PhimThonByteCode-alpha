#pragma once

#ifndef PHIMINTEGER_H
#define PHIMINTEGER_H

#include "./PhimObject.h"

namespace objects {

    struct PhimInteger : public PhimObject {

        int* data_crrnt;

        ~PhimInteger();

        PhimInteger(void*);

        void* destructor();

        void* getData();

        PhimObject* add(PhimObject*);

        PhimObject* getCopy();

        void print();

    };

}

#endif