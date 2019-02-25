/*
 * Projekt 3 - Prosta baza danych studentow
 * Autor: Robert Dudzinski
 * Plik: iodata.h
 */

#ifndef IODATA_H
#define IODATA_H

#include "common.h"
#include "list.h"

#define DATA_FILES_LOCATION "mapowanie.txt"

void SaveStudent (Student* student, const char* fileName);
void SaveStudents (Student* studentList, const char* fileName, char  whichDataFile);
int LoadStudents (Student** studentList, const char* fileName);

#endif // IODATA_H
