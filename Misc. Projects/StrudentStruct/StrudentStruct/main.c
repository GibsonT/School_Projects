//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COURSE_COUNT 2
#define COURSE_NAME_LIMIT 16

struct Student
{
	char name[20];
	float gpa;
	char courses[COURSE_COUNT][COURSE_NAME_LIMIT];
} typedef Student;

void SetStudent(Student*);
void DispStudent(Student*);

int main()
{
	Student student[3];
	Student* pStudent = &student[0];
	int i = 0;
	int j = 0;

	for (; i < 3; i++)
	{
		memset((pStudent + i)->name, 'G', sizeof((pStudent + i)->name));
		(pStudent + i)->gpa = 4.0;

		for (; j < COURSE_COUNT; j++)
		{
			memset( (pStudent + i)->courses[j], 'C', (sizeof((pStudent + i)->courses[j]) - sizeof(char)) );
			(pStudent + i)->courses[j][COURSE_NAME_LIMIT - 1] = '\0';
		}
		
	}

	SetStudent( (pStudent + 0) );
	DispStudent( (pStudent + 0) );
	system("PAUSE");
	return 0;
}

void SetStudent(Student* student)
{
	char* input = (char*)malloc(sizeof(char) * 20);
	int i = 0;

	printf("Enter student name: ");
	fgets(student->name, 20, stdin);

	printf("\nEnter GPA: ");
	fgets(input, 20, stdin);
	student->gpa = atof(input);

	for (i = 0; i < COURSE_COUNT; i++)
	{
		printf("\nEnter Course #%d: ", i);
		fgets(student->courses[i], COURSE_NAME_LIMIT, stdin);
	}
}

void DispStudent(Student* student)
{
	int i = 0;
	int j = 0;
	
	printf("Student name:\t\t%s\n", student->name);
	printf("Current GPA:\t\t%f\n", student->gpa);
	printf("Courses Enrolled:\t");
	for (i = 0; i < COURSE_COUNT; i++)
	{
		for (j = 0; j < COURSE_NAME_LIMIT; j++)
		{
			if (student->courses[i][j] == '\0' || student->courses[i][j] == '\n')
			{
				break;	
			}
			
			printf("%c", student->courses[i][j]);
		}

		printf("\n\t\t\t");
	}
}