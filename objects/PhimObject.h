#pragma once


#ifndef PHIMOBJECT_H
#define PHIMOBJECT_H

namespace objects {

    struct PhimObject {

        virtual ~PhimObject();

        virtual void* getData() = 0;

        virtual PhimObject* add(PhimObject*) = 0;

        virtual PhimObject* sub(PhimObject*) = 0;

        virtual PhimObject* mul(PhimObject*) = 0;

        virtual PhimObject* div(PhimObject*) = 0;

        virtual PhimObject* mod(PhimObject*) = 0;

        virtual PhimObject* bitwiseAnd(PhimObject*) = 0;

        virtual PhimObject* bitwiseOr(PhimObject*) = 0;

        virtual PhimObject* bitwiseXor(PhimObject*) = 0;

        virtual PhimObject* bitwiseLeftShift(PhimObject*) = 0;

        virtual PhimObject* bitwiseRightShift(PhimObject*) = 0;

        virtual PhimObject* bitwiseNot() = 0;

        virtual PhimObject* getCopy() = 0;

        virtual void print() = 0;

    };

}

#endif