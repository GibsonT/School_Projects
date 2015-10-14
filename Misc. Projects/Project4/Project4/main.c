#include <stdio.h>
#include <stdlib.h>

void AsciiCheck(int*, int);
int* AsciiReverse(char*, int);
int* ArraySwap(int* arrayToSwap, int arraySize);

int main()
{
	int i = 0;

	int arrayInt[10] = {55,41,23,12,20,15,56,98,78,4};
	int* sortedArray = ArraySwap(arrayInt, 10);

	printf("Before sort: ");
	for(i = 0; i < 10; i++)
	{
		printf("%d, ", arrayInt[i]);
	}

	printf("\nAfter sort: ");
	for (i = 0; i < 10; i++)
	{
		printf("%d, ", sortedArray[i]);
	}

	system("PAUSE");
	return 0;
}

void AsciiCheck(int* codeArray, int arraySize)
{
	char userChar;
	int matchCount = 0;
	int i = 0;
	int j = 0;

	for (i = 0; i < arraySize; i++)
	{
		printf("Enter character #%d to check: ", (i + 1));
		scanf("%c", &userChar);
		fflush(stdin);

		for (j = 0; j < arraySize; j++)
		{
			if ((int)userChar == *(codeArray + j))
			{
				matchCount++;
			}
		}

		printf("\n");
	}

	printf("Number of matches found: %d", matchCount);
}

int* AsciiReverse(char* charArray, int arraySize)
{
	int* asciiArray = malloc(arraySize * sizeof(int));
	int i = 0;
	int j = 0;
	int sortCheck = 0;
	int tempHolder = 0;
	int tempHolder2 = 0;

	for (i = 0; i < arraySize; i++)
	{
		*(asciiArray + i) = (int)*(charArray + i);
	}

	//Begin swaping process
	//1. Place ith element in temporary placeholder
	//2. Store value of ith from last element into ith element
	//3. Place temporary placeholder value into ith from last element
	for (i = 0; i < arraySize / 2; i++)
	{
		tempHolder = *(asciiArray + i);
		*(asciiArray + i) = *(asciiArray + ((arraySize - 1) - i));
		*(asciiArray + ((arraySize - 1) - i)) = tempHolder;
	}

	

	return asciiArray;
}

int* ArraySwap(int* arrayToSwap, int arraySize)
{
	int i = 0;
	int j = 0;
	int tempHolder = 0;
	
	for (i = 0; i < arraySize; i++)
	{
		for (j = i + 1; j < arraySize; j++)
		{
			if (arrayToSwap[j] < arrayToSwap[i])
			{
				tempHolder = arrayToSwap[i];
				arrayToSwap[i] = arrayToSwap[j];
				arrayToSwap[j] = tempHolder;
			}
		}
	}

	return arrayToSwap;
}
