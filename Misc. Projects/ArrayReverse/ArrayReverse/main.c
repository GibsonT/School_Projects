#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

int* arrayReverse(int*);
void printResult(int*, int*);

int main()
{
	int i = 0;
	int num[SIZE] = { 17, 4, 11, 94 };

	printResult(num, arrayReverse(num));

	printf("\n");
	system("PAUSE");

	return 0;
}

int* arrayReverse(int* arrayToReverse)
{
	static int reversedArray[SIZE] = {0};
	int i = 0;
	int j = SIZE - 1;
	
	for (i = 0; i < SIZE; i++)
	{
		*(reversedArray + j) = *(arrayToReverse + i);
		j--;
	}

	return reversedArray;
}

void printResult(int* intArray, int* reversedArray)
{
	int i = 0;

	printf("Original array: ");
	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", *(intArray + i));
	}

	printf("\nReversed array: ");
	for (i = 0; i < SIZE; i++)
	{
		printf("%d ", *(reversedArray + i));
	}
}