#include "linkedlist.h"

LinkedList::LinkedList() {
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
}

int LinkedList::insert(Element* element) {
    int elementAlreadyExists = 0;

    if (find(element) != NULL) {
        elementAlreadyExists = 1;
    }
    else {
        if (this->head == NULL) {
            this->head = new Node;
            this->head->data = element;
            this->head->next = NULL;
            this->tail = NULL;
        }
		
        else {
			if (this->tail == NULL) {
				this->tail = new Node;
				this->tail->data = element;
				this->tail->next = NULL;
				this->head->next = this->tail;
			}
			else {
				this->tail->next = new Node;
				this->tail->next->data = element;
				this->tail->next->next = NULL;
				this->tail = this->tail->next;
			}
			
        }

        this->size++;
    }

    return elementAlreadyExists;
}

LinkedList::Node* LinkedList::find(Element* element) {
    Node* currentNode = this->head;

    while (currentNode != NULL) {
        if (currentNode->data->label.compare(element->label) == 0) {
            break;
        }
		else {
			currentNode = currentNode->next;
		}
    }
	
    return currentNode;
}

int LinkedList::listSize() {
    return this->size;
}
