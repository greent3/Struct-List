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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file holds the struct named record
//
****************************************************************/


struct record
{
    int accountno;
    char name[25];
    char address[80];
    struct record* next;
};
