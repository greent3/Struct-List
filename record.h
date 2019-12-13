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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the class definition for the record struct
//    
****************************************************************/


struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};
