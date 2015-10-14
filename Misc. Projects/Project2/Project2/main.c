#include <stdio.h>
#include <stdlib.h>

void AsciiCheck(int*, int);
int* AsciiReverse(char*, int);
int* BinAddition(int*, int*);

int main()
{
	int binOne[8] = {1,0,0,0,1,1,0,0};
	int binTwo[8] = {0,0,0,1,1,1,0,1};
	int* binSum = BinAddition(binOne, binTwo);
	int i = 0;

	for (i = 7; i >= 0; i--)
	{
		printf("%d\t%d\t%d\n", binOne[i], binTwo[i], binSum[i]);
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
	int* asciiArray = (int*)malloc(arraySize * sizeof(int));
	int i = 0;
	int swaps = arraySize / 2;
	int tempHolder = 0;

	for (i = 0; i < arraySize; i++)
	{
		*(asciiArray + i) = (int)*(charArray + i);
	}

	//Begin swaping process
	//1. Place ith element in temporary placeholder
	//2. Store value of ith from last element into ith element
	//3. Place temporary placeholder value into ith from last element
	for (i = 0; swaps > 0; i++)
	{
		tempHolder = *(asciiArray + i);
		*(asciiArray + i) = *(asciiArray + ((arraySize - 1) - i));
		*(asciiArray + ((arraySize - 1) - i)) = tempHolder;

		swaps--;
	}

	return asciiArray;
}

int* BinAddition(int* binArrayOne, int* binArrayTwo)
{
	int* binSum = (int*)malloc(8 * sizeof(int));
	int i = 0;
	int carry = 0;

	for (i = 7; i >= 0; i--)
	{
		if (i == 0 && *(binArrayOne + i) + *(binArrayTwo + i) + carry > 1)
		{
			return NULL;
		}
		
		switch (*(binArrayOne + i) + *(binArrayTwo + i) + carry)
		{
		case 0:
		case 1:
			*(binSum + i) = *(binArrayOne + i) + *(binArrayTwo + i) + carry;
			carry = 0;
			break;
		case 2:
			*(binSum + i) = 0;
			carry = 1;
			break;
		case 3:
			*(binSum + i) = 1;
			carry = 1;
			break;
		default:
			break;
		}
	}

	return binSum;
}
