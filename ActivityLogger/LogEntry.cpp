#include "LogEntry.h"
#include <iostream>
#include <regex>
using namespace std;
//Action: contstructor initalizes Log Entry entity.
LogEntry::LogEntry()
{
	DateEnd = "";
	DateStart = "";
	TimeEnd = "";
	TimeStart = "";
	GroupSize = 0;
	ActivityType = Activity::None;
	Note = "";
}
//Action: creates an error message, if a set property method fails
//Parameter: msg (string) error message
//Return: fill error message
string LogEntry::FailedSetMessage(string msg)
{
	return "FAILED. Sorry, " + msg + "\n";
}
//Action: takes an a log entry in splits into two by copying it into this log entry. 
//Action: also this only happens when a log entry spans past midnight. similiar to a copy constructor
//Parameter: originalLog (LogEntry) log entry we want to copy
void LogEntry::SplitFrom(LogEntry originalLog)
{
	DateEnd = originalLog.DateEnd;
	DateStart = originalLog.DateEnd;
	TimeStart = "00:00";
	TimeEnd = originalLog.TimeEnd;
	GroupSize = originalLog.GroupSize;
	ActivityType = originalLog.ActivityType;
	Note = originalLog.Note;
}
// Action: checks to see if log entry has empty data
//Returns: true if log entry has empty data
bool LogEntry::Empty()
{
	if (DateStart.empty() || DateEnd.empty() || TimeEnd.empty() || TimeStart.empty() || GroupSize == 0 || ActivityType == Activity::None)
	{
		return true;
	}
	return false;
}
// Action: getter for DateEnd
//Returns: DateEnd property (string)
string LogEntry::GetDateEnd() {
	return DateEnd;
}
// Action: getter for DateStart
//Returns: DateStart property (string)
string LogEntry::GetDateStart() {
	return DateStart;
}
// Action: getter for TimeStart
//Returns: TimeStart property (string)
string LogEntry::GetTimeStart() {
	return TimeStart;
}
// Action: getter for TimeEnd
//Returns: TimeEnd property (string)
string LogEntry::GetTimeEnd() {
	return TimeEnd;
}
// Action: getter for GroupSize
//Returns: GroupSize property (int)
int LogEntry::GetGroupSize() {
	return GroupSize;
}
// Action: getter for ActivityType code
//Returns: ActivityType property (char)
char LogEntry::GetActivityType() {
	return static_cast<char>(ActivityType);
}
// Action: getter for note
//Returns: Note property (string)
string LogEntry::GetNote() {
	return Note;
}
// Action: setter for date ended
//Parameter: date in mm/dd/yyyy format (string)
void LogEntry::SetDateEnd(string date)
{
	if (ValidateDate(date) == false)
	{
		throw runtime_error("Error: Attempted To Set Start Time With Invalid Date Format: " + date + ". Time Format Must Be MM/DD/YYYY");
	}
	DateEnd = date;
}
// Action: setter for date started
//Parameter: date in mm/dd/yyyy format (string)
void LogEntry::SetDateStart(string date)
{
	if (ValidateDate(date) == false)
	{
		throw runtime_error("Error: Attempted To Set Start Time With Invalid Date Format: " + date + ". Time Format Must Be MM/DD/YYYY");
	}
	DateStart = date;
}
// Action: setter for time start
//Parameter: time in HH:MM format (string)
void LogEntry::SetTimeStart(string time)
{
	if (ValidateTime(time) == false)
	{
		throw runtime_error("Error: Attempted To Set Start Time With Invalid Time Format: " + time + ". Time Format Must Be HH:SS");
	}

	TimeStart = time;
}
// Action: setter for time ended
//Parameter: time in HH:MM format (string)
void LogEntry::SetTimeEnd(string time)
{
	if(ValidateTime(time) == false)
	{
		throw runtime_error("Error: Attempted To Set End Time With Invalid Time Format: " + time + ". Time Format Must Be HH:SS");
	}

	TimeEnd = time;
}
// Action: validates date format, must be mm/dd/yyyy and numerics must be logical as seen in regex
//Parameter: date (string)
bool LogEntry::ValidateDate(string date) {

	std::regex monthDayYearFormat("^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/(19|20)\\d{2}$");


	if (regex_match(date, monthDayYearFormat))
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Action: validates time format, must be hh:mm and numerics must be logical as seen in regex
//Parameter: time (string)
bool LogEntry::ValidateTime(string time) {

	regex hourMinuteFormat("^([0-1][0-9]|2[0-3]):([0-5][0-9])$");

	if (regex_match(time, hourMinuteFormat)) {
		return true; 
	}
	else {
		return false; 
	}
}
// Action: validates time format, must be hh:mm and numerics must be logical as seen in regex
//Parameter: time (string)
string LogEntry::SetActivityType(char activityCode)
{
	char copyOfOriginalCode = activityCode;
	if (isCharacterADigit(activityCode) == false)
	{
		activityCode = toupper(activityCode);
	}

	if (ValidateActivityCode(activityCode) == false)
	{
		return FailedSetMessage("Activity Code '" + string(1, copyOfOriginalCode) + "' Is Invalid.");
	}

	ActivityType = static_cast<Activity>(activityCode);

	return SUCCESSFUL_SET_MESSAGE;

}
//Action: converts Activity code into a title string representing what the activity is.
//Return: returns name of Activity (string)
string LogEntry::GetActivityName()
{
	switch (ActivityType)
	{
	case Activity::ReadTextbookOrCanvas:
		return "Reading Textbook or Canvas";
	case Activity::StudyPracticeQuiz:
		return "Studying Practice Quiz";
	case Activity::TakeScoringQuiz:
		return "Taking Scoring Quiz";
	case Activity::CanvasDiscussion:
		return "Canvas Discussion";
	case Activity::TeamMeeting:
		return "Team Meeting";
	case Activity::DocumentationWork:
		return "Documentation Work";
	case Activity::WorkOnDesigns:
		return "Working on Designs";
	case Activity::Programming:
		return "Programming";
	case Activity::ProgramTestingOrTestPlan:
		return "Program Testing or Test Plan Making";
	case Activity::StudyForExam:
		return "Studying for Exam";
	case Activity::ProfessorMeeting:
		return "Instructor Meeting";
	case Activity::MiniLectureTask:
		return "Mini Lecture Or Reading Task";
	case Activity::ReadOrWatchOutsideContent:
		return "Reading or Watching Outside Relevant Content";
	case Activity::Other:
		return "Other";
	default:
		return "Unknown Activity";
	}
}
//Action: Validates if Activity code from user input is legit
//Parameter: character representing a potential activity code
//Return: true if Activity code is between 0 and D (hex)
bool LogEntry::ValidateActivityCode(char code)
{

	switch (code)
	{
	case static_cast<char>(Activity::ReadTextbookOrCanvas):
	case static_cast<char>(Activity::StudyPracticeQuiz):
	case static_cast<char>(Activity::TakeScoringQuiz):
	case static_cast<char>(Activity::CanvasDiscussion):
	case static_cast<char>(Activity::TeamMeeting):
	case static_cast<char>(Activity::DocumentationWork):
	case static_cast<char>(Activity::WorkOnDesigns):
	case static_cast<char>(Activity::Programming):
	case static_cast<char>(Activity::ProgramTestingOrTestPlan):
	case static_cast<char>(Activity::StudyForExam):
	case static_cast<char>(Activity::ProfessorMeeting):
	case static_cast<char>(Activity::MiniLectureTask):
	case static_cast<char>(Activity::ReadOrWatchOutsideContent):
	case static_cast<char>(Activity::Other):
		return true;
	default:
		return false;
	}
}
//Action: checks if a character is a digit (0-9)
//Parameter: character 
//Return: true if char is between 0 and 9 (digit)
bool LogEntry::isCharacterADigit(char character)
{
	int asciiValueForCharacter = static_cast<int>(character);

	const int ASCII_DIGIT_0 = 48;
	const int ASCII_DIGIT_9 = 57;
	if (asciiValueForCharacter < ASCII_DIGIT_0 || asciiValueForCharacter > ASCII_DIGIT_9)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//Action: checks if amount of people value is between (1-50)
//Parameter: amountOfPeople (int) from user input 
//Return: true if between 1 and 50 
bool LogEntry::ValidateGroupSize(int amountOfPeople)
{
	const int MIN_AMOUNT_OF_PEOPLE = 1;
	const int MAX_AMOUNT_OF_PEOPLE = 50;

	if (amountOfPeople < MIN_AMOUNT_OF_PEOPLE || amountOfPeople > MAX_AMOUNT_OF_PEOPLE)
	{
		return false;
	}
	else
	{
		return true;
	}

}
//Action: setter for group size property that represents amount of people in activity
//Parameter: amountOfPeople (string) from user input 
//Return: string message reporting success or failure of set operation
string LogEntry::SetGroupSize(string amountOfPeople)
{

	int size;

	try {
		
		size = std::stoi(amountOfPeople);
		
		if (ValidateGroupSize(size) == false)
		{
			throw std::out_of_range("Group Size Has To Be Between 1 - 50");
		}

	}
	catch (const std::invalid_argument& e) {
		return FailedSetMessage("You Entered Text Instead Of A Number!");
	}
	catch (const std::out_of_range& e) {
		return FailedSetMessage("The Amount Of People In A Group Is 1 - 50 People. Please Enter A Realistic Number!");
	}

	GroupSize = size;

	return SUCCESSFUL_SET_MESSAGE;
}
//Action: setter for note property that represents possible note in activity
//Parameter: note (string) from user input 
//Return: string message reporting success or failure of set operation
string LogEntry::SetNote(string note)
{
	if (IsNoteRequired())
	{
		if (ValidateIfRequiredNoteEmpty(note))
		{
			return FailedSetMessage("Since The Activity You Are Doing Is 'Other', You Must Enter In A Note To Describe What You Are Doing!");
		}
	}

	if (ValidateNoteSizeLimit(note) == false)
	{
		return FailedSetMessage("Note Size Limit Is 80 Characters!");
	}

	if (ValidateNoteContent(note) == false)
	{
		return FailedSetMessage("Note Cannot Contain Commas! A Comma is a ',' character.");
	}

	Note = note;
	
	return SUCCESSFUL_SET_MESSAGE;
}
//Action: checks if note is empty, if any white space replace it with empty strings, becuase all whitespace notes are still considered empty
//Parameter: note (string) from user input 
//Return: true if note is empty
bool LogEntry::ValidateIfRequiredNoteEmpty(string note)
{
	string noteWithNoWhiteSpace = regex_replace(note, regex("\\s+"), "");
	
	if (noteWithNoWhiteSpace.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//Action: checks if note has any commas to prevent messing with the csv file
//Parameter: note (string) from user input 
//Return: true if no commas in note
bool LogEntry::ValidateNoteContent(string note)
{
	if (note.find(',') != string::npos) {
		return false;
	}
	else {
		return true;
	}
}
//Action: checks if note is too big (length)
//Parameter: note (string) from user input 
//Return: true if note size greater than 80 character
bool LogEntry::ValidateNoteSizeLimit(string note)
{
	const int SIZE_LIMIT = 80;

	if (note.size() > SIZE_LIMIT)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//Action: checks if note is required
//Return: true if activity code is Other
bool LogEntry::IsNoteRequired()
{
	if (ActivityType == Activity::Other)
	{
		return true;
	}
	else
	{
		return false;
	}
}