#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <format>
#include "LogEntry.h"
using namespace std;
//controls logs entries to the user's csv file
class ActivityLogger
{
public:
	//Action: contstructor initalizes Logger entity. finds log file
	ActivityLogger();

	//string to being comparable too to check if a log validation was successful 
  const string LOG_APPROVED = "APPROVED";

	LogEntry ActivityEntry;
	//Action: adds log entry to csv file. splits log entry if need be
//Return: returns a string with all of the new rows added to the csv file
	string LogActivity();
	//Action: getter for LogOwnerFirstName
//Return: user's first name
	string GetFirstNameOfLogOwner();
	//Action: getter for LogOwnerLastName
//Return: user's last name
	string GetLastNameOfLogOwner();
	//Action: getter for ClassID
//Return: class id associated with activity log
	string GetClassID();
	//Action: getter for ClassID
//Return: name of activity log csv file
	string GetFileName();
	//Action: gets current local date time 
//Returns: string in mm/dd/yyyy format
	string AccessCurrentDate();
	//Action: gets current local time 
//Returns: string in hh:mm format
	string AccessCurrentTime();
	//Action: adds a single entry as a row to the csv file
//Parameter: newLog (LogEntry) entry being converted to csv row
//Return: returns string will equal "APPROVED" if log entry is valid. If the entry is not valid we get error report instead
	string ValidateLogEntry(LogEntry newLog);


private:
	//file name of user's activity log csv file
	string LogFile;
	//user's first name
	string LogOwnerFirstName;
	//user's last name
	string LogOwnerLastName;
	//class id associated with user's activity log
	string ClassID;

	//Action: adds a single entry as a row to the csv file
//Parameter: newLog (LogEntry) entry being converted to csv row
//Return: csv row added to file as a string
	string ApendNewCsvRow(LogEntry newLog);
	//Action: determines if Activity Entry goes over midnight
//Return: returns true if log enty should be split
	bool ShouldLogEntrySplit();
	//Action: gets local time from user's computers system clock
//Returns: returns data type from chrono library with info on user's current local date and time
	chrono::zoned_time<chrono::system_clock::duration> GetLocalTime();
	//Action: Stores Class Id in classes ClassID property
	void StoreValidClassID(string id);
	//Action: Stores first and last names in classes LogOwnerFirstName and LogOwnerLastName property
//Parameter: fname (string) first name found in the csv file header
//Parameter: lname (string) last name found in the csv file header
	void StoreValidName(string fname, string lname);
	//Action: Finds user's activity log file
//Returns: string that is the activity log file name
	string FindActivityLogFile();
	//Action: get all the csv files in the folder 
//Return: a vector list of all the csv files in the folder 
	vector<string> FetchAllCsvFileNamesInFolder();
	//Action: looks at all the csv files in the folder for files that match are desired 'LastnameFirstnameLog.csv' format
//Parameter: fileNames (vector<string>), list of all csv file names in the folder
//Return: a vector list of all the csv files that match the format 'LastnameFirstnameLog.csv'
	vector<string> FilterFilesForActivityLogFormat(vector<string> fileNames);
	//Action: parses all the rows in the user's csv file
//Parameter: logFileName (string) is file name of activity log 
	void ParseLogData(string logFileName);
	//Action: if we are on the first row, we can get the user's name. if we are on the second row we can get the class id
//Parameter: cells (vector<string>) is an array of all the cells in a row in the csv file
//Parameter: rowNumber (int) is the row number in the csv file we are on.
	void StoreLogHeaderDetails(vector<string> cells, int rowNumber);
	//Action: validates that the csv row sizes are correct. must be between 5 and 6 cells. normally length 5 cells, but can be 6 cells if user added a note to an entry
//Parameter: amountOfCells (int) is amount of cells in a csv row 
//Parameter: rowNumber (int) is the row number in the csv file we are on.
	void ValidateCellCountInCsvRow(int amountOfCells, int rowNumber);

};

