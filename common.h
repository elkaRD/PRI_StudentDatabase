/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: Common.h

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FIRSTNAME_LENGTH    24
#define SECONDNAME_LENGTH   24

#define MODE_NAME           1
#define MODE_AGE            2

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct Student                      //struktura przechowujaca informacje o pojedynczym studencie
{
    char firstName[FIRSTNAME_LENGTH];
    char secondName[SECONDNAME_LENGTH];
    Date dateOfBirth;
    int indexNumber;

    struct Student* nextName;
    struct Student* nextAge;
} Student;

int CompareStrings (char* s1, char* s2);
int CompareDates (Date d1, Date d2);

void ClearInputBuffer ();
void DisplayRecord (Student* student, int it);
void DisplayHeader ();

#endif // COMMON_H
