#include "linkedlist.h"
#include "hashtable.h"
#include "element.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>

void pass1(std::ifstream* inputFile, HashTable* labelTable, HashTable* opsTable);
void pass2(std::ifstream* inputFile, HashTable* labelTable, HashTable* opsTable, std::ofstream* lstFile, std::ofstream* objFile);

int main(int argc, char* argv[]) {
    std::ifstream inputFile;
	std::ifstream opsList;
	std::ofstream lstFile;
	std::ofstream objFile;
	std::string line;
	HashTable* labelTable = new HashTable(101);
	HashTable* opsTable = new HashTable(101);
    if (argc < 2) {
        std::cout << "No input given. Exiting.";
		return 1;
    }
	// Open source file
	inputFile.open(argv[1]);

	// Create and open *.lst
	std::string lstFileName = (std::string)argv[1] + ".lst";
	lstFile.open(lstFileName);

	// Create and open *.obj
	std::string objFileName = (std::string)argv[1] + ".obj";
	objFile.open(objFileName);

	// Fill operations table
	opsList.open("ops.dat");
	while (std::getline(opsList, line)) {
		std::string operation;
		std::string info;    // For opcode and SIC \ SIC/XE sizes
		Element *operationElement = new Element();
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

		opsTable->insert(operationElement);
	}

	opsList.close();

	pass1(&inputFile, labelTable, opsTable);
	inputFile.close();
	inputFile.open(argv[1]);
	pass2(&inputFile, labelTable, opsTable, &lstFile, &objFile);

	inputFile.close();
	objFile.close();
	lstFile.close();

    return 0;
}

void pass1(std::ifstream* inputFile, HashTable* labelTable, HashTable* opsTable) {
	std::string line;

	if (inputFile->is_open()) {
		bool startFound = false;
		bool endFound = false;
		int startAddress = 0;
		int PC = 0;

		while (std::getline(*inputFile, line)) {
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
				continue;
			}

			// Check for label. If none, then there's nothing to record
			if (line[0] != ' ') {
				for (int i = 0; i < 9 && line[i] != ' ' && i < line.length(); i++) {
					label += line[i];
				}
			}
			else {
				continue;
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
            // Only 2 prefixes supported right now, skip to next line otherwise
			else if (line[9] != ' ') {
				continue;
			}

			// Load and check mneumonic
			if (line[10] == ' ') {
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

			Element *mneumonicElement = new Element();
			if (mneumonicPrefix != ' ') {
				mneumonicElement->label = mneumonicPrefix + mneumonic;
			}
			else {
				mneumonicElement->label = mneumonic;
			}

			mneumonicElement = opsTable->find(mneumonicElement);
			if (mneumonicElement == NULL) {
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
					continue;
			}

			for (int i = 19; i < 28 && i < line.length(); i++) {
				if (line[i] == ' ') {
					break;
				}

				operand = operand + line[i];
			}

			// This is an assembly operation
			if (mneumonicElement->value == "0000") {
				std::string assemblerDirective = mneumonicElement->label;
				if (assemblerDirective == "START") {
					if (!startFound) {
						startAddress = std::stoi(operand, NULL, 16);
						PC = std::stoi(operand, NULL, 16);
						startFound = true;
						continue;
					}
					else {
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
				Element *labelElement = new Element();
				labelElement->label = label;
				labelElement->value = std::to_string((long long) PC);
				if (labelTable->insert(labelElement) == 1) {
					continue;
				}
			}

			PC += operationSize;
		}
	}
}

void pass2(std::ifstream* inputFile, HashTable* labelTable, HashTable* opsTable, std::ofstream* lstFile, std::ofstream* objFile) {
	std::string line;
	enum Register {
		A,
		X,
		L,
		B,
		S,
		T,
		F
	};

	if (inputFile->is_open()) {
		bool startFound = false;
		bool endFound = false;
		int startAddress = 0;
		int currentAddress = 0;
		int PC = 0;
		int xRegister = 0;

		while (std::getline(*inputFile, line)) {
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
			std::string comment;
			char operandPrefix = ' ';
			std::string operand[3];
			for (int i = 0; i < 3; i++) {
				operand[i] = "?";
			}

			// Check if line is blank or a comment, continue to next line if so
			if (line.size() == 0 || line[0] == '.') {
				*lstFile << line;
				*lstFile << '\n';
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
				pFlag = false;
				mneumonicPrefix = '+';
			}
            // ...or a SIC compatible one?
			else if (line[9] == '*') {
				mneumonicPrefix = '*';
			}
			else if (line[9] != ' ') {
				*lstFile << " ***ERROR: UNSUPPORTED MNEUMONIC PREFIX: " << line[9] << "***\n";
				continue;
			}

			// Load and check mneumonic
			if (line[10] == ' ') {
				*lstFile << " ***ERROR: NO MNEUMONIC DECLARED***\n";
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

			Element *mneumonicElement = new Element();
			if (mneumonicPrefix != ' ') {
				mneumonicElement->label = mneumonicPrefix + mneumonic;
			}
			else {
				mneumonicElement->label = mneumonic;
			}
			mneumonicElement = opsTable->find(mneumonicElement);
			if (mneumonicElement == NULL) {
				*lstFile << " ***ERROR: INVALID MNEUMONIC OR NOT SUPPORTED: " << mneumonic << " ***\n";
				continue;
			}

			// Is there an operand prefix?
			operandPrefix = line[18];
			switch (operandPrefix) {
				case '#':
					iFlag = true;
					nFlag = false;
					break;
				case '@':
					nFlag = true;
					iFlag = false;
					break;
				case ' ':
					break;
				default:
					*lstFile << " ***ERROR: OPERAND PREFIX NOT RECOGNIZED***\n";
					continue;
			}

			if (operand[1][0] == 'X') {
				xFlag = true;
			}

			int operandCounter = 0;
			for (int i = 19; i < 28 && i < line.length(); i++) {
				if (operand[operandCounter] == "?") {
					operand[operandCounter] = "";
				}

				if (line[i] == ' ') {
					break;
				}
				if (line[i] == ',') {
					operandCounter++;
					continue;
				}

				operand[operandCounter] = operand[operandCounter] + line[i];
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
						if (operand[0] == "?") {
							*lstFile << "ERROR: NO START ADDRESS DEFINED";
							break;
						}
						startAddress = std::stoi(operand[0], NULL, 16);
						currentAddress = startAddress;
						startFound = true;
						*objFile << std::setw(6) << std::setfill('0') << std::hex << currentAddress << std::endl;
						*objFile << "000000\n";
					}
					else {
						*lstFile << "***ERROR: START ALREADY DECLARED AT ADDRESS " << startAddress << "***\n";
						continue;
					}
				}
				else if (assemblerDirective == "END") {
					*objFile << "!";
					break;
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
					operationSize = 0x3 * std::stoi(operand[0], NULL, 10);
				}
				else if (assemblerDirective == "RESB") {
					operationSize = 0x1 * std::stoi(operand[0], NULL, 10);
				}
			}
			else {
				std::string opSizeString;
				std::stringstream opCodeStringStream;
				std::string opCountString;
				std::string objectCodeString;
				int objectCode;
				char registerValue[2];
				int requiredOperandCount;

				registerValue[0] = '?';
				registerValue[1] = '?';

				opCodeStringStream << mneumonicElement->value[0];
				opCodeStringStream << mneumonicElement->value[1];

				opCountString = mneumonicElement->value[3];
				requiredOperandCount = stoi(opCountString, NULL, 10);

				opSizeString += mneumonicElement->value[2];
				operationSize = std::stoi(opSizeString, NULL, 16);

				objectCode = std::stoi(opCodeStringStream.str(), NULL, 16);
				if (operationSize > 2) {
					if (nFlag) {
                        objectCode += 2;
						opCodeStringStream.str("");
						opCodeStringStream.clear();
						opCodeStringStream << std::hex << objectCode;
					}

					if (iFlag) {
                        objectCode += 1;
						opCodeStringStream.str("");
						opCodeStringStream.clear();
						opCodeStringStream << std::hex << objectCode;
					}
				}

				// This is a register - register operation
				if (operationSize == 2) {
					for (int i = 0; i < requiredOperandCount && operand[i] != "?"; i++) {
						switch (operand[i][0]) {
							case 'A':
								registerValue[i] = '0';
								break;
							case 'X':
								registerValue[i] = '1';
								break;
							case 'L':
								registerValue[i] = '2';
								break;
							case 'B':
								registerValue[i] = '3';
								break;
							case 'S':
								registerValue[i] = '4';
								break;
							case 'T':
								registerValue[i] = '5';
								break;
							case 'F':
								registerValue[i] = '6';
								break;
							default:
								break;
						}
					}

					if (requiredOperandCount == 1) {
						if (registerValue[0] != '?') {
							objectCodeString = opCodeStringStream.str();
							objectCodeString.push_back(registerValue[0]);
							objectCodeString.push_back('0');
						}
						else {
							*lstFile << "INVALID OPERAND OR INCORRECT NUMBER OF OPERANDS" << "\n";
							continue;
						}
					}

					else if (requiredOperandCount == 2) {
						if (registerValue[0] != '?' && registerValue[1] != '?') {
							objectCodeString = opCodeStringStream.str();
							objectCodeString.push_back(registerValue[0]);
							objectCodeString.push_back(registerValue[1]);
						}
						else {
							*lstFile << "INVALID OPERAND OR INCORRECT NUMBER OF OPERANDS" << "\n";
							continue;
						}
					}
					else {
						objectCodeString = opCodeStringStream.str() + "00";
					}

					*objFile << objectCode << "\n";
				}

				else if (operationSize > 2) {
					std::stringstream addressOffsetStringStream;
					std::stringstream addressOffsetHexStringStream;
					std::string addressOffsetString;
					Element* labelElement = new Element();
					int addressOffset = 0;
					int xbpeModifier = 0;
					int totalAddressDigits = 3;

					if (eFlag) {
						totalAddressDigits = 5;
					}

					if (operand[0] == "?") {
						*lstFile << "NO OPERAND DECLARED" << "\n";
						continue;
					}

					if (isdigit(operand[0][0])) {
						addressOffset = std::stoi(operand[0]);
					}

					else {
						labelElement->label = operand[0];
						labelElement = labelTable->find(labelElement);
						if (labelElement == NULL) {
							*lstFile << "LABEL NOT DEFINED: " << operand[0];
							continue;
						}

						if (iFlag && !nFlag) {
							addressOffset = std::stoi(labelElement->value, NULL, 10);
						}
						else {
							addressOffset = std::stoi(labelElement->value, NULL, 10) - (PC + operationSize);
						}
					}

                    if (xFlag) {
                        addressOffset += xRegister;
                        xbpeModifier += 8;
                    }
                    if (bFlag) {
                        xbpeModifier += 4;
                    }
                    if (pFlag) {
                        xbpeModifier += 2;
                    }
                    if (eFlag) {
                        xbpeModifier += 1;
                    }

                    addressOffsetStringStream << std::hex << xbpeModifier;
                    addressOffsetHexStringStream << std::hex << addressOffset;
                    for (int i = totalAddressDigits; i > addressOffsetHexStringStream.str().length(); i--) {
                        addressOffsetStringStream << "0";
                    }

					addressOffsetStringStream << std::hex << addressOffset;
					addressOffsetString = addressOffsetStringStream.str();
					objectCodeString = opCodeStringStream.str();
					objectCodeString = objectCodeString + addressOffsetString;

					*objFile << objectCodeString << "\n";
                }


            }
        }
			/*if (label.length() > 0) {
				Element *labelElement = new Element();
				labelElement->label = label;
				labelElement->value = std::to_string((long long) PC);
				if (labelTable->insert(labelElement) == 1) {
					lstFile << "***ERROR: LABEL ALREADY EXISTS - " << label << "***\n";
					continue;
				}
			}*/

			/*lstFile << std::hex << PC;
			for (int i = 0; i < 8 - std::to_string((long long) PC).length(); i++) {
				lstFile << " ";
			}
			lstFile << label;
			for (int i = 0; i < 8 - label.length(); i++) {
				lstFile << " ";
			}
			lstFile << mneumonicPrefix << mneumonic;
			for (int i = 0; i < 8 - mneumonic.length(); i++) {
				lstFile << " ";
			}
			lstFile << operandPrefix << operand;
			for (int i = 0; i < 8 - operand.length(); i++) {
				lstFile << " ";
			}
			lstFile << comment << "\n";

			PC += operationSize;
		}*/

		/*outputFile << "\n\n";
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
		}*/

	}
}
