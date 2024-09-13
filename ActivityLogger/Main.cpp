//Programming Language: C++
//IDE: Visual Studio
//Compile And Build In Console Using g++: g++ main.cpp -o programB
//Run In Console Using g++: Linux/Mac: ./programB       Windows: programB.exe

//Author: Connor Gilmore
//Date: 9/27/2024
//Class: CS 4500 - Intro To Software Profession
//Desc: Creates A New Activity Log Entry While the User Does the Activity

//Data Structure 1: Vectors: in c++ vectors are like dynamic arrays that grow in size when new elements are added.
// I used vectors to store the amount of files found in the user's folder that match the format 'LastnameFirstnameLog.csv'
//I also used vectors to store a csv row. each vector element corresponded to a csv cell. 
//both use cases for vectors were becuase I dont know the size of the csv row or how many files with the same format exist in the folder

//Data Structure 2: ActivityEnum: simply a list of enum values that represent a character code 0 - D. These codes represent an Activity

//Data Structure 3: LogEntry: A class structure to represent a new row in the csv file

//Data Structure 4: ActivityLogger: a class structure that represents a logger for adding new LogEntries to the log csv file

//Data Structure 5: ActivityLoggerConsole: a class structure that acts as a wrapper around the logger and allows user to interact with it via the console

//External File 1: Any .csv files in the folder will be accessed see if they match the format 'LastnameFirstnameLog.csv'

//External File 2: A single matching .csv file in the folder will be accessed, read and writtten to.

//Global Function: WriteAppIntro(), simply outputs the introduction screen for this app to the console

//No Global Variables 


//Sources
//https://github.com/mortennobel/cpp-cheatsheet basic c++ syntax
//https://en.cppreference.com/w/cpp/filesystem working with file system content(for csv)
// https://en.cppreference.com/w/cpp/regex c++ library syntax for regex
// https://cpprocks.com/files/c++11-regex-cheatsheet.pdf using regex c++ library
//https://www.geeksforgeeks.org/cpp-program-to-get-the-list-of-files-in-a-directory/ get all files in my folder
//https://stackoverflow.com/questions/17095639/bind-a-char-to-an-enum-type set enum equal to characters
//https://www.geeksforgeeks.org/csv-file-management-using-c/ access/read/write for csv files
//https://en.cppreference.com/w/cpp/utility/format/format format method I use to format datetime strings
//https://en.cppreference.com/w/cpp/chrono/system_clock/now working with system clock
//https://cplusplus.com/forum/beginner/217950/ for outputing activity code table
#include "ActivityLoggerConsole.h"
#include <iostream>
using namespace std;

//Action: Details what the app is about and by who
void WriteAppIntro();

//Action: Where this c++ program starts. Controls program flow via the consoleApp object
int main()
{

  try {
    
    WriteAppIntro();

    cin.ignore();

    ActivityLoggerConsole consoleApp;

    consoleApp.WriteLogFileHeader();

    consoleApp.ActivityTypeHandler();

    consoleApp.GroupSizeHandler();

    consoleApp.NoteEntryHandler();

    consoleApp.TimeEventHandler();

    consoleApp.LogActivity();

  }
  catch (const exception& e) {
    cerr << endl;
    cerr << e.what() << endl;
    cerr << endl;
    exit(1);
  }

    return 0;
}

//Action: Details what the app is about and by who
void WriteAppIntro()
{
  cout << "\n\n\n\n";
  cout << "\nWelcome To Activity Logger!\n" << endl;
  cout << "\nOtherwise Known As Program B!\n" << endl;
  cout << "\nAuthor: Connor Gilmore\n" << endl;
  cout << "\nGroup: Team 11\n" << endl;
  cout << "\nDetails: Creates A New Activity Log Entry While the User Does the Activity\n" << endl;
  cout << "\n\Summary: Inputs from the user's keyboard and a user's csv file following the format 'LastnameFirstnameLog.csv'; outputs to the console and to the user's csv file. Designed to track and log time time a user spends doing a class Activity, This program uses your computers system clock to track time spent on an activity and automatically generates a new log to the csv file when the user is done working on their activity!\n" << endl;
  cout << "\n\n\n\n";
  cout << "Please Press Enter To Continue...\n" << endl;
}

