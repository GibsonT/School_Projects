#include "hashtable.h"

HashTable::HashTable(int numberOfBuckets) {
    //this->table = (LinkedList*)(malloc(numberOfBuckets * sizeof(LinkedList)));
	this->table = new LinkedList[numberOfBuckets];
	for (int i = 0; i < numberOfBuckets; i++) {
		this->table[i] = LinkedList();
	}
    this->buckets = numberOfBuckets;
    this->size = 0;
}

//Hashes elements based on sum of ASCII values of its label
int HashTable::hash(Element* element) {
    int sum = 0;
    for (int i = 0; i < (int)element->label.size(); i++) {
        sum += (int)element->label[i];
    }
    element->hash = sum % buckets;
    return element->hash;
}

int HashTable::insert(Element* element) {
    this->size++;
	return this->table[hash(element)].insert(element);
}

Element* HashTable::find(Element* element) {
	LinkedList::Node* node = this->table[hash(element)].find(element);
	Element* foundElement;
	
	if (node == NULL) {
		foundElement = NULL;
	}
	else {
		foundElement = node->data;
	}
	
	return foundElement;
}
