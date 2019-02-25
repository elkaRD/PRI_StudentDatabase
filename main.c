/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: main.c

#include "common.h"                                                             //zawiera uzywane struktury
#include "iodata.h"                                                             //zawiera funkcje do zapisu i odczytu danych z plikow

int DisplayOptions (Student** studentList, int numberOfStudents, int mode)      //wyswietla czynnosci mozliwe do zrobienia z lista
{                                                                               //mode to tryb listy (wg imienia lub wg wieku)
    printf("\n 0 - back, 1 - remove student\n");
    int menu;

    while (1)
    {
        if (scanf("%d", &menu) != 1)
        {
            ClearInputBuffer();
            continue;
        }

        if (menu == 0) break;                                                   //zakoncz petle opcji; wroc do petli listy, a nastepnie do petli glownej
        if (menu == 1)
        {
            printf("\nEnter record number from list to be removed: ");
            int number;
            if (scanf("%d", &number) != 1)
            {
                ClearInputBuffer();
                break;
            }

            if (number > 0 && number <= numberOfStudents)                       //sprawdz czy rekord o takim numerze istnieje
            {
                RemoveFromList(studentList, number, mode);                      //usun rekord, ktory mial liczbe porzadkowa rowna number na liscie wg mode
            }
            break;
        }
    }
    return menu;                                                                //funkcja zwraca ktora opcja zostala wybrana
}

int DisplayByName (Student* studentList)                                        //wyswietlanie listy wg imienia
{
    DisplayHeader();
    puts("      List of students by name:\n");
    printf("  No. %-24s %-24s %-10s  %-6s\n\n", "Second Name", "First Name", "Birth", "Index");

    int i = 0;
    if (studentList->nextName == NULL)
    {
        printf("\n    No students in the database\n\n");
    }
    else
    {
        studentList = studentList->nextName;

        while(studentList != NULL)
        {
            i++;
            DisplayRecord(studentList, i);
            studentList = studentList->nextName;
        }
    }
    return i;
}

int DisplayByAge (Student* studentList)                                         //wyswietlanie listy wg wieku
{
    DisplayHeader();
    puts("      List of students by age:\n");
    printf("  No. %-24s %-24s %-10s  %-6s\n\n", "Second Name", "First Name", "Birth", "Index");

    int i = 0;
    if (studentList->nextName == NULL)
    {
        printf("\n    No students in the database\n\n");
    }
    else
    {
        studentList = studentList->nextAge;

        while(studentList != NULL)
        {
            i++;
            DisplayRecord(studentList, i);
            studentList = studentList->nextAge;
        }
    }
    return i;
}

int CheckName (const char* s)                                               //sprawdza czy podane imie lub nazwisko skladaja sie tylko z liter
{
    unsigned int i;
    for (i = 0; i < strlen(s); i++)
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))) return 0;

    return 1;
}

int LeapYear (int y)                                                        //sprawdza czy rok jest przestepny; potrzebne przy sprawdzaniu poprawnosci wprowadzonej daty
{
    if (y % 4) return 0;
    else if (y % 100) return 1;
    else if (y % 400) return 0;
    else return 1;
}

int CheckDate (Date d)                                                      //sprwadza poprawnosc wprowadzonej daty
{
    if (d.month < 1 || d.month > 12) return 0;
    if (d.year < 1800 || d.year > 9999) return 0;
    if (d.day < 1) return 0;

    switch (d.month)                                                        //warunek sprawdza czy podano prawidlowy dzien miesiaca; uwzglednia rozna liczbe dni w zaleznosci od miesiaca
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (d.day > 31) return 0;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        if (d.day > 30) return 0;
        break;

    case 2:
        if (LeapYear(d.year))
        {
            if (d.day > 29) return 0;
        }
        else if (d.day > 28) return 0;
        break;
    }

    return 1;
}

int CheckIndexNumber (Student* studentList, int n)                          //sprawdza czy przypadkiem nie isrnieje juz student o takim samym indeksie
{
    studentList = studentList->nextName;

    while (studentList != NULL)
    {
        if (studentList->indexNumber == n) return 0;
        studentList = studentList->nextName;
    }
    return 1;
}

void AddStudent (Student** studentList)                                     //funkcja zbierajaca i sprawdzajaca informacje do utworzenia nowego studenta
{
    DisplayHeader();
    printf("      Adding a new student\n\n\n");

    Student student;

    printf("Enter first name: ");
    if (scanf("%s", student.firstName) != 1 || !CheckName(student.firstName))
    {
        puts("\n  Incorrect first name");
        sleep(3);                                                           //trzy sekundowy komunikat o niepowodzeniu
        return;
    }
    printf("Enter second name: ");
    if (scanf("%s", student.secondName) != 1 || !CheckName(student.secondName))
    {
        puts("\n  Incorrect second name");
        sleep(3);
        return;
    }
    puts("Enter date of birth");
    printf("Dzien: ");
    if (scanf("%d", &student.dateOfBirth.day) != 1)
    {
        puts("\n  Failed to read the day");
        sleep(3);
        return ;
    }
    printf("Miesiac: ");
    if (scanf("%d", &student.dateOfBirth.month) != 1)
    {
        puts("\n  Failed to read a month");
        sleep(3);
        return;
    }
    printf("Rok: ");
    if (scanf("%d", &student.dateOfBirth.year) != 1)
    {
        puts("\n  Failed to read the year");
        sleep(3);
        return;
    }
    if (!CheckDate(student.dateOfBirth))
    {
        puts("\n  Incorrect date of birth");
        sleep(3);
        return;
    }
    printf("Enter index number: ");
    if (scanf("%d", &student.indexNumber) != 1 || student.indexNumber < 0)
    {
        puts("\n  Failed to read the index number");
        sleep(3);
        return;
    }
    if (!CheckIndexNumber(*studentList, student.indexNumber))
    {
        puts("\n  Entered index already exists in the database");
        sleep(4);
        return;
    }

    AddStudentToList(studentList, student, NULL);                             //dodaj studenta do listy

    SaveStudent(&student, DATA_FILES_LOCATION);                         //zapisz nowego studenta do pliku

    puts("\n  Added");
    sleep(2);                                                           //krotki komunikat o pomyslnosci dodania nowego rekordu
}

void DisplayMenu ()                                                     //po prostu wyswietla glowne menu programu
{
    DisplayHeader();

    puts("      What would you like to do?:\n");
    puts(" 1. Display list by name");
    puts(" 2. Display list by age");
    puts(" 3. Add a new student");
    puts(" 0. Exit");
}

void ListByName (Student** studentList)                                         //wyswietla ekran odpowiedzialny za liste wg imienia
{
    while (1)
    {
        int numberOfStudents = DisplayByName(*studentList);                     //wyswietl liste
        if (!DisplayOptions(studentList, numberOfStudents, MODE_NAME)) break;   //wyswietla mozliwe operacje do wykonanania i je obsluguje
    }
}

void ListByAge (Student** studentList)                                          //wyswietla ekran odpowiedzialny za liste wg wieku
{
    while (1)
    {
        int numberOfStudents = DisplayByAge(*studentList);
        if (!DisplayOptions(studentList, numberOfStudents, MODE_AGE)) break;
    }
}

int main ()
{
    Student* studentList;

    CreateEmptyList(&studentList);
    if (LoadStudents(&studentList, DATA_FILES_LOCATION) < 0)
    {
        DisplayHeader();
        puts("  File mapping.txt does not contain valid paths to files");
        puts("  or does not contain paths to all 26 files");
    }
    else while (1)                                                                   //glowna petla programu
    {
        DisplayMenu();
        int menu;
        if (scanf("%d", &menu) != 1)
        {
            ClearInputBuffer();
            continue;
        }

        switch (menu)
        {
        case 1:
            ListByName(&studentList);                                           //wyswietl liste po imieniu
            break;

        case 2:
            ListByAge(&studentList);                                            //wyswietl liste po wieku
            break;

        case 3:
            AddStudent(&studentList);                                           //dodaj nowego studenta do bazy
            ClearInputBuffer();
            break;

        case 0:
            ClearStudentList(&studentList);                                     //zakoncz dzialanie programu, ale najpierw usun dane z pamieci
            exit(0);
        }
    }

    return 0;
}
