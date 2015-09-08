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
void CreateFile(string &location, int &ownfile);
void Apend();
void Print();
void OpenFile(string location, int ownfile);
void WriteFile(string);




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
    int ownfile = 2;
    //int for main menu
    int choose;
    int loop = 3;
    
    while (loop ==3)
    {
        //menu
        cout << "   Employee Database Editor    \n\n"
        << " Pick an option number from the menu below.\n\n"
        << "    Main Menu\n"
        << "1. Create new database file\n"
        << "2. Edit current database file\n"
        << "3. Print a database report\n"
        << "9. Exit\n";
        cin >> choose;
        
        switch(choose)
        {
            case 1:
#if SHOW_DEBUG_OUTPUT
                cout << "test 1\n";
#endif
                CreateFile(location, ownfile);
            case 2:
                OpenFile(location, ownfile);
                WriteFile(location);
#if SHOW_DEBUG_OUTPUT
                cout << "inside the loop!\n";
#endif
                break;
            case 3:
#if SHOW_DEBUG_OUTPUT
                cout << "test 3\n";
#endif
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
    
    
    return 0;
}


/* -----------------------------------------------------------------------------
 FUNCTION:          CreateFile()
 DESCRIPTION:       Creates new database file and opens it
 RETURNS:           1 for new file, 2 for given
 NOTES:
 ----------------------------------------------------------------------------- */

void CreateFile(string &location, int &ownfile)
{
    //get peramiters
    cout << "what should the database be called?\n";
    cin >> location;
    
#if SHOW_DEBUG_OUTPUT
    cout << location;
#endif
    //to not ask for file later on
    ownfile = 1;
}

/* -----------------------------------------------------------------------------
 FUNCTION:          OpenFile()
 DESCRIPTION:       Gets file location from user and opens it for appending
 RETURNS:           0 for good and 1 for fail
 NOTES:
 ----------------------------------------------------------------------------- */
void OpenFile(string location, int ownfile)
{
    //find file
    if (ownfile == 2)
    {
        cout << "Where is the database and what is it called?\n";
        cin >> location;
#if SHOW_DEBUG_OUTPUT
        cout << location << endl;
#endif
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
    
    while (x == 2)
    {
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
        ofstream fout;
        fout.open(location, ios::app);

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
        }
        else
            x=1;
    }
}









