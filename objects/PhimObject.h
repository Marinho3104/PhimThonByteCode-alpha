#pragma once


#ifndef PHIMOBJECT_H
#define PHIMOBJECT_H

namespace objects {

    struct PhimObject {

        virtual int getType() = 0;

        virtual void print() = 0;

    };

}

#endif