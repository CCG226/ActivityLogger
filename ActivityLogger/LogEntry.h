#include <string>
#include "ActivityEnum.h"
#pragma once
using namespace std;


class LogEntry
{
public:
	//Action: contstructor initalizes Log Entry entity.
	LogEntry();

	//comparable string. used to check if a LogEntry property set was successful
	inline static const string SUCCESSFUL_SET_MESSAGE = "SUCCESS";
	// Action: getter for DateStart
//Returns: DateStart property (string)
	string GetDateStart();
	// Action: getter for DateEnd
//Returns: DateEnd property (string)
	string GetDateEnd();
	// Action: getter for TimeStart
//Returns: TimeStart property (string)
	string GetTimeStart();
	// Action: getter for TimeEnd
//Returns: TimeEnd property (string)
	string GetTimeEnd();
	// Action: getter for GroupSize
//Returns: GroupSize property (int)
	int GetGroupSize();
	// Action: getter for ActivityType code
//Returns: ActivityType property (char)
	char GetActivityType();
	// Action: getter for note
//Returns: Note property (string)
	string GetNote();
	string GetActivityName();
	//Action: checks if note is required
//Return: true if activity code is Other
	bool IsNoteRequired();
	// Action: checks to see if log entry has empty data
//Returns: true if log entry has empty data
	bool Empty();
	// Action: setter for date started
//Parameter: date in mm/dd/yyyy format (string)
	void SetDateStart(string date);
	// Action: setter for date ended
//Parameter: date in mm/dd/yyyy format (string)
	void SetDateEnd(string date);
	// Action: setter for time start
//Parameter: time in HH:MM format (string)
	void SetTimeStart(string time);
	// Action: setter for time ended
//Parameter: time in HH:MM format (string)
	void SetTimeEnd(string time);
	//Action: setter for group size property that represents amount of people in activity
//Parameter: amountOfPeople (string) from user input 
//Return: string message reporting success or failure of set operation
	string SetGroupSize(string amountOfPeople);
	string SetActivityType(char activityCode);
	//Action: setter for note property that represents possible note in activity
//Parameter: note (string) from user input 
//Return: string message reporting success or failure of set operation
	string SetNote(string note);
	//Action: takes an a log entry in splits into two by copying it into this log entry. 
//Action: also this only happens when a log entry spans past midnight. similiar to a copy constructor
//Parameter: originalLog (LogEntry) log entry we want to copy
	void SplitFrom(LogEntry originalLog);

private:
	//Date activity was started
	string DateStart;
	//Date activity was ended
	string DateEnd;
	//time in hours/minutes activity was started
	string TimeStart;
	//time in hours/minutes activity was ended
	string TimeEnd;
	//amount of people the user worked with on this activity
	int GroupSize;
	//activity code
	Activity ActivityType;
	//note about activity
	string Note;

	//Action: creates an error message, if a set property method fails
//Parameter: msg (string) error message
//Return: fill error message
	string FailedSetMessage(string msg);
	// Action: validates time format, must be hh:mm and numerics must be logical as seen in regex
//Parameter: time (string)
	bool ValidateTime(string time);
	// Action: validates date format, must be mm/dd/yyyy and numerics must be logical as seen in regex
//Parameter: date (string)
	bool ValidateDate(string date);
	//Action: checks if amount of people value is between (1-50)
//Parameter: amountOfPeople (int) from user input 
//Return: true if between 1 and 50 
	bool ValidateGroupSize(int amountOfPeople);
	//Action: checks if note is too big (length)
//Parameter: note (string) from user input 
//Return: true if note size greater than 80 character
	bool ValidateNoteSizeLimit(string note);
	//Action: checks if note has any commas to prevent messing with the csv file
//Parameter: note (string) from user input 
//Return: true if no commas in note
	bool ValidateNoteContent(string note);
	//Action: Validates if Activity code from user input is legit
//Parameter: character representing a potential activity code
//Return: true if Activity code is between 0 and D (hex)
	bool ValidateActivityCode(char code);
	//Action: checks if a character is a digit (0-9)
//Parameter: character 
//Return: true if char is between 0 and 9 (digit)
	bool isCharacterADigit(char character);
	//Action: checks if note is empty, if any white space replace it with empty strings, becuase all whitespace notes are still considered empty
//Parameter: note (string) from user input 
//Return: true if note is empty
	bool ValidateIfRequiredNoteEmpty(string note);
	
};

