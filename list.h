/*
 * Projekt 3 - Prosta baza danych studentow
 * Autor: Robert Dudzinski
 * Plik: list.h
 */

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
