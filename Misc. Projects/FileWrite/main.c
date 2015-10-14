#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* ID;
    int HP;

} Engine_s;

void GetInfo(Engine_s*, int*);
void DispInfo(Engine_s*, int);
void SaveRecord(Engine_s*, int, FILE*);
void ReadRecord(Engine_s*, int, FILE*);

int main()
{
    Engine_s* eng = NULL;
    int numOfEngs = 0;
    FILE* file = NULL;
    int i = 0;

    GetInfo(eng, &numOfEngs);
    /*SaveRecord(eng, numOfEngs, file);

    for (i = 0; i < numOfEngs; i++)
    {
        (eng + i)->ID = NULL;
        (eng + i)->HP = 0;
    }

    ReadRecord(eng, numOfEngs, file);*/
    DispInfo(eng, numOfEngs);

    return 0;
}

void GetInfo(Engine_s* eng, int* numOfEntries)
{
    int i = 0;
    char buf[25];
    memset(buf, 0, sizeof(buf));

    printf("In GetInfo()\n");

    printf("Enter number of engines to input: ");
    fgets(buf, 25, stdin);
    *numOfEntries = atoi(buf);
    eng = (Engine_s*)malloc(sizeof(Engine_s) * (*numOfEntries));
    memset(buf, 0, sizeof(buf));

    for (i = 0; i < *numOfEntries; i++)
    {
        memset(buf, 0, sizeof(buf));

        printf("Enter ID for engine #%d: ", i);
        fgets(buf, 25, stdin);
        (eng + i)->ID = (char*)malloc(sizeof(strlen(buf) + 1));
        strcpy((eng + i)->ID, buf);

        memset(buf, 0, sizeof(buf));

        printf("Enter HP: ");
        fgets(buf, 25, stdin);
        (eng + i)->HP = atoi(buf);

        printf("\n");
    }
}

void DispInfo(Engine_s* eng, int numOfEntries)
{
    int i = 0;

    printf("In DispInfo()\n");

    for (i = 0; i < numOfEntries; i++)
    {
        printf("\nEngine #%d:", i + 1);
        printf("\nID: %s", (eng + i)->ID);
        printf("HP: %d", (eng + i)->HP);
        printf("\n");
    }
}

void SaveRecord(Engine_s* eng, int numOfEntries, FILE* file)
{
    int i = 0;

    printf("In SaveRecord()");

    if ( !(file = fopen("engines.lst", "a+")) )
    {
        printf("File creation failed");
        exit(1);
    }

    for (i = 0; i < numOfEntries; i++)
    {
        fwrite((eng + i), sizeof(Engine_s), 1, file);
    }

    fclose(file);
}

void ReadRecord(Engine_s* eng, int numOfEntries, FILE* file)
{
    int i = 0;

    printf("In ReadRecord()\n");

    if ( !(file = fopen("engines.lst", "r")) )
    {
        printf("Error opening engines list");
        exit(1);
    }

    for (i = 0; i < numOfEntries; i++)
    {
        fread((eng + i), sizeof(Engine_s), 1, file);
    }
}
