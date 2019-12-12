/*****************************************************************
//
//  NAME:        Travis Green
//
//  HOMEWORK:    Project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        02Nov2019
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   This file holds the prototypes for the functions used in main()
//
****************************************************************/


#include "record.h"

int addRecord (struct record **start, int, char[], char[]);
int printRecord (struct record *start, int);
void printAllRecords(struct record *);
int modifyRecord (struct record *, int, char[]);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
int writefile(struct record *, char []);
void cleanup(struct record **);
