#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include "element.h"


class LinkedList {
    public:
		struct Node {
			Element* data;
			Node* next;
		};

		LinkedList();
        int insert(Element* element);
        Node* find(Element* element);
        int listSize();
		
	private:
        Node* head;
        Node* tail;
        int size;
};

#endif
