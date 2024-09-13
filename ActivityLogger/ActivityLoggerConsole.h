#pragma once
#include "ActivityLogger.h"
#include <string>
//wrapper around logger. Controls console input/output for logging.
class ActivityLoggerConsole
{
public:
	//instance of Activity Logger
	ActivityLogger logger;
	//Action: Prints the heading of the csv log file (student name and class Id)
	void WriteLogFileHeader();
	//Action: Prints the heading of the csv log file (student name and class Id)
	//Parameter: newLogRows (string) that represents the new rows (logs) that have been added to the file as the program ran
	void WriteResults(string newLogRows);
	//Action: Controls the process of starting the timer and waiting for the user to end the timer via cin.ignore
	void TimeEventHandler();
	//Action: Controls access to requesting for valid note input from user
	void NoteEntryHandler();
	//Action: Controls access to requesting for valid amount of people input from user
	void GroupSizeHandler();
	//Action: Controls access to requesting for valid activity code input from user
	void ActivityTypeHandler();
	//Action: Adds newly created activity logs to the csv file
	void LogActivity();

private:
	//Action: Outputs a table to the console that defines the meaning of each activity code
	//Action:Also asks the user to enter a activity code
	void WriteActivityMenu();
	//Action: output to ask user to enter a number for amount of people that worked with them on the activity
	void WriteAmountOfPeopleRequest();
	//Action: output to ask user if they want to write or note. (or if they have to if activity is other)
	void WriteNoteRequest();
	//Action: asks user if they are sure they are finished working on their activity.
	void WriteTimeFinishRequest();
	//Action: reads string input from user as line.
	//Return: returns a string read from console input
	string ReadString();
	//Action: reads input from user for 'Y' or 'N'. Y if user is done with their activity and N if not
	void ContinueTimingHandler();
	//Action: reads character input from user.
	//Return: returns a single character read from console input
	char ReadCharacter();
	//Action: outputs the time the activity began at
	void WriteStartTime(string time);
	//Action: outputs the time the activity ended at
	void WriteEndTime(string time);
	
	//contains a response message after an attempt to store the input the user provided into the Activity Log
	string consoleReadResult;

	//is compared to consoleReadResult, if consoleReadResult equals successfulRead, the user input is valid
	const string successfulRead = LogEntry::SUCCESSFUL_SET_MESSAGE;
};

