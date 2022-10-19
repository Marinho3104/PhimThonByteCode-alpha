#pragma once


#ifndef PHIMOBJECT_H
#define PHIMOBJECT_H

namespace objects {

    struct PhimObject {

        virtual ~PhimObject();

        virtual void* getData() = 0;

        virtual PhimObject* add(PhimObject*) = 0;

        virtual PhimObject* getCopy() = 0;

        virtual void print() = 0;

    };

}

#endif