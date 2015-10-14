#include <stdlib.h>
#include <stdio.h>

void allocInt();
void allocChar();

int main()
{
    allocChar();
    //allocInt();
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
    char* pChar = NULL;
    int size = 0;
    int i = 0;

    printf("Enter size for array: ");
    scanf("%d", &size);

    pChar = (char*)malloc(size * sizeof(char));
    for (i = 0; i < size; i++)
    {
         while (getchar() != '\n');     //Needed to clear input buffer of newline
         printf("\nEnter character for element %d: ", i);
        *(pChar + i) = getchar();
    }

    printf("\n");

    for (i = 0; i < size; i++)
    {
        printf("\nValue stored at element %d is %c.", i, *(pChar + i));
    }

    printf("Freeing memory stored at &pChar...\n");
    free(pChar);
    printf("Memory freed!");
}

