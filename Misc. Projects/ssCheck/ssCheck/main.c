#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 10

int checkFormat(char*);
int checkLength(char*);
void getInfo(char*);

int main()
{
	char buf[BUFFER_SIZE];
	memset(buf, 0, sizeof(buf));
	getInfo(buf);

	system("PAUSE");
	return 0;
}

void getInfo(char* buffer)
{
	char groupOne[4];
	char groupTwo[3];
	char groupThree[5];
	memset(groupOne, 0, sizeof(groupOne));
	memset(groupTwo, 0, sizeof(groupTwo));
	memset(groupThree, 0, sizeof(groupThree));

	while(1)
	{
		printf("Enter your SSN without dashes: ");
		
		fflush(stdin);
		fgets(buffer, BUFFER_SIZE, stdin);

		if(checkLength(buffer) == -1)
		{
			printf("\nSorry, SSN is incorrect length. Please try again.\n");
		}
		else if(checkFormat(buffer) == -1)
		{
			printf("\nSorry, SSN is incorrect format. Please try again.\n");
		}
		else
		{
			strncpy(groupOne, buffer, 3);
			strncpy(groupTwo, (buffer + 3), 2);
			strncpy(groupThree, (buffer + 5), 4);
			printf("\n\nYour SSN is: %s-%s-%s\n", groupOne, groupTwo, groupThree);

			return;
		}
	}
}

int checkFormat(char* buffer)
{
	int i = 0;

	for (i = 0; i < strlen(buffer); i++)
	{
		if (*(buffer + i) < (int)'0' || *(buffer + i) > (int)'9')
		{
			return -1;
		}
	}

	return 1;
}

int checkLength(char* buffer)
{
	if (strlen(buffer) != BUFFER_SIZE - 1)
	{
		return -1;
	}

	return 1;
}

