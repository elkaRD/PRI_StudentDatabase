/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: list.c

#include "list.h"

void CreateEmptyList (Student** studentList)                                //tworzy pusta liste; poniewaz lista jest o podwojnych wiazaniach to pierwszy element nie zawiera informacji o zadnych studencie, tylko zawiera wskazniki do pierwszego elementu listy wg imienia i wg wieku
{
    *studentList = (Student*) malloc(sizeof(Student));
    (*studentList)->nextName = NULL;
    (*studentList)->nextAge = NULL;
    (*studentList)->secondName[0] = 0;                                      //zapezpieczenie dla funkcji SaveStudents() z pliku "iodata"
}

void ClearStudentList (Student** studentList)                               //czysci cala liste; uzywane przy wychodzeniu z programu
{
    Student* temp;
    while(*studentList != NULL)
    {
        temp = *studentList;
        *studentList = (*studentList)->nextName;
        free(temp);
    }
}

void InsertToNameList (Student** studentList, Student* temp, Student* optLastStudent)   //umieszcza podany adres elementu w liscie studentow wg imienia
{                                                                                       //optLastStudent to opcjonalny wzkaznik do ostatniego elementu listy; jest to uzywane podczas wczytywania studentow z plikow na poczatku dzialania programu
    Student* curStudent = (*studentList)->nextName;                                     //studentList zawiera tylko adresy do pierwszych elementow list; sam nie zawiera informacji o zadnym studencie
    Student* prevStudent = *studentList;

    if (optLastStudent != NULL)
        if (optLastStudent->nextName == NULL)
            if (CompareStrings(optLastStudent->secondName, temp->secondName))
            {
                optLastStudent->nextName = temp;                                        //jezeli nowo dodany student jest alfabetycznie za ostatnim z listy to mozna go od razu dodac na koniec bez iteracji po kazdym elemencie listy
                temp->nextName = NULL;
                return;
            }

    while(curStudent != NULL)
    {
        if (CompareStrings(curStudent->secondName, temp->secondName))
            break;

        prevStudent = curStudent;
        curStudent = curStudent->nextName;
    }

    prevStudent->nextName = temp;
    temp->nextName = curStudent;                                                        //wstaw element
}

void InsertToAgeList (Student** studentList, Student* temp)                             //umieszcza podany adres elementu w liscie studentow wg wieku
{
    Student* curStudent = (*studentList)->nextAge;
    Student* prevStudent = *studentList;

    while(curStudent != NULL)
    {
        if (CompareDates(curStudent->dateOfBirth, temp->dateOfBirth))
            break;

        prevStudent = curStudent;
        curStudent = curStudent->nextAge;
    }

    prevStudent->nextAge = temp;                                                        //wstaw element
    temp->nextAge = curStudent;
}

Student* AddStudentToList (Student** studentList, Student student, Student* optLastStudent)  //dodaje podany obiekt typu Student do listy
{                                                                                            //optLastStudent to opcjonalny wzkaznik do ostatniego elementu listy; jest to uzywane podczas wczytywania studentow z plikow na poczatku dzialania programu
    Student* temp = (Student*) malloc(sizeof(Student));
    *temp = student;

    if ((*studentList)->nextName == NULL)                                               //gdy lista jest pusta
    {
        temp->nextName = NULL;
        temp->nextAge = NULL;
        (*studentList)->nextName = temp;
        (*studentList)->nextAge = temp;
    }
    else
    {
        InsertToNameList(studentList, temp, optLastStudent);
        InsertToAgeList(studentList, temp);
    }

    return temp;
}

void RemoveFromList (Student** studentList, int number, int mode)       //usuwa element o numerze number (zaczynajac liczyc od 1), numer jest liczony na liscie wg imienia lub wieku w zaleznosci od wartosci argumentu mode
{
    char whichFile = 0;

    int i = 0;
    Student* curStudent = *studentList;
    Student* prevStudent = NULL;

    while (1)                                                           //petla wyszukuje podanego studenta na liscie wg podanego trybu (po imieniu / po wieku)
    {
        if (i == number)                                                //w tym momencie wzkaznik curStudent zawiera w sobie adres elementu do usuniecia
        {
            DisplayHeader();
            printf("    Are you sure you want to remove this record:\n\n\n");    //potwierdzenie usuniecia konkretnego studenta z bazy
            DisplayRecord(curStudent, 0);
            printf("\n\n[1-YES / 0-NO]: ");

            int menu;
            if (scanf("%d", &menu) != 1)
            {
                ClearInputBuffer();
                return;
            }
            if (menu == 0) return;                                      //zrezygnowanie z usuniecia danego studenta

            whichFile = curStudent->secondName[0];                      //znajdz plik,z ktorego usunac studenta

            if (mode == MODE_NAME)
                prevStudent->nextName = curStudent->nextName;           //usun dany element z wiazania
            else
                prevStudent->nextAge = curStudent->nextAge;
            break;
        }

        prevStudent = curStudent;

        if (mode == MODE_NAME)
            curStudent = curStudent->nextName;
        else
            curStudent = curStudent->nextAge;
        i++;
    }

    Student* studentToDelete = curStudent;
    curStudent = *studentList;
    prevStudent = NULL;

    while (1)                                                           //wiedzac, ktory element jest do usuniecia i usunieciu wiazania z jednej listy, trzeba jeszcze usunac wiazanie z drugiej listy
    {
        if (curStudent == studentToDelete)                              //znajdz usuwany element
        {
            if (mode == MODE_AGE)
                prevStudent->nextName = curStudent->nextName;           //usun wiazania z tym elementem z drugiej listy
            else
                prevStudent->nextAge = curStudent->nextAge;
            break;
        }

        prevStudent = curStudent;

        if (mode == MODE_AGE)
            curStudent = curStudent->nextName;
        else
            curStudent = curStudent->nextAge;
    }

    free(curStudent);                                                   //po usunieciu wiazan z obu list, mozna dany element zwolnic ostatecznie z pamieci

    if (whichFile)
    {
        SaveStudents(*studentList, DATA_FILES_LOCATION, whichFile);     //zapisz zmiany: zapisuje tylko jeden plik, w ktorym byla zmiana (plik przechowujacy studentow o nazwiskach zaczynajaych sie ta sama litera)
    }

    puts("\n  Removed");
    sleep(2);                                                           //komunikat o powodzeniu usuwania
}
