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
 
 
 ----------------------------------------------------------------------------- */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "My_Macros.h"

using namespace std;

//function prototypes
void CreateFile(string &location);
void Apend();
void Print(string location);
void OpenFile(string location, int &i);
void WriteFile(string, int &i);
void Print_title(ofstream& fout);



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
    int i = 1;  // for number of enteries
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
                WriteFile(location, i);
                break;
            case 2:
#if SHOW_DEBUG_OUTPUT
                cout << "test 2\n";
#endif
                OpenFile(location, i);
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
void OpenFile(string location, int &i)
{
    cout << "Where is the database and what is it called?\n";
    cin >> location;
    //file check
    ifstream fin;
    fin.open(location);
    if (fin.is_open())
    {
        fin.seekg(0, ios::beg);
        fin >> i;
        fin.close();
        WriteFile(location, i);
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }

#if SHOW_DEBUG_OUTPUT
    cout << location << endl;
#endif
    
}

/* -----------------------------------------------------------------------------
 FUNCTION:          WriteFile()
 DESCRIPTION:       controls how information is writen to file
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void WriteFile(string location, int &i)
{
#if SHOW_DEBUG_OUTPUT
    cout << "In WriteFile() !!\n";
#endif
    //variables
    char fname[25];
    char lname[25];
    char MI;
    unsigned int social;
    unsigned int area_code;
    unsigned int phone_num;
    float salary;
    int x = 2;
    char yesno;
    //file IO
    ofstream fout;
    fout.open(location, ios::app);

    while (x == 2)
    {
        //number of enteries line
        fout.seekp(0, ios::beg);
        fout << i;
        //get information
        cout << "Employee's last name\n";
        cin >> lname;
        cout << "Employee's first name\n";
        cin >> fname;
        cout << "Employee's Middle Intial\n";
        cin >> MI;
        cout << "Employee's SSN\n";
        cin >> social;
        cout << "Employee's Area Code\n";
        cin >> area_code;
        cout << "Employee's Phone Number\n";
        cin >> phone_num;
        cout << "Employee's Salary\n";
        cin >> salary;
        
        //write to file
        fout.seekp(0, ios::end);
        fout << lname << endl
            << fname << endl
            << MI << endl
            << social << endl
            << area_code << endl
            << phone_num << endl
            << salary << endl;
        
        cout << "Add another entery to database? (y,n)\n";
        cin >> yesno;
        
        if (yesno == 'y' || yesno == 'Y')
        {
            x=2;
            i++;
        }
        else
            x=1;
    }
    fout.close();

}


void Print(string location)
{
    //variables
    char fname[25];
    char lname[25];
    char MI;
    unsigned int social;
    unsigned int area_code;
    unsigned int phone_num;
    float salary;
    string location2;
    int i, j;   //i = numb of entries, j =
    
    cout << "Where should the file be saved and what should it be called?\n";
    cin >> location2;
    
    //open database file and get # of enteries
    ifstream fin;
    fin.open(location);
    if (fin.is_open())
    {
        fin.seekg (0, ios::beg);
        fin >> i;
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }
    //setup user document
    ofstream fout;
    fout.open(location2);
    
    Print_title(fout);
    for (j = 1; j < i; j++)
    {
        fin.seekg(((7*j)-7), ios::beg);
        fin >> lname;
        fin >> fname;
        fin >> MI;
        fin >> social;
        fin >> area_code;
        fin >> phone_num;
        fin >> salary;
    }
}


void Print_title(ofstream& fout)
{
    
}



