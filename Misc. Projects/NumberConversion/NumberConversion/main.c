/************************************************************************/
/* Assignment #: Number Base Converter                                  */
/*                                                                      */
/* Author: Travis Gibson                                                */
/*                                                                      */
/* Class: COP2220, Reference #378760                                    */
/*                                                                      */
/* Due Date: February 4th, 2013                                         */
/*                                                                      */
/* Purpose:  Converts a decimal number into either octal or hex			*/
/*			 base. Also has an option to view an ASCII character's		*/
/*			 binary equivalent.											*/					
/*          		            									    */
/************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char displayBeginningMenu();
int displayMainMenu();
void convDectoBin(int);
void convDectoHex(int);
void convDecToOct(int);
void convAsciiToBin(char);
void displayConvResult(int, char*, int, int);

int main()
{
	int menuSelection = 0;
	int decToConvert = 0;
	char charToConvert = ' ';
	
	if (toupper(displayBeginningMenu()) == 'Y')
	{
		//Begin main menu loop
		do 
		{
			menuSelection = displayMainMenu();

			switch (menuSelection)
			{
				case 1:
					printf("Decimal -> Binary Converter\n");
					printf("---------------------------\n");
					printf("Enter a decimal value: ");
					scanf("%d", &decToConvert);
					fflush(stdin);
					convDectoBin(decToConvert);
					break;
				case 2:
					printf("Decimal -> Hexadecimal Converter\n");
					printf("---------------------------\n");
					printf("Enter a decimal value: ");
					scanf("%d", &decToConvert);
					fflush(stdin);
					convDectoHex(decToConvert);
					break;
				case 3:
					printf("Decimal -> Octal Converter\n");
					printf("---------------------------\n");
					printf("Enter a decimal value: ");
					scanf("%d", &decToConvert);
					fflush(stdin);
					convDecToOct(decToConvert);
					break;
				case 4:
					printf("ASCII -> Binary Converter\n");
					printf("---------------------------\n");
					printf("Enter character value: ");
					scanf("%c", &charToConvert);
					fflush(stdin);
					convAsciiToBin(charToConvert);
					break;
				default:
					break;
			}

		} while (menuSelection != 5);
		//End main menu loop
	}

	return 0;
}

//Displays a menu that prompts a user to either start the main program or exit.
char displayBeginningMenu() 
{
	char menuSelection;
	
	system("CLS");
	
	printf("**********************************************************\n");
	printf("****               Number Base Converter              ****\n");
	printf("**********************************************************\n\n");
	printf("This program converts decimal numbers into their octal and\n");
	printf("hex equivalents. There is also an option available to view a\n");
	printf("button's ASCII binary equivalent.\n\n");
	printf("Continue with execution? (y/n)");
	
	scanf("%c", &menuSelection);
	fflush(stdin);
	return menuSelection;
}

//Displays the main menu of the program to the user.
//1 = decimal -> binary conversion
//2 = decimal -> hex conversion
//3 = decimal -> octal conversion
//4 = ASCII decimal -> binary conversion
//5 = Exit program
int displayMainMenu()
{
	int menuSelection = 0;

	system("CLS");

	printf("**********************************************************\n");
	printf("****                    Main Menu                     ****\n");
	printf("**********************************************************\n\n");
	printf("1. - Convert decimal to binary\n");
	printf("2. - Convert decimal to hex\n");
	printf("3. - Convert decimal to octal\n");
	printf("4. - Convert ASCII character to binary\n");
	printf("5. - Exit\n\n");
	printf("Enter selection (1-5): ");

	scanf("%d", &menuSelection);
	printf("\n");
	
	//Ensure user input valid selection
	while (menuSelection < 1 || menuSelection > 5)
	{
		printf("\nPlease make a valid selection (1-5): ");
		scanf("%d", &menuSelection);
		printf("\n");
	}

	fflush(stdin);
	return menuSelection;
}

//Converts any ASCII character to its binary equivalent
void convAsciiToBin(char asciiChar)
{
	printf("\n");
	printf("Character Value: %c\n", asciiChar);
	convDectoBin((int)asciiChar);
}

//Converts a decimal number to binary
void convDectoBin(int decNum)
{
	int decCopy = decNum;
	char binNum[33] = "";
	char remainderBuf[2] = "";

	//Convert remainder into string and append to main binary conversion
	while (decCopy > 0)
	{
		itoa(decCopy % 2, remainderBuf, 10);
		strcat(binNum, remainderBuf);
		decCopy /= 2;
	}

	displayConvResult(decNum, binNum, 33, 2);
}

//Converts decimal number to hexadecimal
void convDectoHex(int decNum)
{
	int decCopy = decNum;
	char hexNum[33] = "";
	char remainderBuf[3] = "";

	//Convert remainder into string and append to main hex conversion
	while (decCopy > 0)
	{
		//If remainder > 10, append appropriate letter; otherwise, append single digit
		switch (decCopy % 16)
		{
		case 10:
			strcat(hexNum, "A");
			break;
		case 11:
			strcat(hexNum, "B");
			break;
		case 12:
			strcat(hexNum, "C");
			break;
		case 13:
			strcat(hexNum, "D");
			break;
		case 14:
			strcat(hexNum, "E");
			break;
		case 15:
			strcat(hexNum, "F");
			break;
		default:
			itoa(decCopy % 16, remainderBuf, 10);
			strcat(hexNum, remainderBuf);
			break;
		}
		
		decCopy /= 16;
	}

	displayConvResult(decNum, hexNum, 33, 16);
}

//Converts decimal number to octal
void convDecToOct(int decNum)
{
	int decCopy = decNum;
	char octNum[33] = "";
	char remainderBuf[2] = "";

	//Convert remainder into string and append to main octal conversion
	while (decCopy > 0)
	{
		itoa(decCopy % 8, remainderBuf, 10);
		strcat(octNum, remainderBuf);
		
		decCopy /= 8;
	}

	displayConvResult(decNum, octNum, 33, 8);
}

//Displays the result of any decimal conversion
void displayConvResult(int originalNum, char* result, int resultSize, int base)
{
	int i = 0;
	
	printf("Decimal: %d\n", originalNum);

	//Check base and apply appropriate label
	switch (base)
	{
	case 2:
		printf("Binary: ");
		break;
	case 8:
		printf("Octal: ");
		break;
	case 16:
		printf("Hexadecimal: ");
		break;
	default:
		printf("Base %d: ", base);
		break;
	}
	
	//Begin reading conversion string
	for (i = resultSize - 1; i >= 0; i--)
	{
		if (i == resultSize - 1)
		{
			//Skip null terminators
			while (result[i] == '\0')
			{
				i--;
			}

			//Formatting for binary conversions
			while (base == 2 && (i + 1) % 4 != 0)
			{
				i++;
				result[i] = '0';
			}
		}

		//Space binary conversions in groups of four
		if (base == 2 && (i + 1) % 4 == 0)
		{
			printf(" ");
		}

		printf("%c", result[i]);
	}

	printf("\n\n");
	system("PAUSE");
}