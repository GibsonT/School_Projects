#include <stdio.h>
#include <stdlib.h>

//Also write hex converter by wed.

//TODO: change program to use strings for binary

int main()
{
	int decimalNum = 0;
	int binaryConv[64];
	
	int i;
	for (i = 0; i < 64; i++)
	{
		binaryConv[i] = 0;
	}

	while (decimalNum != -1)
	{
		printf("Enter integer number to convert to binary: ");
		scanf("%d", &decimalNum);
		printf("\n\nYour binary conversion is ");



		for (i = 0; decimalNum >= 1; i++)
		{
			if (decimalNum % 2 == 0)
			{
				binaryConv[i] = 0;
			}
			else
			{
				binaryConv[i] = 1;
			}
			
			decimalNum = decimalNum / 2;
		}

		for (i = 63; i > -1; i--)
		{
			if (binaryConv[i] == 0 && i == 63)
			{
				while (binaryConv[i] == 0)
				{
					i--;
				}
			}

			printf("%d", binaryConv[i]);
		}

		printf("\n\n\n");
	}

	printf("\n\n");
	system("PAUSE");
	return 0;
}