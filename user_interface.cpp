/*****************************************************************
//
//  NAME:        Travis Green
//
//  HOMEWORK:    Homework3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        28Sept2019
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file is used to communicate the user's desires to the
//   program and call the appropriate function to perform
//    the appropriate actions
//
****************************************************************/


#include <stdio.h>
#include <string.h>
#include "database.h"

void getAddress(char[] , int);

int debugMode;

/*****************************************************************
//
//  Function name: Main()
//
//  DESCRIPTION:   This function calls all appropriate functions
//                 and is responsible for the activation debug mode
//
//  Parameters:    argc : # of arrays used to call the program
//                 argv: arrays of characters used to call the program
//
//  Return values:  0 : success
//                 
//
****************************************************************/

int main(int argc, char* argv[])
{
    char userInput[64];
    char nameHolder[64];
    char addressHolder[102];
    char trashArray[100];
    char nameOfFile[25];
    int looper = 0;
    int skipOver = 0;
    int secondLoop = 0;
    int accHolder = 0;
    int num = 0;
    int i = 0;
    int length = 0;
    struct record *start = NULL;
    debugMode = 0;

    if(argc > 1)
    {
        if((strcmp("debug", argv[1]) == 0))
        {
            debugMode = 1;
        }
        else
        {
            skipOver = 1;
            printf("%s: missing file operand Try '%s --help' for more information. \n", argv[1], argv[1]);
        }
    }


    if(skipOver != 1)
  {
    strcpy(nameOfFile, "accountRecords.txt");
    readfile(&start, nameOfFile);
  
    printf("Welcome to the UserInterface \n \n");
    printf("please select the desired action by typing the corresponding integer \n");
    while(looper == 0)
    {
        secondLoop = 0;
        printf("1: Add a new record in the database \n");

        printf("2: Print information about a record using the account number as key \n");

        printf("3: Print all records in the database \n");

        printf("4: Modify the address field of a record using the account number as key \n");

        printf("5: Delete an existing record from the database using account number as key \n");

        printf("6: Quit the program \n");

        fgets(userInput, 1, stdin);
        while(secondLoop == 0)
        {
            length = 0;
            i = 0;
            if(strlen(userInput) > 1)
            {
                printf("enter a digit between 1 and 6 \n");
                fgets(userInput, 1, stdin);
            }
            else
            {
                scanf("%d", &num);
                fgets(trashArray, 10, stdin); 
                switch(num)
                {
                case 1:
                    secondLoop = 1;
                    printf("please enter a new account number\n");
                    fgets(userInput, 63, stdin); 
                    sscanf(userInput, "%d", &accHolder);
        
                    printf("please enter the name of the account holder\n");
                    fgets(nameHolder, 63, stdin); 
                    while(length < sizeof(nameHolder))
                    {
                        if(nameHolder[length] == '\n')
                        {
                            nameHolder[length] = ' ';
                        }
                        if(nameHolder[length] > 90 || nameHolder[length] < 65 )
                        {
                            if((nameHolder[length] > 122 || nameHolder[length] < 97) && nameHolder[length] != 32 && nameHolder[length] != 46 && nameHolder[length] != 0)
                            {
                                nameHolder[length] = ' ';
                            }
                        }
                        length++;
                    }
                    getAddress(addressHolder, 100);
                    addRecord(&start, accHolder, nameHolder, addressHolder);
                    break;

                case 2:
                    secondLoop = 1;
                    printf("please enter the number of the account you'd like to print \n");
                    fgets(userInput, 63, stdin);
                    sscanf(userInput, "%d", &accHolder);
                    printRecord(start, accHolder);
                    break;
 
                case 3:
                    secondLoop = 1;
                    printAllRecords(start);
                    break;

                case 4:
                    secondLoop = 1;
                    printf("please enter the account number of the account you wish to modify \n ");
                    fgets(userInput, 63, stdin);
                    sscanf(userInput, "%d", &accHolder);
                    getAddress(addressHolder, 100);
                    modifyRecord(start, accHolder, addressHolder);
                    break;

                case 5:
                    secondLoop = 1;
                    printf("please enter the account number of the account you wish to delete \n ");
                    fgets(userInput, 63, stdin);
                    sscanf(userInput, "%d", &accHolder);
                    deleteRecord(&start, accHolder);
                    break;

                case 6:
                    secondLoop = 1;
                    looper = 1;
                    break;

                default:
                    printf("please enter a # between 1 and 6 \n");
                    break;
                   
                    i = 0; 
                    while(i < 100)
                    {
                        addressHolder[i] = 0;
                        i++;
                    }
                }

            }
        }
    }
    
    writefile(start, nameOfFile);
  }
    cleanup(&start);
    return 0;
}

/*****************************************************************
//
//  Function name: getAddress(char[], int)
//
//  DESCRIPTION:   This function gives the user instructions to enter their address
//                 and ensures the input is stored in one array
//
//  Parameters:    char array[] : an array of characters (where the address will be stored)
//                 int length: the max amount of address characters allowed
//
//  Return values:  n/a                
//
****************************************************************/


void getAddress(char array[], int length)
{
    char next;
    int spot = 0;

    while(spot < length)
    {
        array[spot] = 0;
        spot++;
    }
    spot = 0;
    printf("Please type your mailing address. You may use multiple lines, \n");
    printf("but please signify the end of the address with the @ symbol \n");
    printf("For example:\nDoja Cat \n");
    printf("555 Drewy Lane \n");
    printf("Beverly Hills, CA 90210@ \n");
    while((next = getchar()) != '@' && spot < length)
    {
        if(next == '\n')
        {
            next = ' ';
        }
        array[spot] = next;
        spot++;
    }
    spot++;
    array[spot] = '\0';
} 
