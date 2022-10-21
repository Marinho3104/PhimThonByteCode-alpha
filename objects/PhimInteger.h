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

        PhimObject* sub(PhimObject*);

        PhimObject* mul(PhimObject*);

        PhimObject* div(PhimObject*);

        PhimObject* mod(PhimObject*);

        PhimObject* bitwiseAnd(PhimObject*);

        PhimObject* bitwiseOr(PhimObject*);

        PhimObject* bitwiseXor(PhimObject*);

        PhimObject* bitwiseLeftShift(PhimObject*);

        PhimObject* bitwiseRightShift(PhimObject*);

        PhimObject* bitwiseNot();

        PhimObject* getCopy();

        void print();

    };

}

#endif