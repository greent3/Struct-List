/*****************************************************************
//
//  NAME:        Travis Green
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        11Dec2019
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains all the methods for the llist class
//    
****************************************************************/

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "record.h"
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name:  readfile()
//
//  DESCRIPTION:   reads from a file and inputs data into a list of records
//
//  Parameters:    n/a                       
//
//  Return values:  int returnVal: -1 if file not read from, 0 if successful 
//
****************************************************************/
int llist::readfile()
    {
        ifstream inputfile;
        char garbagearray[80];
        int numHolder;
        char nameHolder[64];
        char addressHolder[102];
        int returnVal;
        returnVal = 0;
        inputfile.open(filename);

        if(inputfile.is_open() == 0)
        {
            returnVal = -1;
        }
        else
        {
            while(inputfile.peek()!=EOF)
            {
                inputfile>>numHolder;
                inputfile.getline(garbagearray,8);
                inputfile.getline(nameHolder, 25); 
                inputfile.getline(addressHolder, 80);
                addRecord(numHolder, nameHolder, addressHolder);
            }
        }

    if(returnVal != -1)
    {
        inputfile.close();
    }

    return returnVal;
}


/*****************************************************************
//
//  Function name:  writefile()
//
//  DESCRIPTION:   reads from a list of records and writes to an file
//
//  Parameters:    n/a                       
//
//  Return values:  int returnVal: -1 if file not written to, 0 if successful 
//
****************************************************************/
int llist::writefile()
{
    ofstream inputfile;
    struct record *copier;
    int returnVal;
    copier = start;
    returnVal = 0;

    inputfile.open(filename);
    if(inputfile.is_open() == 0)
    {
        returnVal = -1;
    }
    else
    {

        while(copier != NULL)
        {
            inputfile << (*copier).accountno << "\n";
            inputfile << (*copier).name << "\n";
            inputfile << (*copier).address << "\n";
            copier = (*copier).next;
        }
    }

    if(returnVal != -1)
    {
        inputfile.close();
    }

    return returnVal;
}


/*****************************************************************
//
//  Function name:  reverse(record * start)
//
//  DESCRIPTION:   reverses the order of a linked list of records
//
//  Parameters:    n/a                       
//
//  Return values:  start (record *): the beginning of the linked list 
//
****************************************************************/
record * llist::reverse(record *start)
{
    #ifdef debugMode
    cout <<"function called is: reverse() \n";
    #endif


    struct record * temp = start;
    struct record * temp2 = start;
    struct record * temp3;
    if(temp->next == NULL)
    {
        return start;
    }
    else
    {
         while(temp->next != NULL)
         {
             temp = temp->next;
         }
         while(temp2->next != temp)
         {
             temp2 = temp2->next;
         }
         temp->next = temp2;
         temp2->next = NULL;
         temp3 = reverse(start);
         start = temp;         
    }
    return start;
        
}

/*****************************************************************
//
//  Function name:  void cleanup()
//
//  DESCRIPTION:   frees all linked list memory in heap 
//
//  Parameters:    n/a                       
//
//  Return values:  n/a: function is void 
//
****************************************************************/
void llist::cleanup()
{
    struct record *temp;
    struct record *traverse;
    traverse = start;


    while(traverse != NULL)
    {
        temp = (*traverse).next;
        delete traverse;
        traverse = temp;
    }

    start = NULL;
}



/*****************************************************************
//
//  Function name:  llist()
//
//  DESCRIPTION:   constructor for linked list class 
//
//  Parameters:    n/a                       
//
//  Return values:  n/a
//
****************************************************************/
llist::llist()
{
    start = NULL;
    strcpy(filename, "accountRecords.txt");
    readfile();
}



/*****************************************************************
//
//  Function name:  llist(char[] zulu)
//
//  DESCRIPTION:   constructor for linked list class, that lets you name the written file 
//
//  Parameters:    char [] zulu: a char array to hold the name of the txt file
//
//  Return values:  n/a
//
****************************************************************/
llist::llist(char zulu[])
{
    start = NULL;
    strcpy(filename, zulu);
    readfile();
}

/*****************************************************************
//
//  Function name:  llist(llist&)
//
//  DESCRIPTION:   creates a llist using another llist (copy constructor)
//
//  Parameters:    llist& original : linked list to be copied
//                 this : llist to be written to
//
//  Return values:  n/a 
//
****************************************************************/
llist::llist(llist& original)
{
    *this=original;

}

/*****************************************************************
//
//  Function name:  llist& operator=(llist& first)
//
//  DESCRIPTION:   copies "llist" first to "llist"this
//
//  Parameters:    llist& first : linked list to be copied
//                 this : llist to be written to
//
//  Return values:  n/a 
//
****************************************************************/
llist& llist::operator=(llist& first)
{
    record * newStart = first.start;
    while(newStart != NULL)
    {
        this->addRecord(newStart->accountno, newStart->name, newStart->address);
        newStart = newStart->next;
    }

return *this;
}

/*****************************************************************
//
//  Function name:  ~llist()
//
//  DESCRIPTION:   destructor for linked list class 
//
//  Parameters:    n/a
//
//  Return values:  n/a
//
****************************************************************/
llist::~llist()
{
    writefile();
    cleanup();
}



/*****************************************************************
//
//  Function name: addRecord (int, char[], char[])
//
//  DESCRIPTION:   
//  will add a new record to the linked list with information from the user
//
//  Parameters:    int: account number 
//                 char [] : an array of characters (where the user's name stored)
//                 char[]: an array of characters (where the user's address is stored)
//
//  Return values:  0 : record added to list
//                 -1 : record not added to list
//                 
****************************************************************/
int llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    struct record *temp;
    struct record *temp2;
    struct record *back;
    int returnVal;
    int size;
    temp = start;
    back = start;
    returnVal = 0;
    size = 0; 
    
    #ifdef debugMode
        cout <<"function called is: addRecord. Account number entered is " << uaccountno << "name entered is "<< uname << "address entered is " << uaddress << "\n";
    #endif


    if(temp == NULL)
    {
        temp2 = new record;
        start = temp2;
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
            temp2 = new record;
            temp = start;
            if(uaccountno > (*temp).accountno)
            {
                (*temp2).next = temp;
                start = temp2;
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
//  Function name: printRecord (int)
//
//  DESCRIPTION:   will print the record of the account who's number is given by the user
//
//  Parameters:    int: account number 
//
//  Return values:  0 : record found and successfully printed
//                  1 : record not found
//
****************************************************************/
int llist::printRecord(int uaccountno)
{
    
    struct record *scanner;
    int returnVal;
    int endLoop;
    scanner = start;
    returnVal = -1;
    endLoop = 0;

    #ifdef debugMode
        printf("function called is: printRecord. Account number entered is %d \n", uaccountno);
    #endif
    
    if(start != NULL)
    {
        while(scanner != NULL && endLoop == 0)
        {
            if((*scanner).accountno == uaccountno)
            {
                cout << (*scanner).accountno << "\n" << (*scanner).name << "\n" << (*scanner).address << "\n";
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
        cout << "Record with that account number does not exist in the database \n";
    }
    else if((returnVal == -1) && (start == NULL))
    {
        cout << "No records exist in the database \n";
    }

    return returnVal;

}

/*****************************************************************
//
//  Function name: modifyRecord(int, char[])
//
//  DESCRIPTION:   
//  will change the address of the account who's # is given by the user
//
//  Parameters:    int: account number 
//                 Char[]: an array of characters (where the user's address is stored)
//
//  Return values:  0 : function finish running
//                 -1 : no records were modified 
//                 
****************************************************************/
int llist::modifyRecord(int uaccountno, char uaddress[])
{
    struct record *scanner;
    int returnVal;
    int endLoop;
    scanner = start;
    returnVal = -1;
    endLoop = 0;

    #ifdef debugMode
    cout << "function called is: modifyRecord. Account number entered is " << uaccountno << "addres entered is " << uaddress << "\n";
    #endif

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
        cout << "Record with that account number does not exist in the database \n";
    }
    else if((returnVal == -1) && (start == NULL))
    {
        cout << "No records exist in the database \n";
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: deleteRecord (int)
//
//  DESCRIPTION:   will delete the record who's account # is given by the user
//
//  Parameters:    int: account number 
//
//  Return values:  0 : record successfully deleted
//                  1 : no record was deleted
//                 
****************************************************************/
int llist::deleteRecord(int uaccountno)
{
    struct record *scanner;
    struct record *reLink;
    int returnVal;
    scanner = start;
    reLink = start;
    returnVal = 1;

    #ifdef debugMode
        cout << "function called is: deleteRecord. Account number entered is " << uaccountno << "\n";
    #endif

    if(scanner != NULL)
    {
        if((*scanner).next == NULL && (*scanner).accountno == uaccountno)
        {
            start = NULL;
            returnVal = 0;
        }
        else if((*scanner).next != NULL)
        {
            if((*scanner).accountno == uaccountno)
            {
                start = (*scanner).next;
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
        delete scanner;
    }

    return returnVal;
}

void llist::reverse()
{
    start = reverse(start);
}



/*****************************************************************
//
//  Function name:  void operator<<(ostream&, llist&)
//
//  DESCRIPTION:   prints out all records in the database
//
//  Parameters:    ostream: output stream
//                  llist : linked list of records
//
//  Return values:  n/a: function is void
//
****************************************************************/
void operator<<(std::ostream& os, llist& j)
{
    struct record *iterator;
    iterator = j.start;

    #ifdef debugMode
        cout<<"function called is: printAllRecords. This will print all records \n";
    #endif

    if(iterator == NULL)
    {
        cout << "The list of records is empty \n";
    }

    else
    {
        while(iterator != NULL)
        {
            cout << (*iterator).accountno << "\n" << (*iterator).name << "\n" << (*iterator).address << "\n";
            iterator = (*iterator).next;
        }
    }


}




