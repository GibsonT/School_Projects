#include "linkedlist.h"
#include "hashtable.h"
#include "element.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
	std::ifstream opsList;
	std::ofstream outputFile;
    if (argc < 2) {
        std::cout << "No input given. Exiting.";
    }
    else {
        std::string outputFileName = (std::string)argv[1] + ".lst";
		inputFile.open(argv[1]);
		opsList.open("ops.dat");
		outputFile.open(outputFileName);
        std::string line;
		
        if (inputFile.is_open() && outputFile.is_open() && opsList.is_open()) {
            int opsTableSize = 75;
            int labelTableSize = 25;
            
			HashTable opsTable(opsTableSize);
			HashTable labelTable(labelTableSize);
			bool startFound = false;
            bool endFound = false;
			int startAddress = 0;
			int PC = 0;
			
			// Fill the operations table with mneumonics
			while (std::getline(opsList, line)) {
				std::string operation;
				std::string info;	// For opcode and SIC \ SIC/XE sizes
				Element* operationElement = new Element();
				int infoStartIndex;
				
				for (int i = 0; i < line.length(); i++) {
					if (line[i] == ' ') {
						infoStartIndex = i;
						break;
					}
					
					operation += line[i];
				}
				
				for (int i = infoStartIndex; i < line.length(); i++) {
					if (line[i] != ' ') {
						info += line[i];
					}
				}
				
				operationElement->label = operation;
				operationElement->value = info;
				
				opsTable.insert(operationElement);
			}
			
			opsList.close();

            while (std::getline(inputFile, line)) {
				bool nFlag = true;
				bool iFlag = true;
				bool xFlag = false;
				bool bFlag = false;
				bool pFlag = true;
				bool eFlag = false;
				std::string label;
				int labelAddress;
				int operationSize = 0;
				std::string mneumonic;
                char mneumonicPrefix = ' ';
				std::string operand;
				std::string comment;
                char operandPrefix = ' ';
				
				// Check if line is blank or a comment, continue to next line if so
				if (line.size() == 0 || line[0] == '.') {
					outputFile << line;
					outputFile << '\n';
					continue;
				}
				
				// Check for label
				if (line[0] != ' ') {
					for (int i = 0; i < 9 && line[i] != ' ' && i < line.length(); i++) {
						label += line[i];
					}
				}
				
				// Is this a SIC/XE operation?
				if (line[9] == '+') {
					eFlag = true;
                    mneumonicPrefix = '+';
				}
                // ...or a SIC compatible one?
                else if (line[9] == '*') {
                    mneumonicPrefix = '*';
                }
                else if (line[9] != ' ') {
                    outputFile << " ***ERROR: UNSUPPORTED MNEUMONIC PREFIX: " << line[9] << "***\n";
                }
				
				// Load and check mneumonic
				if (line[10] == ' ') {
					outputFile << " ***ERROR: NO MNEUMONIC DECLARED***\n";
					continue;
				}
				else {
					for (int i = 10; i < 17 && i < line.length(); i++) {
						if (line[i] == ' ') {
							break;
						}
						
						mneumonic += line[i];
					}
				}
				
				Element* mneumonicElement = new Element();
                if (mneumonicPrefix != ' ') {
                    mneumonicElement->label = mneumonicPrefix + mneumonic;
                }
                else {
                    mneumonicElement->label = mneumonic;
                }
				mneumonicElement = opsTable.find(mneumonicElement);
				if (mneumonicElement == NULL) {
					outputFile << " ***ERROR: INVALID MNEUMONIC OR NOT SUPPORTED: " << mneumonic << " ***\n";
					continue;
				}
				
				// Is there an operand prefix?
				operandPrefix = line[18];
				switch (operandPrefix) {
					case '#':
						iFlag = true;
						break;
					case '@':
						nFlag = true;
						iFlag = false;
						break;
					case ' ':
						break;
					default:
						outputFile << " ***ERROR: OPERAND PREFIX NOT RECOGNIZED***\n";
						continue;
				}
				
				for (int i = 19; i < 28 && i < line.length(); i++) {
					if (line[i] == ' ') {
						break;
					}
					
					operand = operand + line[i];
				}
				
				if (line.length() >= 32) {
					for (int i = 31; i < line.length(); i++) {
						comment = comment + line[i];
					}
				}
				
				// This is an assembly operation
				if (mneumonicElement->value == "0000") {
                    std::string assemblerDirective = mneumonicElement->label;
					if (assemblerDirective == "START") {
						if (!startFound) {
							startAddress = std::stoi(operand, NULL, 16);
							PC = std::stoi(operand, NULL, 16);
							startFound = true;
						}
						else {
							outputFile << "***ERROR: START ALREADY DECLARED AT ADDRESS " << startAddress << "***\n";
							continue;
						}
					}
					else if (assemblerDirective == "END") {
						//FILL ME
					}
					else if (assemblerDirective == "BASE") {
						//FILL ME
					}
					else if (assemblerDirective == "WORD") {
						operationSize = 0x3;
					}
                    else if (assemblerDirective == "BYTE") {
                        operationSize = 0x1;
                    }
                    else if (assemblerDirective == "RESW") {
                        operationSize = 0x3 * std::stoi(operand, NULL, 10);
                    }
                    else if (assemblerDirective == "RESB") {
                        operationSize = 0x1 * std::stoi(operand, NULL, 10);
                    }
				}
                else {
                    std::string opSizeString;
                    opSizeString += mneumonicElement->value[2];
                    operationSize = std::stoi(opSizeString, NULL, 16);
                }
                
                if (label.length() > 0) {
                    Element* labelElement = new Element();
                    labelElement->label = label;
                    labelElement->value = std::to_string((long long)PC);
                    if (labelTable.insert(labelElement) == 1) {
                        outputFile << "***ERROR: LABEL ALREADY EXISTS - " << label << "***\n";
                        continue;
                    }
                }
                
                outputFile << std::hex << PC;
                for (int i = 0; i < 8 - std::to_string((long long)PC).length(); i++) {
                    outputFile << " ";
                }
                outputFile << label;
                for (int i = 0; i < 8 - label.length(); i++) {
                    outputFile << " ";
                }
                outputFile << mneumonicPrefix << mneumonic;
                for (int i = 0; i < 8 - mneumonic.length(); i++) {
                    outputFile << " ";
                }
                outputFile << operandPrefix << operand;
                for (int i = 0; i < 8 - operand.length(); i++) {
                    outputFile << " ";
                }
                outputFile << comment << "\n";
                
                PC += operationSize;
			}
            
            outputFile << "\n\n";
            outputFile << "Symbol Table\n";
            outputFile << "==============================\n";
            outputFile << "Hash\tMneumonic\tAddress\n";
            outputFile << "==============================\n";
            for (int i = 0; i < labelTableSize; i++) {
                LinkedList labelList = labelTable.bucketAt(i);
                
                if (labelList.listSize() > 0) {
                    LinkedList::Node* listNode = labelList.getHead();
                    
                    for (int j = 0; j < labelList.listSize(); j++) {
                        int value = std::stoi(listNode->data->value, NULL, 10);
                        
                        outputFile << std::dec << listNode->data->hash;
                        for (int k = 0; k < 8 - std::to_string((long long)listNode->data->hash).length(); k++) {
                            outputFile << " ";
                        }
                        outputFile << listNode->data->label;
                        for (int k = 0; k < 12 - listNode->data->label.length(); k++) {
                            outputFile << " ";
                        }
                        outputFile << std::hex << value << "\n";
                        
                        listNode = listNode->next;
                    }
                }
            }
			
            inputFile.close();
            outputFile.close();
            inputFile.open(outputFileName);
            while (std::getline(inputFile, line)) {
                std::cout << line << std::endl;
            }
            inputFile.close();
        }
    }
	
    return 0;
}
