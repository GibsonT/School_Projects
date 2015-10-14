#include <stdlib.h>
#include <stdio.h>

//NEXT HOMEWORK (HW5)
//1.) Add a function that allocates memory for char
//2.) Search for why we need 'lf' format code for double
//	  when using malloc()

void allocint();

int main()
{
	allocint();

	system("PAUSE");
	return 0;
}

void allocint()
{
	int x = 0;
	int i = 0;
	int* pNum = NULL;
	
	printf("How many elements: ");
	scanf("%d\n", &x);

	pNum = (int*)malloc(x * sizeof(int));

	for (i = 0; i < x; i++)
	{
		*(pNum + i) = i * 2;
		printf("pNum[%d] = %d\n", i, *(pNum + i));
	}

	free(pNum);
}

void allocdouble()
{
	int x = 0;
	double* pNum = NULL;

	pNum = (double*)malloc(x * sizeof(double));
}