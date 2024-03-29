/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: Common.c

#include "common.h"

int CompareStrings (char* s1, char* s2)         //porownuje dwa ciagu znakow i stwierdza, ktory jest pierwszy alfabetycznie; nie uwzglednia wielkosci liter
{
    return strcasecmp(s1, s2) < 0 ? 0 : 1;
}

int CompareDates (Date d1, Date d2)             //porownuje dwie daty wzgledem chronologicznosci
{
    if (d1.year < d2.year)
        return 0;

    if (d1.year == d2.year)
    {
        if (d1.month < d2.month)
            return 0;

        if (d1.month == d2.month)
            if (d1.day < d2.day)
                return 0;
    }
    return 1;
}

void ClearInputBuffer ()                                                        //usuwa znaki z buforu wejscia; uzywane gdy uzytkownik wprowadzi dane w zlej formie
{
    while (getchar() != '\n');
}

void DisplayRecord (Student* student, int it)                                   //funkcja wyswietla informacje o pojedynczym studencie
{                                                                               //it to numer na liscie do wyswietlenia
    if (it != 0)                                                                //jezeli it jest rowny 0 to numer nie jest wyswietlany
        printf(" %3d.", it);

    printf(" %-24s %-24s %02d-%02d-%4d  %6d\n", student->secondName, student->firstName, student->dateOfBirth.day, student->dateOfBirth.month, student->dateOfBirth.year, student->indexNumber);
}

void DisplayHeader ()                                                           //wyswietla naglowek programu na kazdym ekranie aplikacji
{
    system("clear");

    puts("  3rd project for Fundamentals of Programming lectures");
    puts("  Simple Student Database");
    puts("  Warsaw University of Technology");
    puts("  Copyright (C) Robert Dudzinski 2017\n");
}
