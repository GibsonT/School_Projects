#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int rpm;
	float weight;
} Engine_s;

void sortByWeight(Engine_s*, int);

int main()
{
	Engine_s engines[3];
	int i = 0;

	engines[0].weight = 0.5;

	engines[1].weight = 0.25;

	engines[2].weight = 3;

	for (i = 0; i < 3; i++)
	{
		printf("%f\n", engines[i].weight);
	}

	printf("\n");

	sortByWeight(engines, 3);

	for (i = 0; i < 3; i++)
	{
		printf("%f\n", engines[i].weight);
	}

	system("PAUSE");
}

void sortByWeight(Engine_s* engineList, int size)
{
	Engine_s temp;
	int continueLoop = 0;
	int i;

	do 
	{
		continueLoop = 0;

		for (i = 0; i < size - 1; i++)
		{
			if ((engineList + i)->weight < ((engineList + (i + 1))->weight))
			{
				temp = *(engineList + i);
				*(engineList + i) = *(engineList + (i + 1));
				*(engineList + (i + 1)) = temp;
				continueLoop = 1;
			}
		}

	} while (continueLoop);
}