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
    float salary;
};

//function prototypes
void CreateFile(string &location);
void Apend();
void Print(string location);
void OpenFile(string location);
void WriteFile(string);
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
    string location;
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
                cout << "test 1\n";
#endif
                CreateFile(location);
                WriteFile(location);
                break;
            case 2:
#if SHOW_DEBUG_OUTPUT
                cout << "test 2\n";
#endif
                OpenFile(location);
                break;
            case 3:
#if SHOW_DEBUG_OUTPUT
                cout << "test 3\n";
#endif
                Print(location);
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

void CreateFile(string &location)
{
    //get peramiters
    cout << "what should the database be called?\n";
    cin >> location;
    
#if SHOW_DEBUG_OUTPUT
    cout << location << endl;
#endif
    
}

/* -----------------------------------------------------------------------------
 FUNCTION:          OpenFile()
 DESCRIPTION:       Gets file location from user and opens it for appending
 RETURNS:           0 for good and 1 for fail
 NOTES:
 ----------------------------------------------------------------------------- */
void OpenFile(string location)
{
    cout << "Database location/name: ";
    cin >> location;
    //file check
    ifstream fin(location, ios::binary);
    if (fin.is_open())
    {
#if SHOW_DEBUG_OUTPUT
        cout << location << endl << endl;
#endif
        WriteFile(location);
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
void WriteFile(string location)
{
#if SHOW_DEBUG_OUTPUT
    cout << "In WriteFile !!\n";
#endif
    //variables
    int x = 2;
    char yesno;
    Info person;
    //file IO
    fstream database(location, ios::out | ios::app | ios::binary);

    do
    {
        //get information
        cin.ignore();
        //get first name
        cout << "First Name: ";
        cin.getline(person.fname, NAME_SIZE);
        if (strlen(person.fname) > 24)
        {
            cout << "Name can't have more than 24 letters. Enter name again: ";
            cin.getline(person.fname, NAME_SIZE);
        }
        //get mi
        cout << "Middle Intital: ";
        cin >> person.MI;
        if (islower(person.MI))
        {
            putchar (toupper(person.MI));
        }
        cin.ignore();
        //get last name
        cout << "Last Name: ";
        cin.getline(person.lname, NAME_SIZE);
        if (strlen(person.lname) > 24)
        {
            cout << "Name can't have more than 24 letters. Enter name again: ";
            cin.getline(person.lname, NAME_SIZE);
        }
        //get ssn
        cout << "Employee's SSN: ";
        cin >> person.social;
        /*while (sizeof(person.social) < 9 || sizeof(person.social) > 9)
        {
            cin >> person.social;
            cout << "You must enter a valid SSN: ";
        }*/
        //get phone area code
        cout << "Employee's Area Code: ";
        cin >> person.area_code;
        cout << "Employee's Phone Number: ";
        cin >> person.phone_num;
        cout << "Employee's Salary: ";
        cin >> person.salary;
        
        //write to file
        database.write(reinterpret_cast<char *> (&person), sizeof(person));
        
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
void Print(string location)
{
    //variables
    string location2;
    int i = 1;
    Info person;
    
    cout << "Where is the database: ";
    cin >> location;
    
    cout << "Where should the file be saved and what should it be called: ";
    cin >> location2;
    
    //open database file and get # of enteries
    ifstream database;
    database.open(location, ios::binary);
    if (database.is_open())
    {
        cout << "File is open.\n";
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }
    //setup user document
    ofstream report;
    report.open(location2, ios::trunc);
    
    //setup file header
    Print_title(report);
    
    //loop to write enteries to file
    while (!database.eof())
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
    
    report << "Employee    Last                    First                   MI    SS           Phone           Yearly" << endl
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
    int stringlength, x;
    if (i < 10)
    {
        //line number
        report << i << "           ";
    }
    else if(i >= 10 || i < 100)
    {
        report << i << "          ";
    }
    //last name placement
    stringlength = strlen(db->lname);
    x = 24 - stringlength;
    report << db->lname;
    for (int j=0; j<x; j++)
    {
        report << " ";
    }
    //first name placement
    stringlength = strlen(db->fname);
    x = 24 - stringlength;
    report << db->fname;
    for (int j=0; j<x; j++)
    {
        report << " ";
    }
    //MI placement
    report << db->MI << "     ";
    //SS number placement
    report << db->social << "    ";
    //phone number placement
    report << "(" << db->area_code << ")" << db->phone_num << "    ";
    //salary placement
    report << db->salary << endl;
}























