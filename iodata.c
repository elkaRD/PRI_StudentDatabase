/// EN: 3rd project for Fundamentals of Programming lectures at Warsaw University of Technology
///     Simple Student Database
///
/// PL: Trzeci projekt PRI (Podstawy Programowania) PW WEiTI 17Z
///     Prosta baza danych studentow
///
///     Copyright (C) Robert Dudzinski 2017
///     Warsaw, December 2017
///
///     File: iodata.c

#include "iodata.h"

void SaveStudent (Student* student, const char* fileName)                   //dopisuje pojedynczego studenta do odpowiedniego pliku
{
    char whichDataFile = student->secondName[0];                            //sprawdz do ktorego pliku dodac nowego studenta
    if (whichDataFile >= 'a' && whichDataFile <= 'z')
        whichDataFile -= 32;

    FILE* filesLoc = fopen(fileName, "r");                                  //otworz plik z mapowaniem do innych plikow

    int i;
    for (i = 0; i < 26; i++)
    {
        char fileDataName[256];
        fscanf(filesLoc, "%s", fileDataName);

        if (i == whichDataFile - 'A')                                       //znajdz odpowiedni plik
        {
            fclose(filesLoc);
            FILE* dataFile = fopen(fileDataName, "ab");                     //otworz plik z trybem binarnym do dopisywania danych na koncu pliku

            char day = student->dateOfBirth.day;                            //zmienne od daty maja maly zakres wartosci, wiec zapisujac je do pliku mozna je zapisac jako zmienne typu, ktore zajmuja mniej miejsca
            char month = student->dateOfBirth.month;                        //taki zapis zmniejsza o 8 bajtow wielkosc jednego rekordu
            short year = student->dateOfBirth.year;

            fwrite(student->firstName, sizeof(char), FIRSTNAME_LENGTH, dataFile);
            fwrite(student->secondName, sizeof(char), SECONDNAME_LENGTH, dataFile);
            fwrite(&day, sizeof(char), 1, dataFile);
            fwrite(&month, sizeof(char), 1, dataFile);
            fwrite(&year, sizeof(short), 1, dataFile);
            fwrite(&student->indexNumber, sizeof(int), 1, dataFile);

            fclose(dataFile);
            break;
        }
    }
}

void SaveStudents (Student* studentList, const char* fileName, char  whichDataFile) //funkcja zapisuje od nowa wszystkich studentow o danej literze nazwiska
{                                                                                   //funkcja wykorzystywana, gdy usuwa sie studenta z bazy
    if (whichDataFile >= 'a' && whichDataFile <= 'z')
        whichDataFile -= 32;

    FILE* filesLoc = fopen(fileName, "r");

    int i;
    for (i = 0; i < 26; i++)
    {
        char fileDataName[256];
        fscanf(filesLoc, "%s", fileDataName);

        if (i == whichDataFile - 'A')
        {
            fclose(filesLoc);

            while (studentList != NULL)                                             //petla znajduje pierwszego studenta o nazwisku zaczynajacym sie dana litera
            {
                if (studentList->secondName[0] == whichDataFile || studentList->secondName[0] == whichDataFile + 32) break;

                studentList = studentList->nextName;
            }

            FILE* dataFile = fopen(fileDataName, "wb");                             //plik binarny z czyszczona zawartoscia w chwili otwarcia

            while (studentList != NULL)
            {
                if (studentList->secondName[0] != whichDataFile && studentList->secondName[0] != whichDataFile + 32) break; //skonczyli sie studenci o nazwisku na dana litere, wiec przestan zapisywac w petli

                char day = studentList->dateOfBirth.day;                            //to samo co w funkcji SaveStudent() -> oszczedzanie pamieci
                char month = studentList->dateOfBirth.month;
                short year = studentList->dateOfBirth.year;

                fwrite(studentList->firstName, sizeof(char), FIRSTNAME_LENGTH, dataFile);
                fwrite(studentList->secondName, sizeof(char), SECONDNAME_LENGTH, dataFile);
                fwrite(&day, sizeof(char), 1, dataFile);
                fwrite(&month, sizeof(char), 1, dataFile);
                fwrite(&year, sizeof(short), 1, dataFile);
                fwrite(&studentList->indexNumber, sizeof(int), 1, dataFile);

                studentList = studentList->nextName;
            }

            fclose(dataFile);
            break;
        }
    }
}

int LoadStudents (Student** studentList, const char* fileName)                              //wczytuje wszystkich studentow z plikow do pamieci
{
    int numberOfStudents = 0;
    Student* lastStudent = NULL;
    FILE* filesLoc = fopen(fileName, "r");

    int i;
    for (i = 0; i < 26; i++)
    {
        char dataFileName[256];
        if (fscanf(filesLoc, "%s", dataFileName) != 1)                          //jezeli nie udalo sie odczytac sciezki do wszyskich 26 plikow z danymi to wyczysc liste z pamieci zwroc blad (-1)
        {
            fclose(filesLoc);
            ClearStudentList(studentList);
            return -1;
        }

        FILE* dataFile = fopen(dataFileName, "rb");                             //odczytaj plik binarnie

        while (1)
        {
            Student newStudent;

            char day;
            char month;
            short year;

            if (fread(newStudent.firstName, sizeof(char), FIRSTNAME_LENGTH, dataFile) != sizeof(char) * FIRSTNAME_LENGTH) break;    //kazdy rekord ma dokladnie taka sama ilosc bajtow, wiec koniec pliku mozna stwierdzic, gdy nie da sie odczytac pierwszej zmiennej danego rekordu
            fread(newStudent.secondName, sizeof(char), SECONDNAME_LENGTH, dataFile);
            fread(&day, sizeof(char), 1, dataFile);
            fread(&month, sizeof(char), 1, dataFile);
            fread(&year, sizeof(short), 1, dataFile);
            fread(&newStudent.indexNumber, sizeof(int), 1, dataFile);

            newStudent.dateOfBirth.day = day;
            newStudent.dateOfBirth.month = month;
            newStudent.dateOfBirth.year = year;                                 //zamien elemnety daty na int'y; pliku byly zapisane jako zmienne innego typu w celu zaoszczedzenia pamieci

            Student* h;
            h = AddStudentToList(studentList, newStudent, lastStudent);         //dodaj nowo odczytanego studenta do listy
            if (lastStudent!= NULL && CompareStrings(lastStudent->secondName, h->secondName))
            {
                lastStudent = h;                                                //zmienna lastStudent jest opcjonalnym argumentem funkcji AddStudentToList(); jak jest uzywana powinna zawierac adres ostatniego elementu listy wg nazwiska; skraca to czas na wczytywanie studentow przy uruchomieniu programu
            }
            numberOfStudents++;
        }

        fclose(dataFile);
    }
    fclose(filesLoc);

    return numberOfStudents;
}
