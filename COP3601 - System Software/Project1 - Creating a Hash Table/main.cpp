#include "linkedlist.h"
#include "hashtable.h"
#include "element.h"
#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
	std::ofstream outputFile;
    if (argc < 2) {
        std::cout << "No input given. Exiting.";
    }
    else {
        //inputFile.open(argv[1]);
		inputFile.open("test.txt");
        std::string line;
        if (inputFile.is_open()) {
            HashTable table(75);

            while (std::getline(inputFile, line)) {
                Element* element = new Element();
                element->label = "";
                element->value = "";
                bool valueAssociated = false;

                line.erase(std::remove(line.begin(), line.end(), " "), line.end());
                for (int i = 0; i < (int)line.length(); i++) {
                    if (!valueAssociated) {
                        if (element->label.empty()) {
                            element->label = line[i];
                        }
						else if (std::isspace(line[i])) {
							continue;
						}
                        else if (!std::isdigit(line[i])) {
                            element->label = element->label + line[i];
                        }
                        else {
                            valueAssociated = true;

                            if (element->value.empty()) {
                                element->value = line[i]; 
                            }
                            else {
                                element->value = element->value + line[i]; 
                            }
                        }
                    }
                    else {
                        if (element->value.empty()) {
                            element->value = line[i]; 
                        }
                        else {
                            element->value = element->value + line[i]; 
                        }
                    }
                }
                Element* tempElement = table.find(element);
                if (element->value.empty()) {
                    if (tempElement == NULL) {
                        std::cout << "ERROR: Element \"" << element->label << "\" not found in table! \n";
                    }
                    else {
                        std::cout << "Element \"" << tempElement->label << "\" found with value " << tempElement->value << " at bucket " << tempElement->hash << ".\n"; 
                    }
                }
                else {
					if (table.insert(element) == 0) {
						std::cout << "Element \"" << element->label << "\" with value " << element->value << " inserted into table at bucket " << element->hash << ".\n";
					}
					else {
						std::cout << "ERROR: Element \"" << element->label << "\" already exists with value " << tempElement->value << " at bucket " << tempElement->hash << "!\n";
					}
                    
                }
            }
			
            inputFile.close();
        }
    }
    return 0;
}
