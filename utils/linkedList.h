#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

namespace utils {

    template <typename type>
    struct LinkedListData {

        type* object;
        LinkedListData <type>* previous, *next;

        ~LinkedListData();

        LinkedListData(type*);

    };

    template <typename type>
    struct LinkedList {

        LinkedListData <type>* frst, *last;
        int count;

        ~LinkedList();

        LinkedList();

        void add(type*);

        void addFrst(type*);

        void remove(LinkedListData <type>*);

        type* removeFrst();

        void clean();

        type* operator[](int);

    };
    
}


#endif