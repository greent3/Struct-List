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
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This file contains the code for the front-end portion of project2
//    Gets and displays input to/from the user to maintain a linked list
****************************************************************/
#include <iostream>
#include <cstring>
#include "llist.h"
#include "record.h"
using namespace std;

void getAddress(char[], int);


/*****************************************************************
//
//  Function name:  int main(int argc, char* argv[])
//
//  DESCRIPTION:   interacts with the user to obtain and communicate information
//                               about the linked list of records
//
//  Parameters:    int argc: number of arguments when calling .exe
//                            char* argv[] : array of pointers to arguments 
//
//  Return values:  0: function has finished running
//
****************************************************************/
int main(int argc, char* argv[])
{
    llist myList;
    char nameHolder[64];
    char addressHolder[102];
    char nameOfFile[25];
    int debug;
    int looper = 0;
    int secondLoop = 0;
    int accHolder = 0;
    int num = 0;
    int i = 0;
    unsigned int length = 0;

    #ifdef debugMode
        debug = 1;
    #endif    

    #ifndef debugMode
        debug = 0;
    #endif

    strcpy(nameOfFile, "accountRecords.txt");
  
    cout <<"Welcome to the UserInterface \n \n";
    cout <<"please select the desired action by typing the corresponding integer \n";
    while(looper == 0)
    {
        secondLoop = 0;
        cout <<"1: Add a new record in the database \n";

        cout <<"2: Print information about a record using the account number as key \n";

        cout <<"3: Print all records in the database \n";

        cout <<"4: Modify the address field of a record using the account number as key \n";

        cout <<"5: Delete an existing record from the database using account number as key \n";

        cout <<"6: Quit the program \n";

        cout <<"7: Reverse the list of records\n";

        while(secondLoop == 0)
        {
            i = 0;
            if((cin>>num)==0)
            {
                cout <<"enter a digit between 1 and 6 \n";
            }
            else
            {
                switch(num)
                {
                case 1:
                    secondLoop = 1;
                    cout <<"please enter a new account number\n";
                    cin >>accHolder;
                    cin.ignore(1000, '\n');
        
                    cout <<"please enter the name of the account holder\n";
                    cin.getline(nameHolder, 63); 
                    while(length < sizeof(nameHolder))
                    {
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
                    myList.addRecord(accHolder, nameHolder, addressHolder);
                    break;

                case 2:
                    secondLoop = 1;
                    cout <<"please enter the number of the account you'd like to print \n";
                    cin>>accHolder;
                    myList.printRecord(accHolder);
                    break;
 
                case 3:
                    secondLoop = 1;
                    cout<<myList;
                    break;

                case 4:
                    secondLoop = 1;
                    cout <<"please enter the account number of the record you wish to modify \n ";
                    cin >>accHolder;
                    getAddress(addressHolder, 100);
                    myList.modifyRecord(accHolder, addressHolder);
                    break;

                case 5:
                    secondLoop = 1;
                    cout <<"please enter the account number of the account you wish to delete \n ";
                    cin>>accHolder;
                    myList.deleteRecord(accHolder);
                    break;

                case 6:
                    secondLoop = 1;
                    looper = 1;
                    break;

                case 7:
                    secondLoop = 1;
                    myList.reverse();
                    break;

                default:
                    cout <<"please enter a # between 1 and 6 \n";
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
    return 0;
}

/*****************************************************************
//
//  Function name:  void getAddress(char array[], int length)
//
//  DESCRIPTION:   obtains data from user to put into a char array and replace
//                               the address of a specific record
//
//  Parameters:    char array[]: array to store characters
//                            int length : amount of characters to be read
//
//  Return values:  n/a : function is void
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
    cout <<"Please type your mailing address. You may use multiple lines, \n";
    cout <<"but please signify the end of the address with the @ symbol \n";
    cout <<"For example:\nDoja Cat \n";
    cout <<"555 Drewy Lane \n";
    cout <<"Beverly Hills, CA 90210@ \n";
    while((next = cin.get()) != '@' && spot < length)
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


