#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstdlib>
#include "element.h"
#include "linkedlist.h"

class HashTable {
    private:
        int buckets;
        int size;
        LinkedList* table;
    public:
        HashTable(int numberOfBuckets);
        int insert(Element* element);
        int hash(Element* element);
        Element* find(Element* element);
};

#endif
