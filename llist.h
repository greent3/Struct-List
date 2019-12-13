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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file contains the class definition for the llist class
//    
****************************************************************/

#include <iostream>

class llist
{
private:
    struct record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    record *    reverse(record * );
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    llist(llist&);
    friend void operator<<(std::ostream&, llist&);
    llist& operator=(llist&);
    int addRecord(int, char [ ],char [ ]);
    int printRecord(int);
    void printAllRecords();
    int modifyRecord(int, char [ ]);
    int deleteRecord(int);
    void reverse();
    };
