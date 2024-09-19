#include "ActivityLogger.h"
#include <iostream>
#include <filesystem>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace filesystem;
//Action: contstructor initalizes Logger entity. finds log file
ActivityLogger::ActivityLogger()
{
	LogOwnerLastName = "";
	LogOwnerFirstName = "";
	ClassID = "";
	LogFile = FindActivityLogFile();
}
//Action: adds log entry to csv file. splits log entry if need be
//Return: returns a string with all of the new rows added to the csv file
string ActivityLogger::LogActivity()
{
	string logValidationResult = ValidateLogEntry(ActivityEntry);

	if (logValidationResult != LOG_APPROVED)
	{
		throw runtime_error(logValidationResult);
	}
	LogEntry secondaryActivityEntry;

	if (ShouldLogEntrySplit())
	{
		secondaryActivityEntry.SplitFrom(ActivityEntry);

		ActivityEntry.SetTimeEnd("23:59");
	}

	string newLogs = ApendNewCsvRow(ActivityEntry) + "\n";

	logValidationResult = ValidateLogEntry(secondaryActivityEntry);

	if (logValidationResult == LOG_APPROVED)
	{
		newLogs = newLogs + ApendNewCsvRow(secondaryActivityEntry) + "\n";
	}

	return newLogs;
}
//Action: adds a single entry as a row to the csv file
//Parameter: newLog (LogEntry) entry being converted to csv row
//Return: csv row added to file as a string
string ActivityLogger::ApendNewCsvRow(LogEntry newLog)
{

	string row = "\n" + newLog.GetDateStart() + "," + newLog.GetTimeStart() + "," + newLog.GetTimeEnd()
		+ "," + to_string(newLog.GetGroupSize()) + "," + string(1, newLog.GetActivityType()) + ",";

	if (newLog.GetNote().empty() == false)
	{
		row = row + newLog.GetNote();
	}

	ofstream file(LogFile, ios::app);

	if (file.is_open()) {
	
		file << row;
		file.close();           
	}
	else {
		throw runtime_error("File Error: Could not add log entry to the CSV file.");
	}

	file.close();

	return row;
}
//Action: determines if Activity Entry goes over midnight
//Return: returns true if log enty should be split
bool ActivityLogger::ShouldLogEntrySplit()
{
	if (ActivityEntry.GetDateEnd() == ActivityEntry.GetDateStart())
	{
		return false;
	}
	else
	{
		return true;
	}

}
//Action: adds a single entry as a row to the csv file
//Parameter: newLog (LogEntry) entry being converted to csv row
//Return: returns string will equal "APPROVED" if log entry is valid. If the entry is not valid we get error report instead
string ActivityLogger::ValidateLogEntry(LogEntry newLog)
{

	if (newLog.Empty())
	{
		string err = "Error: Invalid Log Entry.\n";
		if (newLog.GetActivityType() == ' ')
		{
			err += "Activity Code Was Never Picked\n";
		}
		if (newLog.GetDateStart().empty())
		{
			err += "Start Date For Log Was Never Set\n";
		}
		if (newLog.GetDateEnd().empty())
		{
			err += "End Date For Log Was Never Set\n";
		}
		if (newLog.GetTimeStart().empty())
		{
			err += "Start Time For Activity Was Never Set\n";
		}
		if (newLog.GetTimeEnd().empty())
		{
			err += "End Time For Activity Was Never Set\n";
		}
		if (newLog.GetGroupSize() == 0)
		{
			err += "Amount Of People Working On The Activity Was Never Set\n";
		}

		return err;
	}
	return LOG_APPROVED;
}
//Action: gets local time from user's computers system clock
//Returns: returns data type from chrono library with info on user's current local date and time
chrono::zoned_time<chrono::system_clock::duration> ActivityLogger::GetLocalTime()
{
	chrono::time_point<chrono::system_clock> currentTime = std::chrono::system_clock::now();

	const chrono::time_zone* myLocalTimeZone = chrono::current_zone();

	chrono::zoned_time localTime(myLocalTimeZone, currentTime);

	return localTime;
}
//Action: gets current local date time 
//Returns: string in mm/dd/yyyy format
string ActivityLogger::AccessCurrentDate()
{	
	return std::format("{:%m/%d/%Y}", GetLocalTime());
}
//Action: gets current local time 
//Returns: string in hh:mm format
string ActivityLogger::AccessCurrentTime() 
{
	return format("{:%H:%M}", GetLocalTime());
}
//Action: Finds user's activity log file
//Returns: string that is the activity log file name
string ActivityLogger::FindActivityLogFile()
{
	vector<string> csvFileNames = FetchAllCsvFileNamesInFolder();
	if (csvFileNames.empty())
	{
		throw runtime_error("File Error: No CSV files exist in the current folder.");
	}

	vector<string> filteredCsvFileNames = FilterFilesForActivityLogFormat(csvFileNames);

	if (filteredCsvFileNames.empty())
	{
		throw runtime_error("File Error: No CSV files exist that match the format 'LastnameFirstnameLog.csv' in the folder.");
	}

	const int ONLY_ONE_CSV_FILE_ALLOWED = 1;

	if (filteredCsvFileNames.size() != ONLY_ONE_CSV_FILE_ALLOWED)
	{
		string errContent;
		for(const string& fileName : csvFileNames)
		{ 
			errContent += fileName + "\n";
		}
		throw std::runtime_error("File Error: Multiple CSV files exist that match the format 'LastnameFirstnameLog.csv' in your folder.\n"
			"Matching Files:\n" + errContent + "\n");
	}
	string csvFileName = filteredCsvFileNames.front();

	ParseLogData(csvFileName);

	return csvFileName;
}
//Action: parses all the rows in the user's csv file
//Parameter: logFileName (string) is file name of activity log 
void ActivityLogger::ParseLogData(string logFileName)
{

	ifstream file(logFileName);
	
	if (file.is_open() == false) {
		throw runtime_error("File Error: Could not open the CSV file.");
	}
	
	const int REQUIRED_AMOUNT_OF_ROWS = 1;

	string row;

	int rowCounter = 0;

	while (getline(file, row)) {
		vector<string> cells;
		stringstream streamForRow(row);
		string cell;

		
		while (getline(streamForRow, cell, ',')) {
			cells.push_back(cell);
		}

		ValidateCellCountInCsvRow(cells.size(), rowCounter);

		if (rowCounter <= REQUIRED_AMOUNT_OF_ROWS)
		{
			StoreLogHeaderDetails(cells, rowCounter);
		}
		
		rowCounter++;
	}

	if (rowCounter <= REQUIRED_AMOUNT_OF_ROWS)
	{
		throw runtime_error("Incorrect Csv File Format Error: " + logFileName + " CSV file is required to have at least two rows. The first row for first and last name (lastName in the first cell and firstName in the second cell)" +
			" and the second row for the Class ID (in the first cell).");
	}

	file.close();

	return;
}
//Action: validates that the csv row sizes are correct. must be between 5 and 6 cells. normally length 5 cells, but can be 6 cells if user added a note to an entry
//Parameter: amountOfCells (int) is amount of cells in a csv row 
//Parameter: rowNumber (int) is the row number in the csv file we are on.
void ActivityLogger::ValidateCellCountInCsvRow(int amountOfCells, int rowNumber)
{
	const int MAX_AMOUNT_OF_CELLS = 6;
	const int MIN_AMOUNT_OF_CELLS = 5;
	if (amountOfCells > MAX_AMOUNT_OF_CELLS)
	{
		throw runtime_error("Incorrect Csv File Format Error: Row " + to_string(rowNumber + 1) +
			" has too many cells. Six cells is the limit.");
	}

	if (amountOfCells < MIN_AMOUNT_OF_CELLS)
	{
		throw runtime_error("Incorrect Csv File Format Error: Row " + to_string(rowNumber + 1) +
			" has too few cells. Five cells is the requirement.");
	}
	return;
}
//Action: if we are on the first row, we can get the user's name. if we are on the second row we can get the class id
//Parameter: cells (vector<string>) is an array of all the cells in a row in the csv file
//Parameter: rowNumber (int) is the row number in the csv file we are on.
void ActivityLogger::StoreLogHeaderDetails(vector<string> cells, int rowNumber)
{

	const int LASTNAME_CELL_INDEX = 0;
	const int FIRSTNAME_CELL_INDEX = 1;
	const int CLASS_ID_CELL_INDEX = 0;
	const int FIRST_CSV_ROW = 0;
	const int SECOND_CSV_ROW = 1;

	if (rowNumber == FIRST_CSV_ROW)
	{
		if (cells[LASTNAME_CELL_INDEX].empty())
		{
			throw runtime_error("Incorrect Csv File Format Error: Missing LastName in your Activity Log on row 1 and at cell 1.");
		}

		if (cells[FIRSTNAME_CELL_INDEX].empty())
		{
			throw runtime_error("Incorrect Csv File Format Error: Missing FirstName in your Activity Log on row 1 and at cell 2.");
		}

		StoreValidName(cells[FIRSTNAME_CELL_INDEX], cells[LASTNAME_CELL_INDEX]);
	}
	if (rowNumber == SECOND_CSV_ROW)
	{
		if (cells[CLASS_ID_CELL_INDEX].empty())
		{
			throw runtime_error("Incorrect Csv File Format Error: Missing Class ID in your Activity Log on row 2 and at cell 1.");
		}
		
			StoreValidClassID(cells[CLASS_ID_CELL_INDEX]);
		
	}

}
//Action: Stores Class Id in classes ClassID property
void ActivityLogger::StoreValidClassID(string id)
{
	ClassID = id;
}
//Action: Stores first and last names in classes LogOwnerFirstName and LogOwnerLastName property
//Parameter: fname (string) first name found in the csv file header
//Parameter: lname (string) last name found in the csv file header
void ActivityLogger::StoreValidName(string fname, string lname)
{
		LogOwnerFirstName = fname;
		LogOwnerLastName = lname;
}
//Action: looks at all the csv files in the folder for files that match are desired 'LastnameFirstnameLog.csv' format
//Parameter: fileNames (vector<string>), list of all csv file names in the folder
//Return: a vector list of all the csv files that match the format 'LastnameFirstnameLog.csv'
vector<string> ActivityLogger::FilterFilesForActivityLogFormat(vector<string> fileNames)
{
	vector<string> results;

	for (string& fileName : fileNames) {
		fileName = fileName.substr(0, fileName.size() - 4);//this is just removing the .csv ext
	}

	regex csvFileActivityLogPattern(R"(^[A-Z][a-zA-Z]*[A-Z][a-zA-Z]*Log$)");

	for (const string& fileName : fileNames) {
		if (regex_match(fileName, csvFileActivityLogPattern))
		{
			results.push_back(fileName + ".csv");
		}
	}

	return results;
}
//Action: get all the csv files in the folder 
//Return: a vector list of all the csv files in the folder 
//Adapted From: https://www.geeksforgeeks.org/cpp-program-to-get-the-list-of-files-in-a-directory/
vector<string> ActivityLogger::FetchAllCsvFileNamesInFolder()
{

	const string CSV_EXTENSION = ".csv";

	vector<string> results;

	path pathOfCurrentFolder = current_path();

	for (const auto& file : directory_iterator(pathOfCurrentFolder)) {
		if (file.path().extension() == CSV_EXTENSION) {
			
			string fileName = file.path().filename().string();

			results.push_back(fileName);
		}
	}

	return results;
}
//Action: getter for LogOwnerFirstName
//Return: user's first name
string ActivityLogger::GetFirstNameOfLogOwner() 
{
	return LogOwnerFirstName;
}
//Action: getter for LogOwnerLastName
//Return: user's last name
string ActivityLogger::GetLastNameOfLogOwner() 
{
	return LogOwnerLastName;
}
//Action: getter for ClassID
//Return: class id associated with activity log
string ActivityLogger::GetClassID() 
{
	return ClassID;
}
//Action: getter for ClassID
//Return: name of activity log csv file
string ActivityLogger::GetFileName()
{
	return LogFile;
}