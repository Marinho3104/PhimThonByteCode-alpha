#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

namespace utils {

    template <typename type>
    struct LinkedList {

        type* object;
        LinkedList <type>* next;

        ~LinkedList();

        LinkedList();

    };
    
}


#endif