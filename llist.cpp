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
//  DATE:        03Nov2019
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   This file holds the functions called in main
//
****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

extern int debugMode;
/*****************************************************************
//
//  Function name: addRecord (struct record**, int, char[], char[])
//
//  DESCRIPTION:   
//  Intended use: will add a new record to the linked list with information from the user
//
//  Parameters:    struct record**: a pointer to record pointer
//                 int: account number 
//                 char [] : an array of characters (where the user's name stored)
//                 char[]: an array of characters (where the user's address is stored)
//
//  Return values:  0 : record added to list
//                 -1 : record not added to list
//                 
****************************************************************/

int addRecord(struct record **start, int uaccountno, char uname[], char uaddress[])
{
    struct record *temp;
    struct record *temp2;
    struct record *back;
    int returnVal;
    int size;
    temp = *start;
    back = *start;
    returnVal = 0;
    size = 0; 
    
    if(debugMode == 1)
    {
        printf("function called is: addRecord. Account number entered is %d, name entered is %s, address entered is %s \n", uaccountno, uname, uaddress);
    }


    if(temp == NULL)
    {
        temp2 = malloc(1 * sizeof(struct record));
        *start = temp2;
        (*temp2).next = NULL;
    }

    else
    {
        while(temp !=  NULL)
        {
            if((*temp).accountno == uaccountno)
            {
                returnVal = -1;
            }
            temp = (*temp).next;
            size = size + 1;
        }
        if(returnVal == 0)
        {
            temp2 = malloc(1 * sizeof(struct record));
            temp = *start;
            if(uaccountno > (*temp).accountno)
            {
                (*temp2).next = temp;
                *start = temp2;
            }
            else if(uaccountno < (*temp).accountno && size == 1)
            {
                (*temp).next = temp2;
                (*temp2).next = NULL;
            }
            
            else
            {
                temp = (*temp).next;
                while(uaccountno < (*temp).accountno && (*temp).next != NULL)
                {
                    if((*back).accountno > uaccountno && (*temp).accountno < uaccountno)
                    {
                        (*temp2).next = temp;
                        (*back).next = temp2;
                    }
                    temp = (*temp).next;
                    back = (*back).next;
                }
                if((*back).accountno > uaccountno && (*temp).accountno < uaccountno)
                {
                    (*temp2).next = temp;
                    (*back).next = temp2;
                }
                else if(uaccountno < (*temp).accountno)
                {
                    (*temp).next = temp2;
                    (*temp2).next = NULL;
                }
         
            }
        }
    }
    if(returnVal ==  0)
    {
        (*temp2).accountno = uaccountno;
        strcpy((*temp2).name, uname);
        strcpy((*temp2).address, uaddress);
    }

return returnVal;

}

/*****************************************************************
//
//  Function name: printRecord (struct record*, int)
//
//  DESCRIPTION:   will print the record of the account who's number is given by the user
//
//  Parameters:    struct record*: a pointer to a (struct) record
//                 int: account number 
//
//  Return values:  0 : record found and successfully printed
//                  1 : record not found
//
****************************************************************/

int printRecord(struct record *start, int uaccountno)
{
    
    struct record *scanner;
    int returnVal;
    int endLoop;
    scanner = start;
    returnVal = -1;
    endLoop = 0;

    if(debugMode == 1)
    {
        printf("function called is: printRecord. Account number entered is %d \n", uaccountno);
    }
    
    if(start != NULL)
    {
        while(scanner != NULL && endLoop == 0)
        {
            if((*scanner).accountno == uaccountno)
            {
                printf("%d\n%s\n%s\n", (*scanner).accountno, (*scanner).name, (*scanner).address);
                endLoop = 1;
                returnVal = 0;
            }
            if(endLoop != 1)
            {
                scanner = (*scanner).next;
            }
        }
    }
    if ((returnVal == -1) && (start != NULL))
    {
        printf("Record with that account number does not exist in the database \n");
    }
    else if((returnVal == -1) && (start == NULL))
    {
        printf("No records exist in the database \n");
    }

    return returnVal;

}

/*****************************************************************
//
//  Function name: printAllRecords (struct record*)
//
//  DESCRIPTION: Will print out all records in the list or notify
//  the user that the list of records is empty
//
//  Parameters:    struct record *start: a pointer to struct record
//
//  Return values:   n/a
//
****************************************************************/

void printAllRecords(struct record *start)
{
    
    struct record *iterator;
    iterator = start;

    if(debugMode == 1)
    {
        printf("function called is: printAllRecords. This will print all records \n");
    }

    if(iterator == NULL)
    {
        printf("The list of records is empty \n");
    }

    else
    {
        while(iterator != NULL)
        {
            printf("%d\n%s\n%s\n", (*iterator).accountno, (*iterator).name, (*iterator).address);
            iterator = (*iterator).next;
        }
    }

}

/*****************************************************************
//
//  Function name: modifyRecord (struct record*, int, char[])
//
//  DESCRIPTION:   
//  Intended use: will change the address of the account who's # is given by the user
//
//  Parameters:    struct record*: a pointer to a struct of type record
//                 int: account number 
//                 Char[]: an array of characters (where the user's address is stored)
//
//  Return values:  0 : function finish running
//                 -1 : no records were modified 
//                 
****************************************************************/


int modifyRecord(struct record *start, int uaccountno, char uaddress[])
{
    struct record *scanner;
    int returnVal;
    int endLoop;
    scanner = start;
    returnVal = -1;
    endLoop = 0;

    if(debugMode == 1)
    {
    printf("function called is: modifyRecord. Account number entered is %d, addres entered is %s \n", uaccountno, uaddress);
    }

    if(start != NULL)
    {
        while(scanner != NULL && endLoop == 0)
        {
            if((*scanner).accountno == uaccountno)
            {
                strcpy((*scanner).address, uaddress);
                endLoop = 1;
                returnVal = 0;
            }
            if(endLoop != 1)
            {
                scanner = (*scanner).next;
            }
        }
    }

    if((returnVal == -1) && (start != NULL))
    {
        printf("Record with that account number does not exist in the database \n");
    }
    else if((returnVal == -1) && (start == NULL))
    {
        printf("No records exist in the database \n");
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: deleteRecord (struct record**, int)
//
//  DESCRIPTION:   will delete the record who's account # is given by the user
//
//  Parameters:    struct record**: a pointer to a pointer to struct of type record
//                 int: account number 
//
//  Return values:  0 : record successfully deleted
//                  1 : no record was deleted
//                 
****************************************************************/


int deleteRecord(struct record **start, int uaccountno)
{
    struct record *scanner;
    struct record *reLink;
    int returnVal;
    scanner = *start;
    reLink = *start;
    returnVal = 1;

    if(debugMode == 1)
    {
        printf("function called is: deleteRecord. Account number entered is %d \n", uaccountno);
    }

    if(scanner != NULL)
    {
        if((*scanner).next == NULL && (*scanner).accountno == uaccountno)
        {
            *start = NULL;
            returnVal = 0;
        }
        else if((*scanner).next != NULL)
        {
            if((*scanner).accountno == uaccountno)
            {
                *start = (*scanner).next;
                returnVal = 0;
            }
            else
            {
                scanner = (*scanner).next;
                while((*scanner).next != NULL && (*scanner).accountno != uaccountno)
                {
                    scanner = (*scanner).next;
                    reLink = (*reLink).next;
                }

                if((*scanner).next == NULL && (*scanner).accountno == uaccountno)
                {
                    (*reLink).next = NULL;
                    returnVal = 0;
                }

                else if ((*scanner).next != NULL && (*scanner).accountno == uaccountno)
                {
                    (*reLink).next = (*scanner).next;
                    returnVal = 0;
                }
            }
        }   
    }
    if(returnVal == 0)
    {
        free(scanner);
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: int readfile()
//
//  DESCRIPTION:  This function reads from a textfile and writes the contents
//   of the text file into a list of struct records
//
//  Parameters: struct record **start: pointer to struct record pointer holding address of first record
//              filename(char[]): holds the name of the file to be read from
//
//  Return values:  0 : success
//                 -1 : the text file is invalid, therefore no records were written into
//
****************************************************************/

int readfile(struct record **start, char filename[])
{
    FILE *inputfile;
    char garbagearray[80];
    int numHolder;
    char nameHolder[64];
    char addressHolder[102];
    int returnVal;
    int looper;
    looper = 0;
    returnVal = 0;
    inputfile = fopen(filename,"r");

    if(inputfile == NULL)
    {
        returnVal = -1;
    }
    else
    {
        while(feof(inputfile) != 1)
        {
                fscanf(inputfile, "%d", &numHolder);
                fgets(garbagearray, 20, inputfile); 
                fgets(nameHolder, 25, inputfile);
                looper = 0;
                while(looper < 25)
                {
                    if(nameHolder[looper] == '\n')
                    {
                        nameHolder[looper] = '\0';
                    }
                    looper += 1;
                }
                looper = 0;
                fgets(addressHolder, 80, inputfile);
                while(looper < 80)
                {
                    if(addressHolder[looper] == '\n')
                    {
                        addressHolder[looper] = '\0';
                    }
                    looper += 1;
                }
                looper = 0;
                addRecord(start, numHolder, nameHolder, addressHolder);
         }
    }

    if(returnVal != -1)
    {
        fclose(inputfile);
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: int writefile()
//
//  DESCRIPTION:  This function reads from a list of records and 
//   writes the contents of the records into a text file
//
//  Parameters:  struct record *start: a record pointer that holds the value of the first record
//               filename(char[]): holds the name of the file to be written into
//
//  Return values:  0 : success
//                 -1 : the text file is invalid, therefore no records were written to the file
//
****************************************************************/

int writefile(struct record *start, char filename[])
{
    FILE *inputfile;
    struct record *copier;
    int returnVal;
    copier = start;
    returnVal = 0;

    inputfile = fopen(filename,"w");
    if(inputfile == NULL)
    {
        returnVal = -1;
    }
    else
    {

        while(copier != NULL)
        {
            fprintf(inputfile, "%d\n", (*copier).accountno);
            fprintf(inputfile, "%s\n", (*copier).name);
            fprintf(inputfile, "%s\n", (*copier).address);
            copier = (*copier).next;
        }
    }

    if(returnVal != -1)
    {
        fclose(inputfile);
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: void cleanup()
//
//  DESCRIPTION:  This function releases all allocated spaces in the heap memory
//  and assigns the value of NULL to start
//
//  Parameters: &start : pointer to a struct record pointer
//
//  Return values: n/a
//
****************************************************************/
 
void cleanup(struct record **start)
{
    struct record *temp;
    struct record *traverse;
    traverse = *start;


    while(traverse != NULL)
    {
        temp = (*traverse).next;
        free(traverse);
        traverse = temp;
    }

    *start = NULL;
}
