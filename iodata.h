/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: iodata.h

#ifndef IODATA_H
#define IODATA_H

#include "common.h"
#include "list.h"

#define DATA_FILES_LOCATION "mapping.txt"

void SaveStudent (Student* student, const char* fileName);
void SaveStudents (Student* studentList, const char* fileName, char  whichDataFile);
int LoadStudents (Student** studentList, const char* fileName);

#endif // IODATA_H
