/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: list.h

#ifndef LIST_H
#define LIST_H

#include "common.h"
#include "iodata.h"

void CreateEmptyList (Student** studentList);
void ClearStudentList (Student** studentList);
void InsertToNameList (Student** studentList, Student* temp, Student* optLastStudent);
void InsertToAgeList (Student** studentList, Student* temp);
Student* AddStudentToList (Student** studentList, Student student, Student* optLastStudent);
void RemoveFromList (Student** studentList, int number, int mode);

#endif // LIST_H
