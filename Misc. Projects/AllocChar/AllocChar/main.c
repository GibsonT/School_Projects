#include <stdlib.h>
#include <stdio.h>

void allocInt();
void allocChar();
void allocDouble();

int main()
{
	allocChar();
	//allocInt();
	//-allocDouble();

	system("PAUSE");
	return 0;
}

void allocInt()
{
	int* pNum = NULL;
	int size = 0;
	int i = 0;

	printf("Enter size for array: ");
	scanf("%d", &size);

	pNum = (int*)malloc(size * sizeof(int));

	for (i = 0; i < size; i++)
	{
		printf("\nEnter value for element %d:", i);
		scanf("%d", (pNum + i));
	}

	printf("\n");

	for (i = 0; i < size; i++)
	{
		printf("\nValue stored at element %d is %d.", i, *(pNum + i));
	}

	printf("Freeing memory stored at &pNum...\n");
	free(pNum);
	printf("Memory freed!");
}

void allocChar()
{
	char* pChar = &pChar[0];
	int size = 0;
	int i = 0;

	printf("Enter size for array: ");
	scanf("%d", &size);

	//Allocating memory for pChar (size of array user specified * the size of char variable (1 byte))
	pChar = (char*)malloc(size * sizeof(char));

	for (i = 0; i < size; i++)
	{
		//This is needed to clear the input buffer before each new entry.
		//Otherwise, the program will see two inputs: the user input and the newline
		//character when the user presses enter. This will cause the program
		//to count the newline as a user input and store it in the next array element.
		while (getchar() != '\n');

		printf("\nEnter character for element %d: ", i);
		*(pChar + i) = getchar();
	}

	printf("\n");

	for (i = 0; i < size; i++)
	{
		printf("\nValue stored at element %d is %c.", i, *(pChar + i));
	}

	printf("\n\nFreeing memory stored at &pChar...\n");

	//Deallocating the memory allocated to pChar
	free(pChar);

	printf("Memory freed!\n");
}

void allocDouble()
{
	double* pDouble = NULL;
	int size = 0;
	int i = 0;

	printf("Enter size for array: ");
	scanf("%d", &size);

	//Allocating memory for pDouble (size of array user specified * the size of double variable (8 bytes))
	pDouble = (double*)malloc(size * sizeof(double));

	for (i = 0; i < size; i++)
	{
		printf("\nEnter value for element %d:", i);

		//%lf is needed because of the way C promotes variables in function arguments.
		//
		//The function printf() takes in two things: the string to print, and the variables
		//to print for any type masks present inside of the string. C will automatically
		//promote types like float to double, along with their respective type masks,
		//which means that specifying "%f" is enough in printf();
		//
		//In functions like scanf(), however, they don't take in variables, but pointers.
		//C doesn't automatically promote pointers, which means that it's up to the user
		//to specify the correct type. If the incorrect format is used (such as %f instead
		//of %lf), then C is going to try to fit the bigger size inside of the smaller size
		//allocated, which can lead to incorrect values and overflow issues.
		scanf("%lf", (pDouble + i));
	}

	printf("\n");

	for (i = 0; i < size; i++)
	{
		printf("\nValue stored at element %d is %f.", i, *(pDouble + i));
	}

	printf("\n\nFreeing memory stored at &pDouble...\n");

	//Deallocating memory allocated to pDouble
	//
	//When free() is placed inside of a loop, this causes the program to try
	//to free() the memory multiple times. Because you're ofter trying to 
	//access the memory while still in the loop, this can cause the program
	//to give garbage values, as the memory is now free to use in other processes.
	free(pDouble);

	printf("Memory freed!\n\n");
}