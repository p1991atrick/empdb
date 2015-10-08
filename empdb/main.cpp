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
void handle_cmd_line_args(int argc, char *argv[], char *, char *, int &enteries);
void help();

void CreateFile(char *, char *, int &enteries);
void Print(char *, char *);
void OpenFile(char *, char *, int &enteries);
void WriteFile(char *, char *, int &enteries, Info *);
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
    //variables for later on
    char location[50]; //refered to as dbloc
    char location2[60];//refered to as numloc
    location2[0] = '\0';
    int enteries;

    if (argc <2)
        help();
    else
        handle_cmd_line_args(argc, argv, location, location2, enteries);

    return EXIT_CODE_SUCCESS;
}


void handle_cmd_line_args(int argc, char *argv[], char *location, char *location2, int &enteries)
{
     Info person;
    /*get args
    char * acceptible_strings[] =
    {
        "verbose", "create-file", "add-entrie", "dbloac", "print-report", "x", "help"
    };*/
    //true false checks
    bool found_help = false;
    bool found_create_file = false;
    bool found_add_entrie = false;
    bool found_dbloc = false;
    bool found_change_name = false;
    bool found_print_file = false;
    
    
    unsigned int count = 0;
    //loop for finding argv's
    for (int i=1; i < argc; i++)
    {
        char * argument = argv[i];
        //      DEBUG_OUTPUT(argv[i]);
        if (argument[0] != '-')      // for dos '/' should be used, cause dos
        {
            if (count > 0)
            {
                
            }
            else
            {
                cout << "Exiting with code " << EXIT_CODE_INCORECCT_INPUT << endl;
                exit(EXIT_CODE_INCORECCT_INPUT);
            }
        }
        count++;
        
        // Look for "help"
        int return_code = strcmp(argument + 1, "help");
        if (return_code == 0)
            found_help = true;
        // look for "create-file"
        return_code = strcmp(argument + 1, "create-file");
        if (return_code == 0)
        {
            found_create_file = true;
            i++;
            strcpy(location, argv[i]);
        }
        // look for "create-file"
        return_code = strcmp(argument + 1, "add-entrie");
        if (return_code == 0)
        {
            found_add_entrie = true;
            if(found_dbloc == true)
            {
                i++;
                strncpy(person.fname, argv[i], 20);
                i++;
                strncpy(person.lname, argv[i], 20);
                i++;
                strncpy(&person.MI, argv[i], 1);
                i++;
                person.social = atol(argv[i]);
                i++;
                person.area_code = atoi(argv[i]);
                i++;
                person.phone_num = atoi(argv[i]);
                i++;
                person.salary = atof(argv[i]);
            }
            
        }
        //look for file locaion
        return_code = strcmp(argument + 1, "dbloc");
        if (return_code == 0)
        {
            found_dbloc = true;
            i++;
            strcpy(location, argv[i]);
        }
        
    }
    if (found_create_file == true)
    {
        CreateFile(location, location2, enteries);
    }
    if (found_help == true || (found_dbloc == false && found_add_entrie == false && found_change_name == false && found_create_file == false && found_print_file == false))
    {
        help();
    }
    if (found_add_entrie == true && found_dbloc == true)
    {
        OpenFile(location, location2, enteries);
        WriteFile(location, location2, enteries, &person);
    }
    
}

/* -----------------------------------------------------------------------------
 FUNCTION:          help()
 DESCRIPTION:       lists all comands and their functions
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void help()
{
#if SHOW_DEBUG_OUTPUT
    cout <<"this is help" << endl;
#endif
    cout << "Employee Database tool\n"
    << "Writen by Patrick Kelly\n\n"
    << "-crate-file [destination]       creates a new database file in the location speciied with name given. will overwrite same name file.\n"
    << "-dbloc [location]               the location of the database file\n"
    << "-add-entrie [fistname] [lastname] [Middle Initial] [social] [area code] [phone number] [salary]\n"
    << "                                the dbloc must be specified first\n"
    << "-print-report [db location] [name of report file]\n"
    << "                                prints report file from chosen database file to listed report file. the report file name is optional\n";
}


/* -----------------------------------------------------------------------------
 FUNCTION:          CreateFile()
 DESCRIPTION:       Creates new database file and opens it
 RETURNS:           void function
 NOTES:
 ----------------------------------------------------------------------------- */
void CreateFile(char *dbloc, char *numloc, int &enteries)
{
    fstream database;
    ofstream count;
    char *returnarg = nullptr;
    //int returncode;
    //check if .db is on filename
    returnarg = strstr(dbloc, ".db");
    //returncode = strcmp(returnarg, ".db");
    if (returnarg == NULL)
    {
        strcat(dbloc, ".db");
    }
    //gen count file name
    unsigned int dblocsize = (strlen(dbloc)+1);
    strncpy(numloc, dbloc, dblocsize);
    strcat(numloc, "-count.dat");

    
    database.open(dbloc, ios::out | ios::trunc | ios::binary);
    if(database.is_open())
    {
        count.open(numloc, ios::trunc | ios::binary);
        if(!count.is_open())
            exit(EXIT_CODE_NO_FILE);
    }
#if SHOW_DEBUG_OUTPUT
    cout << dbloc << " and " << numloc << endl;
#endif
    enteries = 0;
    Count number;
    number.times = enteries;
    database.write(reinterpret_cast<char *>(&number), sizeof(number));
    database.close();
    count.close();
    
}

/* -----------------------------------------------------------------------------
 FUNCTION:          OpenFile()
 DESCRIPTION:       Gets file location from user and opens it for appending and get number of entries
 RETURNS:           void
 NOTES:
 ----------------------------------------------------------------------------- */
void OpenFile(char *dbloc, char *numloc, int &enteries)
{
    //temp arg variables
    char *returnarg = nullptr;
    //int returncode;
    
    //check if .db is on filename
    returnarg = strstr(dbloc, ".db");
   // returncode = strcmp(returnarg, ".db");
    if (returnarg == NULL)
    {
        strcat(dbloc, ".db");
    }
    //gen count file name
    unsigned int dblocsize = (strlen(dbloc)+1);
    strncpy(numloc, dbloc, dblocsize);
    strcat(numloc, "-count.dat");
    
    //file check
    ifstream database;
    database.open(dbloc, ios::binary);
    if (database.is_open())
    {
        ifstream count;
        count.open(numloc, ios::binary);
        if (count.is_open())
        {
            Count numbers;
            database.read(reinterpret_cast<char *>(&numbers), sizeof(numbers));
            enteries = numbers.times;
            count.close();
        }
        else
        {
            cout << "Failed to open file\n";
            exit(EXIT_CODE_NO_FILE);
        }
        database.close();
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
void WriteFile(char *dbloc, char *numloc, int &enteries, Info *person)
{
#if SHOW_DEBUG_OUTPUT
    cout << "In WriteFile !!\n";
#endif
    Count number;
    //file IO
    fstream database(dbloc, ios::out | ios::app | ios::binary);
    WriteFile_VerifySSN(person);
    WriteFile_VerifyArea(person);
    WriteFile_VerifyPhone(person);
    //number of entries
    enteries++;
    number.times = enteries;
    
    //write to file
    database.write(reinterpret_cast<char *>(&person), sizeof(person));
    database.close();
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
    database.read(reinterpret_cast<char *>(&person), sizeof(person));
    enteries = person.times;
    
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



