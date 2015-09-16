//  Created by Gordon Freeman on 8/27/15.
//  Copyright © 2015 Patrick Kelly. All rights reserved.

/* -----------------------------------------------------------------------------
 
 FILE:              empdb.cpp
 
 DESCRIPTION:       A brief description of this source code file ...
 
 COMPILER:          Visual Studio C++ and Xcode C++ compiler
 
 NOTES:             Put other information here ...
 
 MODIFICATION HISTORY:
 
 Author                  Date               Version
 ---------------         ----------         --------------
 Patrick Kelly           2015-8-27          1.0
 Patrick Kelly           2015-8-29          2.0
 Patrick Kelly           2015-9-15          3.0 - It Works
 
 
 ----------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "My_Macros.h"

using namespace std;

//record information and variables
const int NAME_SIZE = 25;
struct Info
{
    char fname[NAME_SIZE];
    char lname[NAME_SIZE];
    char MI;
    unsigned int social;
    unsigned int area_code;
    unsigned int phone_num;
    double salary;  //told in class to change from float to double
};

//for count
struct Count
{
    int times;
};

//function prototypes
void CreateFile(char *, char *, int &enteries);
void Apend();
void Print(char *, char *);
void OpenFile(char *, char *, int &enteries);
void WriteFile(char *, char *, int &enteries);
void Print_title(ofstream& fout);
void Print_body(ofstream& report, int i, Info *);


/* -----------------------------------------------------------------------------
 FUNCTION:          main()
 DESCRIPTION:       The guy driving
 RETURNS:           0 with no errors
 NOTES:             version 1
 ----------------------------------------------------------------------------- */
int main()
{
    //variables for later on
    char location[50];
    char location2[60];
    int enteries;
    //int for main menu
    int choose;
    int loop = 3;
    
    while (loop ==3)
    {
        //menu
        cout << "   Employee Database Editor    \n\n"
        << "    Main Menu\n"
        << "1. Create new database file\n"
        << "2. Add to current database file\n"
        << "3. Print a database report\n"
        << "9. Exit\n";
        cin >> choose;
        
        switch(choose)
        {
            case 1:
#if SHOW_DEBUG_OUTPUT
                cout << "In case 1\n";
#endif
                CreateFile(location, location2, enteries);
                WriteFile(location, location2, enteries);
                break;
            case 2:
#if SHOW_DEBUG_OUTPUT
                cout << "In case 2\n";
#endif
                OpenFile(location, location2, enteries);
                break;
            case 3:
#if SHOW_DEBUG_OUTPUT
                cout << "In case 3\n";
#endif
                Print(location, location2);
                break;
            case 9:
                cout << "Good bye\n";
                loop = 4;
                break;
            default:
                cout << "You must pick an option from the list\n"
                << choose << " is not a valid selection\n\n";
                break;
        }
        CLEAR_SCREEN;
    }
    
    return EXIT_CODE_SUCCESS;
}


/* -----------------------------------------------------------------------------
 FUNCTION:          CreateFile()
 DESCRIPTION:       Creates new database file and opens it
 RETURNS:           1 for new file, 2 for given
 NOTES:
 ----------------------------------------------------------------------------- */

void CreateFile(char *dbloc, char *numloc, int &enteries)
{
    //get peramiters
    char temp[51];
    cout << "what should the database be called?\n";
    cin >> temp;
    strcat(temp, ".db");
    strcpy(dbloc, temp);
    strcat(temp, "-count.dat");
    strcpy(numloc, temp);
    
#if SHOW_DEBUG_OUTPUT
    cout << dbloc << " -and- " << numloc << endl;
#endif
    enteries = 0;
    
}

/* -----------------------------------------------------------------------------
 FUNCTION:          OpenFile()
 DESCRIPTION:       Gets file location from user and opens it for appending
 RETURNS:           void
 NOTES:
 ----------------------------------------------------------------------------- */
void OpenFile(char *dbloc, char *numloc, int &enteries)
{
    //temp holder
    char temp[60];
    //get db location
    cout << "Database location/name: ";
    cin >> temp;
    strcat(temp, ".db");
    strcpy(dbloc, temp);
    strcat(temp, "-count.dat");
    strcpy(numloc, temp);
    
    //file check
    ifstream database;
    database.open(dbloc, ios::binary);
    if (database.is_open())
    {
        //count file check
        ifstream count;
        count.open(numloc, ios::binary);
        if (count.is_open())
        {
            Count numbers;
            count.read(reinterpret_cast<char *>(&numbers), sizeof(numbers));
            enteries = numbers.times;
            count.close();
            database.close();
            WriteFile(dbloc, numloc, enteries);
        }
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }
    
}

/* -----------------------------------------------------------------------------
 FUNCTION:          WriteFile()
 DESCRIPTION:       controls how information is writen to file
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void WriteFile(char *dbloc, char *numloc, int &enteries)
{
#if SHOW_DEBUG_OUTPUT
    cout << "In WriteFile !!\n";
#endif
    //variables
    int x = 2;
    char yesno;
    char upper;
    Info person;
    Count numbers;
    //file IO
    fstream database(dbloc, ios::out | ios::app | ios::binary);
    fstream databasecount(numloc, ios::out | ios::trunc | ios::binary);
    do
    {
        //get information
        cin.ignore();
        //get first name
        cout << "First Name: ";
        cin.getline(person.fname, NAME_SIZE);
        //get mi
        cout << "Middle Intital: ";
        cin >> person.MI;
        if (islower(person.MI))
        {
            upper = person.MI;
            toupper(upper);
            person.MI = upper;
        }
        cin.ignore();
        //get last name
        cout << "Last Name: ";
        cin.getline(person.lname, NAME_SIZE);
        //get ssn
        cout << "Employee's SSN: ";
        cin >> person.social;
        //get phone area code
        cout << "Employee's Area Code: ";
        cin >> person.area_code;
        cout << "Employee's Phone Number: ";
        cin >> person.phone_num;
        cout << "Employee's Salary: ";
        cin >> person.salary;
        
        //number of entries
        enteries++;
        numbers.times = enteries;
        
        //write to file
        database.write(reinterpret_cast<char *>(&person), sizeof(person));
        databasecount.write(reinterpret_cast<char *>(&numbers), sizeof(numbers));
        //go again?
        cout << "Add another entery to database? (y,n)\n";
        cin >> yesno;
        if (yesno == 'y' || yesno == 'Y')
        {
            x=2;
        }
        else
            x=1;
    }while (x==2);
    database.close();
}


/* -----------------------------------------------------------------------------
 FUNCTION:          Print()
 DESCRIPTION:       controls the writing of the report file
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void Print(char *dbloc, char *numloc)
{
    //variables
    int enteries;
    int i = 1;
    Info person;
    char temp[60];
    char location2 [60];
    
    //ask for db location
    cout << "Where is the database: ";
    cin >> temp;
    
    //get count dat
    strcpy(dbloc, temp);
    strcat(temp, "-count.dat");
    strcpy(numloc, temp);
    
    //open database file
    ifstream database;
    database.open(dbloc, ios::binary);
    if (database.is_open())
    {
#if SHOW_DEBUG_OUTPUT
        cout << "db is open.\n";
#endif
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }
    
    //open count dat
    ifstream entrie;
    entrie.open(numloc, ios::binary);
    if (entrie.is_open())
    {
#if SHOW_DEBUG_OUTPUT
        cout << "dat is open.\n";
#endif
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }

    
    
    cout << "Where should the file be saved and what should it be called: ";
    cin >> location2;
    
    //setup user document
    ofstream report;
    report.open(location2, ios::trunc);
    
    /*get number of entries*/
    Count numbers;
    entrie.read(reinterpret_cast<char *>(&numbers), sizeof(numbers));
    enteries = numbers.times;
    
    //setup file header
    Print_title(report);
    
    //loop to write enteries to file
    while (i <= enteries)
    {
        //loading record
        database.read(reinterpret_cast<char *>(&person), sizeof(person));
        //write to file
        Print_body(report, i, &person);
        i++;//record count
    }
    //close files
    database.close();
    report.close();
}



/* -----------------------------------------------------------------------------
 FUNCTION:          Print_title()
 DESCRIPTION:       write the header lables to the report file
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */

void Print_title(ofstream& report)
{
    
    report << "                 Employee Database Report\n"
           << "Employee    Last                    First                   MI    SS           Phone           Yearly" << endl
           << "Number      Name                    Name                          Number       Number          Salary" << endl
           << "--------    ----                    -----                   --    ------       ------          ------" << endl;
}



/* -----------------------------------------------------------------------------
 FUNCTION:          Print_body()
 DESCRIPTION:       writes the bulk of the information to the report file
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void Print_body(ofstream& report, int i, Info *db)
{
    //line number
    report << setw(12) << left << i;
    //last name placement
    report << setw(24) << db->lname;
    //first name placement
    report << setw(24) << db->fname;
    //MI placement
    report << setw(6) << db->MI;
    //SS number placement
    report << setw(13) << db->social;
    //phone number placement
    report << setw(1) << "(";
    report << setw(3) << db->area_code;
    report << setw(1) << ")" ;
    report << setw(11) << db->phone_num;
    //salary placement
    report.unsetf (ios::floatfield);
    report << setw(15) << setprecision(12) << db->salary << endl;
}























