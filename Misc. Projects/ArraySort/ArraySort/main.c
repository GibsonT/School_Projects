#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE 15

void ArraySort(int*, int);
void DispUnsortedArray(int*, int);
void DispSortedArray(int*, int);

int main()
{
	int i = 0;
	int unsortedArray[ARRAY_SIZE];

	//Seeding random number generator for unique array every run
	srand(time(NULL)); 
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		//Produces random integers between 1 and 50
		unsortedArray[i] = (rand() % 50) + 1;
	}

	DispUnsortedArray(unsortedArray, ARRAY_SIZE);
	DispSortedArray(unsortedArray, ARRAY_SIZE);

	system("PAUSE");
	return 0;
}

void ArraySort(int* arrayToSort, int arraySize)
{
	int i = 0;
	int j = 0;
	int tempHolder = 0;
	int arrayNotSorted = 1;

	//Bubble Sort - compares element 'i' to 'i + 1'and swaps values if 'i' is greater. 
	//Once at the end of the array, the process starts again and the loop
	//continues until 'arrayNotSorted' is not flagged.
	while (arrayNotSorted == 1)
	{
		arrayNotSorted = 0;
		
		for (i = 1; i < arraySize; i++)
		{
			j = i - 1;

			if ( *(arrayToSort + i) < *(arrayToSort + j) )
			{
				tempHolder = *(arrayToSort + j);
				*(arrayToSort + j) = *(arrayToSort + i);
				*(arrayToSort + i) = tempHolder;

				arrayNotSorted = 1;
			}
		}
	}

}

void DispUnsortedArray(int* unsortedArray, int arraySize)
{
	int i = 0;

	printf("Unsorted Array: \t");
	for (i = 0; i < arraySize; i++)
	{
		printf("%d ", *(unsortedArray + i));
	}

	printf("\n\n");
}

void DispSortedArray(int* arrayToSort, int arraySize)
{
	int i = 0;
	ArraySort(arrayToSort, arraySize);

	printf("Sorted Array: \t\t");
	for (i = 0; i < arraySize; i++)
	{
		printf("%d ", *(arrayToSort + i));
	}

	printf("\n\n");
}