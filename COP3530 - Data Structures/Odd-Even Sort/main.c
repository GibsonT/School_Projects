#include "main.h"

int main(int argc, char* argv[]) {
	
    //There was an argument entered, lets see if it's a valid file
	if (argc > 1) {
		FILE* inputFile = fopen(argv[1], "r");
		
		//File couldn't be opened, close program
		if (inputFile == NULL) {
			printf("Unable to open file: "); printf(argv[1]); printf("\n");
			printf("Exiting. . .");
		}
		
		//File was opened, lets have fun!
		else {
			int sizeOfArray;
			int i;
			
			//Grab first number from file to set array size
			fscanf(inputFile, "%d", &sizeOfArray);
			int inputArray[sizeOfArray];
			
			//Fill the array with file contents
			for (i = 0; i < sizeOfArray; i++) {
				fscanf(inputFile, "%d", &inputArray[i]);
			}
			
			fclose(inputFile);								//Close the file, it's not needed anymore
			oddEvenSort(inputArray, sizeOfArray);			//Sort that sucker with the odd-even sort implementation
			
			//Grab inputs to check sorted array indices
			while(1) {
				int indexInput;
				printf("Enter index to check: ");
				scanf("%d", &indexInput);
				
				//-1 ends input and closes the program
				if (indexInput == -1) {
					break;
				}
				
				printf("The number at index %d is %d.\n\n", indexInput, inputArray[indexInput]);
			}
		}
	}
	
	//File wasn't entered as argument, give error message and close
	else {
		printf("No file was entered as argument, closing . . .\n");
	}
	
    return 0;
}

void oddEvenSort(int arrayToSort[], int arraySize) {
    int sorted;
	int i;
    
    do {
        i = 0;
        sorted = 1;

        //Start with odd indexes and their neighbors...
		for (i = 1; i < arraySize - 1; i += 2) {
            if (arrayToSort[i] > arrayToSort[i + 1]) {
                swap(&arrayToSort[i], &arrayToSort[i + 1]);
                sorted = 0;
            }
        }
		
		//...and then do the even indexes
        for (i = 0; i < arraySize - 1; i += 2) {
            if (arrayToSort[i] > arrayToSort[i + 1]) {
                swap(&arrayToSort[i], &arrayToSort[i + 1]);
                sorted = 0;
            }
        }

    } while (!sorted);
}

void swap(int* numberOne, int* numberTwo) {
	int temp = *numberOne;
	*numberOne = *numberTwo;
	*numberTwo = temp;
}
