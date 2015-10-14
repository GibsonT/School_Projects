/********************************************************
 * Casino Project (Phase I)
 *
 * Author: Travis Gibson
 * Date:   April 23rd, 2013
 *
 * BEWARE YE WHO ENTER, HERE BE DRAGONS
 *
 *******************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define BUF_SIZE                 50
#define MAX_CLIENT_COUNT         10
#define MAX_NAME_COUNT           15
#define ID_VALIDATE_MAX_ATTEMPTS 3

typedef struct
{
    int isRegistered;
    char* firstName;
    char* lastName;
    char* email;
    char* id;
    float funds;
    float currentWager;
} Client_s;

typedef enum
{
    REGISTER = 1,
    ATM,
    PLAY,
    QUIT     = 9
} MenuSelection_e;

MenuSelection_e MainMenu();
void RegisterClient(Client_s*);
void AccessATM(Client_s*);
void PlayCasino(Client_s*);
int ValidMoneyAmount(char*);
int IdValidation(Client_s*);
void PrintReturnToMMMsg();
void Clearstdin();
void RemoveNewline(char*);
void PrintClientProfile(Client_s*, int, float);
void NameInput(char*);
int IsEmailValid(char*);
void CasinoIdInput(char*, Client_s*);
void DisplayGameResult(int, int, int);

int main()
{
    int i = 0;

    Client_s clientList[MAX_CLIENT_COUNT];
    MenuSelection_e selection;
    int atmFrozen = 0;
    int casinoFrozen = 0;
    int clientIndex = 0;

    for (i = 0; i < MAX_CLIENT_COUNT; i++)
    {
        (clientList + i)->isRegistered = 0;
        (clientList + i)->firstName    = NULL;
        (clientList + i)->lastName     = NULL;
        (clientList + i)->email        = NULL;
        (clientList + i)->id           = 0;
        (clientList + i)->funds        = 0;
        (clientList + i)->currentWager = 0;
    }

    do
    {
        selection = MainMenu();

        switch (selection)
        {
            case REGISTER:
            {
                RegisterClient(clientList);
                break;
            }

            case ATM:
            {
                if (atmFrozen)
                {
                    printf("Sorry, ATM access on this machine has been frozen.\n");
                    printf("Please see a financial manager for assistance.\n\n");
                    PrintReturnToMMMsg();
                    continue;
                }
                else if (!clientList->isRegistered)
                {
                    printf("No clients were found on this machine!\n");
                    printf("Please register before accessing the ATM.\n\n");
                    PrintReturnToMMMsg();
                    continue;
                }

                clientIndex = IdValidation(clientList);
                if (clientIndex == -2)
                {
                    atmFrozen = 1;
                    printf("ATM access on this machine is now frozen.\n");
                    printf("Please see a financial manager for details.\n\n");
                    PrintReturnToMMMsg();
                    continue;
                }
                else if (clientIndex == -1)
                {
                    continue;
                }

                AccessATM(clientList + clientIndex);
                break;
            }

            case PLAY:
            {
                if (casinoFrozen)
                {
                    printf("Sorry, casino access on this machine has been frozen.\n");
                    printf("Please see a floor manager for assistance.\n\n");
                    PrintReturnToMMMsg(); continue; }
                else if (!clientList->isRegistered)
                {
                    printf("No clients were found on this machine!\n");
                    printf("Please register before accessing the casino.\n\n");
                    PrintReturnToMMMsg();
                    continue;
                }

                clientIndex = IdValidation(clientList);
                if (clientIndex == -2)
                {
                    casinoFrozen = 1;
                    printf("Casino access on this machine is now frozen.\n");
                    printf("Please see a floor manager for details.\n\n");
                    PrintReturnToMMMsg();
                    continue;
                }
                else if (clientIndex == -1)
                {
                    continue;
                }

                PlayCasino(clientList + clientIndex);
                break;
            }

            default:
            {
                break;
            }
        }

    } while (selection != QUIT);

    return 0;
}

MenuSelection_e MainMenu()
{
    int selection = 0;
    char buf[3];
    memset(buf, 0, sizeof(buf));

    system("CLS");
//  system("clear");    //Needed to clear terminal screen on Linux

    printf("//************************************************\n");
    printf("//***        SUNBRUISE CASINO MAIN MENU        ***\n");
    printf("//************************************************\n");
    printf("//////////////////////////////////////////////////\n\n\n");
    printf("1. - Register New Client\n\n");
    printf("2. - Access ATM System\n\n");
    printf("3. - Wager & Play!\n\n\n");
    printf("9. - Quit\n\n");
    printf("Please make a selection: ");

    do
    {
        fgets(buf, 3, stdin);
        RemoveNewline(buf);
        selection = atoi(buf);

        if ( (selection < 1 || selection > 3) && selection != 9 )
        {
            printf("\nThat is not a valid choice, please try again: ");
            memset(buf, 0, sizeof(buf));
            continue;
        }

    } while (!selection);

    return (MenuSelection_e)selection;
}

void RegisterClient(Client_s* clientList)
{
    char buf[BUF_SIZE];
    char* firstName;
    char* lastName;
    char* email;
    char* id;
    int i = 0;
    int clientNum = 0;
    memset(buf, 0, sizeof(buf));

    system("CLS");
    //system("clear");

    printf("//************************************************\n");
    printf("//***          NEW CLIENT REGISTRATION         ***\n");
    printf("//************************************************\n");
    printf("//////////////////////////////////////////////////\n\n\n");

    //Start input of first name
    printf("First name (%d alphabetical characters max): ", MAX_NAME_COUNT);
    NameInput(buf);
    firstName = (char*)malloc(strlen(buf) + 1);
    strcpy(firstName, buf);

    //Start input of last name
    printf("Last name (%d alphabetical characters max): ", MAX_NAME_COUNT);
    NameInput(buf);
    lastName = (char*)malloc(strlen(buf) + 1);
    strcpy(lastName, buf);

    //Start email input
    printf("Email: ");
    fgets(buf, BUF_SIZE, stdin);
    RemoveNewline(buf);
    while (!IsEmailValid(buf))
    {
        printf("\nSorry, that email is not valid. Please try again.\n");
        printf("Email: ");
        fgets(buf, BUF_SIZE, stdin);
        RemoveNewline(buf);
    }
    email = (char*)malloc(strlen(buf) + 1);
    for (i = 0; i < strlen(buf); i++)
    {
        *(buf + i) = toupper( *(buf + i));
    }
    strcpy(email, buf);

    //Start ID input
    printf("Enter the 9 digit casino ID you wish to use (numeric only): ");
    CasinoIdInput(buf, clientList);
    id = (char*)malloc(strlen(buf) + 1);
    strcpy(id, buf);

    //Set client information
    for (i = 0; i < MAX_CLIENT_COUNT; i++)
    {
        if ((clientList + i)->isRegistered)
        {
            if(!strcmp(firstName, (clientList + i)->firstName) &&
                    !strcmp(lastName, (clientList + i)->lastName) &&
                        id == (clientList + i)->id)
            {
                printf("\nYou are already registered in our system!\n");
                printf("Please use your casino ID to access our ATM and play room.\n\n");
                PrintReturnToMMMsg();
                return;
            }
            else if(i == MAX_CLIENT_COUNT - 1)
            {
                printf("\nSorry, the maximum number of clients have been reached.\n");
                printf("Please speak to a registration assistant for assistance.\n\n");
                PrintReturnToMMMsg();
                return;
            }
        }
        else
        {
            clientNum = i;
            break;
        }
    }

    (clientList + clientNum)->firstName    = firstName;
    (clientList + clientNum)->lastName     = lastName;
    (clientList + clientNum)->email        = email;
    (clientList + clientNum)->id           = id;
    (clientList + clientNum)->isRegistered = 1;
    (clientList + clientNum)->funds        = 0;
    (clientList + clientNum)->currentWager = 0;

    printf("\n***Thank you for registering!***\n\n");
    printf("Here is your information:\n");
    PrintClientProfile(clientList + i, 0, 0);
    printf("\n\nPlease remember your casino ID!\n");
    printf("It's your only way to access the ATM and play room.\n\n");
    PrintReturnToMMMsg();
}

void AccessATM(Client_s* client)
{
    int i = 0;
    int amountConfirmed = 0;
    int validAmount = 0;
    float depositAmount = 0;
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(buf));

    system("CLS");
    //system("clear");

    printf("//************************************************\n");
    printf("//***           SUNBRUISE ATM SYSTEM           ***\n");
    printf("//************************************************\n");
    printf("//////////////////////////////////////////////////\n\n\n");

    printf("\nCurrent information:\n");
    PrintClientProfile(client, 0, 0);

    //Start the deposit process
    printf("\n\nEnter the amount you wish to deposit (0 to return to main menu): ");
    do
    {
        fgets(buf, BUF_SIZE, stdin);
        RemoveNewline(buf);

        if (ValidMoneyAmount(buf))
        {
            if (atoi(buf) == 0)
            {
                return;
            }

            depositAmount = atof(buf);
            memset(buf, 0, sizeof(buf));

            printf("\nYou requested to deposit $%.2f. Is this correct? (y/n): ", depositAmount);
            fgets(buf, 3, stdin);
            RemoveNewline(buf);

            while (tolower(*buf) != 'y' && tolower(*buf) != 'n')
            {
                printf("\nPlease make a valid selection (y - Yes, n - No): ");
                fgets(buf, 3, stdin);
                RemoveNewline(buf);
            }

            if (tolower(*buf) == 'n')
            {
                printf("\n\nEnter the amount you wish to deposit (0 to return to main menu): ");
                continue;
            }

            amountConfirmed = 1;
        }

    } while (!amountConfirmed);

    client->funds += depositAmount;

    printf("\n\n***Transaction completed successfully!***\n\n");
    printf("Your new information:\n");
    PrintClientProfile(client, 0, 0);
    printf("\n\n");
    PrintReturnToMMMsg();
}

void PlayCasino(Client_s* client)
{
    float wager = 0;
    int i = 0;
    char buf[BUF_SIZE];
    int wagerValid = 0;
    int continuePlaying = 0;
    int die1 = 0;
    int die2 = 0;
    int wheelResult = 0;
    float netResult = 0;
    memset(buf, 0, sizeof(buf));
    srand(time(NULL));

    system("CLS");
    //system("clear");

    printf("//************************************************\n");
    printf("//***       SUNBRUISE CASINO GAME ROOM         ***\n");
    printf("//************************************************\n");
    printf("//////////////////////////////////////////////////\n\n\n");

    do
    {
        printf("Roll two dice and spin the wheel.\n");
        printf("Sum of dice is equal to the wheel number and is even = WIN\n");
        printf("Sum of dice is equal to the wheel number and are both 12 = DRAW\n");
        printf("Any other result = LOSS\n");

        printf("\nCurrent Information:\n");
        PrintClientProfile(client, 0, 0);

        printf("\n\nPlease enter the amount you would like to wager (0 to return to main menu): ");
        do
        {
            wagerValid = 0;

            memset(buf, 0, sizeof(buf));
            fgets(buf, BUF_SIZE, stdin);
            RemoveNewline(buf);

            if (ValidMoneyAmount(buf))
            {
                if (atoi(buf) == 0)
                {
                    return;
                }

                wager = atof(buf);

                if (wager > client->funds)
                {
                    printf("\nYou cannot wager more than your current available funds.\n");
                    printf("Please wager a lesser amount (0 to return to main menu): ");
                    continue;
                }

                printf("\nYou are wanting to bet $%.2f, is that correct? (y/n): ", wager);
                memset(buf, 0, sizeof(buf));
                fgets(buf, 3, stdin);
                RemoveNewline(buf);

                while (tolower(*buf) != 'y' && tolower(*buf) != 'n')
                {
                    printf("\nThat is not a valid choice, please try again (y - Yes, n - No): ");
                    memset(buf, 0, sizeof(buf));
                    fgets(buf, 3, stdin);
                    RemoveNewline(buf);
                }

                if (tolower(*buf) == 'y')
                {
                    wagerValid = 1;
                }
                else
                {
                    printf("\n\nPlease enter the amount you would like to wager: ");
                    memset(buf, 0, sizeof(buf));
                    continue;
                }
            }

        } while (!wagerValid);

        client->currentWager = wager;
        die1 = (rand() % 6) + 1;
        die2 = (rand() % 6) + 1;
        wheelResult = (rand() % 11) + 2;
        netResult = ((float)(die1 + die2) / 100) * client->currentWager;

        if (die1 + die2 == wheelResult && (die1 + die2) % 2 == 0)
        {
            printf("\n\n***You win!***\n\n");
            DisplayGameResult(die1, die2, wheelResult);
            PrintClientProfile(client, 1, netResult);
            client->funds += netResult;
        }
        else if (die1 + die2 == 12 && wheelResult == 12)
        {
            printf("\n\n***It's a draw!***\n\n");
            DisplayGameResult(die1, die2, wheelResult);
            PrintClientProfile(client, 1, 0);
        }
        else
        {
            printf("\n\n***Sorry, you lose!***\n");
            DisplayGameResult(die1, die2, wheelResult);
            PrintClientProfile(client, 1, netResult * -1);
            client->funds -= netResult;
        }

        memset(buf, 0, sizeof(buf));
        printf("\n\nWould you like to play again? (y/n): ");
        fgets(buf, 3, stdin);
        RemoveNewline(buf);

        while(tolower(*buf) != 'y' && tolower(*buf) != 'n')
        {
            memset(buf, 0, sizeof(buf));
            printf("\nThat is not a valid choice, please try again (y - Yes, n - No): ");
            fgets(buf, 3, stdin);
            RemoveNewline(buf);
        }

        if (tolower(*buf) == 'y')
        {
            printf("\n\n\n");
            continuePlaying = 1;
        }
        else
        {
            continuePlaying = 0;
        }

    } while (continuePlaying);
}

int ValidMoneyAmount(char* buf)
{
    int i = 0;

    if (*buf == '$')
    {
        *buf = '0';
    }

    for (i = 0; i < strlen(buf); i++)
    {
        if (!isdigit(*(buf + i)))
        {
            if (*(buf + i) == '.' && i == strlen(buf) - 3)
            {
                continue;
            }

            else
            {
                return 0;
            }
        }
    }

    return 1;
}

int IdValidation(Client_s* clientList)
{
    char* id;
    char* email;
    int i = 0;
    int j = 0;
    int accessGranted = 0;
    char buf[BUF_SIZE];
    memset(buf, 0, sizeof(buf));

    printf("\n\nPlease input credentials to continue. (%d attempt(s) remaining)\n", ID_VALIDATE_MAX_ATTEMPTS);
    for (i = 0; i < ID_VALIDATE_MAX_ATTEMPTS; i++)
    {
        printf("Email (-1 to return to main menu): ");
        fgets(buf, BUF_SIZE, stdin);
        RemoveNewline(buf);
        email = (char*)malloc(strlen(buf) + 1);
        strcpy(email, buf);
        memset(buf, 0, sizeof(buf));

        for (j = 0; j < strlen(email); j++)
        {
            *(email + j) = toupper(*(email + j));
        }

        if (!strcmp(email, "-1"))
        {
            free(email);
            return -1;
        }

        printf("Casino ID (-1 to return to main menu): ");
        fgets(buf, BUF_SIZE, stdin);
        RemoveNewline(buf);
        id = (char*)malloc(strlen(buf) + 1);
        strcpy(id, buf);
        memset(buf, 0, sizeof(buf));

        if (atoi(id) == -1)
        {
            free(email);
            return -1;
        }

        for (j = 0; j < MAX_CLIENT_COUNT; j++)
        {
            if (!(clientList + j)->isRegistered)
            {
                continue;
            }
            else if (!strcmp((clientList + j)->email, email) &&
                     !strcmp((clientList + j)->id, id))
            {
                free(email);
                return j;
            }
        }

        if (ID_VALIDATE_MAX_ATTEMPTS - (i + 1) > 0)
        {
        printf("\n\nSorry, that record was not found. Please try again. (%d attempt(s) remaining).\n",
                ID_VALIDATE_MAX_ATTEMPTS - (i + 1));
        }
    }

    free(email);
    return -2;
}

void PrintReturnToMMMsg()
{
    printf("Press ENTER to return to the main menu.");
    getchar();
}

void Clearstdin()
{
    int i = 0;

    while ((i = getchar()) != '\n' && i != EOF);
}

void RemoveNewline(char* buf)
{
    if (strchr(buf, '\n') == NULL)
    {
        Clearstdin();
    }
    else
    {
        *strchr(buf, '\n') = '\0';
    }
}

void PrintClientProfile(Client_s* client, int viewAfterGame, float netResult)
{
            printf("-----------------------------------\n");
            printf("Name:\t\t\t%s %s\n", client->firstName, client->lastName);
            printf("Email:\t\t\t%s\n", client->email);
            printf("Casino ID:\t\t%s\n", client->id);
    if (viewAfterGame)
    {
            printf("Funds before:\t\t$%.2f\n", client->funds);
            printf("Wager:\t\t\t$%.2f\n", client->currentWager);
        if (netResult < 0)
        {
            printf("Net result:\t\t-$%.2f\n", netResult * -1);
        }
        else
        {
            printf("Net result:\t\t$%.2f\n", netResult);
        }
            printf("New funds total:\t$%.2f\n", client->funds + netResult);
    }
    else
    {
            printf("Current Funds:\t\t$%.2f\n", client->funds);
    }
            printf("-----------------------------------");
}

void NameInput(char* buf)
{
    int inputCorrect = 0;
    int i = 0;

    do
    {
        fgets(buf, BUF_SIZE, stdin);
        RemoveNewline(buf);

        if (strlen(buf) > MAX_NAME_COUNT)
        {
            printf("Name is too long, please try again.\n");
            memset(buf, 0, sizeof(buf));
            continue;
        }

        for (i = 0; i < strlen(buf); i++)
        {
            *(buf + i) = toupper(*(buf + i));

            if (!isalpha(*(buf + i)))
            {
                printf("Sorry, only letters are allowed. Please try again.\n");
                memset(buf, 0, sizeof(buf));
                break;
            }
            else if (i == strlen(buf) - 1)
            {
                inputCorrect = 1;
            }
        }

    } while (!inputCorrect);
}

int IsEmailValid(char* buf)
{
    const int MIN_DOMAIN_SIZE = 4;  //e.g. "a.tk" or "b.us"
    int inputCorrect = 0;
    int i = 0;
    char* domain;
    int  usernameSize = 0;

    domain = memchr(buf, '@', strlen(buf));
    if (!domain || strlen(domain) == strlen(buf) || strlen(domain) < MIN_DOMAIN_SIZE + 1)
    {
        return 0;
    }

    domain++;   //Move pointer up one to get rid of the @
    usernameSize = strcspn(buf, "@");

    //Check if username is valid
    for (i = 0; i < usernameSize; i++)
    {
        if (!isalnum( *(buf + i)) && !ispunct( *(buf + i)))
        {
            return 0;
        }
    }

    //Now for the domain
    for (i = 0; i < strlen(domain); i++)
    {
        if (i > strlen(domain) - 3 && !isalnum( *(domain + i)))
        {
            return 0;
        }

        else if (!isalnum( *(domain + i)) && *(domain + i) != '.' && *(domain + i) != '-')
        {
            return 0;
        }
    }

    return 1;
}

void CasinoIdInput(char* buf, Client_s* clientList)
{
    int inputCorrect = 0;
    int i = 0;
    int j = 0;

    do
    {
        fgets(buf, BUF_SIZE, stdin);
        RemoveNewline(buf);

        if (strlen(buf) != 9)
        {
            printf("ID is incorrect length, please try again: ");
            memset(buf, 0, sizeof(buf));
            continue;
        }

        for (i = 0; i < strlen(buf); i++)
        {
            if (!isdigit(*(buf + i)))
            {
                printf("Sorry, only numbers are allowed. Please try again: ");
                memset(buf, 0, sizeof(buf));
                break;
            }
            else if (i == strlen(buf) - 1)
            {
                for (j = 0; j < MAX_CLIENT_COUNT; j++)
                {
                    if ((clientList + j)->id != NULL && !strcmp((clientList + j)->id, buf))
                    {
                        printf("Sorry, that ID is already taken. Please try again: ");
                        memset(buf, 0, sizeof(buf));
                        break;
                    }
                    else if (j == MAX_CLIENT_COUNT - 1)
                    {
                        inputCorrect = 1;
                    }
                }
            }
        }

    } while (!inputCorrect);
}

void DisplayGameResult(int die1, int die2, int wheelResult)
{
    printf("Die #1:\t\t%d\n", die1);
    printf("Die #2:\t\t%d\n\n", die2);
    printf("Dice Total:\t%d\n", die1 + die2);
    printf("Wheel Spin:\t%d\n\n", wheelResult);
}
