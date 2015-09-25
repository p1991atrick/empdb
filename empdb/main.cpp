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
    unsigned long int social;
    unsigned int area_code;
    unsigned int phone_num;
    double salary;  //told in class to change from float to double
};

//for count
struct Count
{
    unsigned int times;
};

//function prototypes
void handle_cmd_line_args(int argc, char *argv[]);
void help();

void CreateFile(char *, char *, int &enteries);
void Print(char *, char *);
void OpenFile(char *, char *, int &enteries);
void WriteFile(char *, char *, int &enteries);
void WriteFile_VerifySSN(Info *);
void WriteFile_VerifyArea(Info *);
void WriteFile_VerifyPhone(Info *);
void Print_title(ofstream& fout);
void Print_body(ofstream& report, int i, Info *);


/* -----------------------------------------------------------------------------
 FUNCTION:          main()
 DESCRIPTION:       The guy driving
 RETURNS:           0 with no errors
 NOTES:
 ----------------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    handle_cmd_line_args(argc, argv);

    return EXIT_CODE_SUCCESS;
}


void handle_cmd_line_args(int argc, char *argv[])
{
    //get args
    char * acceptible_strings[] =
    {
        "v", "c", "w", "f", "p", "x", "h"
    };
    //truefalse for check
    bool found_verbose = false;
    bool found_c = false;
    bool found_write = false;
    bool found_file = false;
    bool found_print = false;
    bool found_x = false;
    bool found_help = false;
    
    //  DEBUG_OUTPUT(argc);
    for (int i=1; i < argc; i++)
    {
        //      DEBUG_OUTPUT(argv[i]);
        char * argument = argv[i];
        if(argument[0] != '-')      // for dos '/' should be used
        {
            cout << "Exiting with code " << EXIT_CODE_INCORECCT_INPUT << endl;
            exit(EXIT_CODE_INCORECCT_INPUT);
        }
            // Look for "help"
            int return_code = strcmp(argument + 1, "h");
            if (return_code == 0)
            {
                found_help = true;
            }
        
    }
    if (found_help == true)
    {
        help();
    }
}


void help()
{
#if DEBUG_OUTPUT
    cout <<"this is help" << endl;
#endif
}


/* -----------------------------------------------------------------------------
 FUNCTION:          CreateFile()
 DESCRIPTION:       Creates new database file and opens it
 RETURNS:           void function
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
    char yesno = 'n';
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
        WriteFile_VerifySSN(&person);
        //get phone area code
        cout << "Employee's Area Code: ";
        cin >> person.area_code;
        WriteFile_VerifyArea(&person);
        cout << "Employee's Phone Number: ";
        cin >> person.phone_num;
        WriteFile_VerifyPhone(&person);
        cout << "Employee's Salary: ";
        cin >> person.salary;
        
        
        //number of entries
        enteries++;
        numbers.times = enteries;
        
        //write to file
        database.write(reinterpret_cast<char *>(&person), sizeof(person));
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
    //write report count
    databasecount.write(reinterpret_cast<char *>(&numbers), sizeof(numbers));
    
    database.close();
    databasecount.close();
}

/* -----------------------------------------------------------------------------
 FUNCTION:          WriteFile_VerifySSN()
 DESCRIPTION:       verifyies that the SSN has 9 numbers
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void WriteFile_VerifySSN(Info *db)
{
    unsigned long int temp, number_of_digits= 1;
    temp = db->social;
    do {
        number_of_digits++;
        temp /= 10;
    } while (temp >= 9);
    if (number_of_digits != 9)
    {
        cout << "Enter correct SSN: ";
        cin >> db->social;
        cin.ignore();
    }
}

/* -----------------------------------------------------------------------------
 FUNCTION:          WriteFile_VerifyArea()
 DESCRIPTION:       verifies that the Area Code has 3 numbers
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void WriteFile_VerifyArea(Info *db)
{
    unsigned int temp, number_of_digits= 1;
    temp = db->area_code;
    do {
        number_of_digits++;
        temp /= 10;
    } while (temp >= 9);
    if (number_of_digits != 3)
    {
        cout << "Enter correct Area Code: ";
        cin >> db->area_code;
        cin.ignore();
    }
}

/* -----------------------------------------------------------------------------
 FUNCTION:          WriteFile_VerifyPhone()
 DESCRIPTION:       verifys that the Phone Number has 7 numbers
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void WriteFile_VerifyPhone(Info *db)
{
    unsigned int temp, number_of_digits= 1;
    temp = db->phone_num;
    do {
        number_of_digits++;
        temp /= 10;
    } while (temp >= 9);
    if (number_of_digits != 7)
    {
        cout << "Enter correct Phone Number: ";
        cin >> db->phone_num;
        cin.ignore();
    }
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
    Count numbers;
    char temp[60];
    char location2 [60] = "Employee.Rpt";
    char yesno = 'n';
    
    //ask for db location
    cout << "Where is the database: ";
    cin >> temp;
    
    //get count dat
    strcat(temp, ".db");
    strcpy(dbloc, temp);
    strcat(temp, "-count.dat");
    strcpy(numloc, temp);
    
    //open database file
    ifstream database;
    ifstream times;
    
    database.open(dbloc, ios::binary);
    if (database.is_open())
    {
#if SHOW_DEBUG_OUTPUT
        cout << "db is open.\n";
#endif
        //open count dat
        times.open(numloc, ios::binary);
        if (times.is_open())
        {
#if SHOW_DEBUG_OUTPUT
            cout << "dat is open.\n";
#endif
        }
    }
    else
    {
        cout << "Failed to open file\n";
        exit(EXIT_CODE_NO_FILE);
    }
    
    cout << "Change default name? (y/n): ";
    cin >> yesno;
    if (yesno == 'y' || yesno == 'Y')
    {
        cout << "Where should the file be saved and what should it be called: ";
        cin >> location2;
    }
    
    //setup user document
    ofstream report;
    report.open(location2, ios::trunc);
    
    /*get number of entries*/
    times.read(reinterpret_cast<char *>(&numbers), sizeof(numbers));
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
    times.close();
}

/* -----------------------------------------------------------------------------
 FUNCTION:          Print_title()
 DESCRIPTION:       write the header lables to the report file
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void Print_title(ofstream& report)
{
    
    //title line
    report << setw(30) << right << "Employee Database Report";
    report << endl << endl;
    //1st line
    report << setw(12) << left << "Employee" << setw(20) << "Last" << setw(20) << "First" << setw(6) << "MI" << setw(13) << "SS"     << setw(16) << "Phone"  << setw(15) << "Yearly" << endl;
    //2nd line
    report << setw(12) << left << "Number"   << setw(20) << "Name" << setw(20) << "Name"  << setw(6) << "  " << setw(13) << "Number" << setw(16) << "Number" << setw(15) << "Salary" << endl;
    //3rd line
    report << setw(12) << "--------" << setw(20) << "----" << setw(20) << "-----" << setw(6) << "--" << setw(13) << "------" << setw(16) << "------" << setw(15) << "------" << endl;

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
    report << setw(NAME_SIZE-4) << db->lname;
    //first name placement
    report << setw(NAME_SIZE-4) << db->fname;
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
    report << "$ " << setw(13) << setprecision(12) << db->salary << endl;
}



