#include "ActivityLoggerConsole.h"
#include <iostream>
using namespace std;
//Action: Controls the process of starting the timer and waiting for the user to end the timer via cin.ignore
void ActivityLoggerConsole::TimeEventHandler()
{
  string sTime = logger.AccessCurrentTime();
  WriteStartTime(sTime);
  logger.ActivityEntry.SetTimeStart(sTime);
  logger.ActivityEntry.SetDateStart(logger.AccessCurrentDate());

  ContinueTimingHandler();

  string eTime = logger.AccessCurrentTime();
  WriteEndTime(eTime);
  logger.ActivityEntry.SetTimeEnd(eTime);
  logger.ActivityEntry.SetDateEnd(logger.AccessCurrentDate());
}
//Action: reads input from user for 'Y' or 'N'. Y if user is done with their activity and N if not
void ActivityLoggerConsole::ContinueTimingHandler()
{
  char yesOrNoChar;
  const char YES = 'Y';
  const char NO = 'N';
  do {

    WriteTimeFinishRequest();

    yesOrNoChar = ReadCharacter();
    yesOrNoChar = toupper(yesOrNoChar);

    if (yesOrNoChar != 'Y' && yesOrNoChar != 'N')
    {
      cout << "Please Enter A 'y' or 'n' or 'Y' or 'N'\n" << endl;
    }
    if (yesOrNoChar == 'N')
    {
      cout << "Press Enter When You Finish.\n" << endl;
      cin.ignore();
    }
  } while (yesOrNoChar != 'Y');

}
//Action: Controls access to requesting for valid note input from user
void ActivityLoggerConsole::NoteEntryHandler()
{
  WriteNoteRequest();

  do {
    string note = ReadString();
    consoleReadResult = logger.ActivityEntry.SetNote(note);

    if (consoleReadResult != successfulRead) {
      cout << consoleReadResult << endl;
      cout << "Please Enter A Note: " << endl;
    }


  } while (consoleReadResult != successfulRead);
}
//Action: Controls access to requesting for valid amount of people input from user
void ActivityLoggerConsole::GroupSizeHandler()
{
  WriteAmountOfPeopleRequest();

  do {
    string groupSize = ReadString();
    consoleReadResult = logger.ActivityEntry.SetGroupSize(groupSize);

    if (consoleReadResult != successfulRead) {
      cout << consoleReadResult << endl;
      cout << "Please Enter A Number Again For Amount Of People: " << endl;
    }
  } while (consoleReadResult != successfulRead);
}
//Action: Controls access to requesting for valid activity code input from user
void ActivityLoggerConsole::ActivityTypeHandler() {

  WriteActivityMenu();

  do {
    char keyCode = ReadCharacter();
    consoleReadResult = logger.ActivityEntry.SetActivityType(keyCode);

    if (consoleReadResult != successfulRead) {
      cout << consoleReadResult << endl;
      cout << "Please Enter A Correct Activity Code Character: " << endl;
    }
  } while (consoleReadResult != successfulRead);
}
//Action: Prints the heading of the csv log file (student name and class Id)
  //Parameter: newLogRows (string) that represents the new rows (logs) that have been added to the file as the program ran
void ActivityLoggerConsole::WriteResults(string newLogRows)
{
  cout << "\n New Logs Added to " + logger.GetFileName() + ":\n" << endl;

  cout << newLogRows << endl;

  cout << "\n\nCongrats On All The Work You Completed! I Hope You Enjoyed Doing Your Activity!\n\n\n\n\n" << endl;
}
//Action: asks user if they are sure they are finished working on their activity.
void ActivityLoggerConsole::WriteTimeFinishRequest()
{
  cout << "Are You Sure You are Done With Your Activity?\n" << endl;
  cout << "Enter 'N' To Confim You Want To Continue Doing The Activity.\n" << endl;
  cout << "Enter 'Y' To Confirm You Are Done Doing The Activity. If So, The Activity Will Automatically Be Logged To Your CSV File For You.\n" << endl;
}
//Action: Prints the heading of the csv log file (student name and class Id)
void ActivityLoggerConsole::WriteLogFileHeader()
{
  string userFullName = logger.GetFirstNameOfLogOwner() + " " + logger.GetLastNameOfLogOwner();

  cout << "\nActivity Log\n" << endl;
  cout << "For User: " + userFullName + ".\n" << endl;
  cout << "In Class: " + logger.GetClassID() +".\n" << endl;
}
//Action: reads character input from user.
//Return: returns a single character read from console input
char ActivityLoggerConsole::ReadCharacter()
{
  char key;
  cin >> key;
  cin.ignore();
  return key;
}
//Action: reads string input from user as line.
//Return: returns a string read from console input
string ActivityLoggerConsole::ReadString()
{
  string str;

  std::getline(cin, str);

  return str;
}
//Action: outputs the time the activity began at
void ActivityLoggerConsole::WriteStartTime(string time)
{
  cout << "\n Your Activity '" + logger.ActivityEntry.GetActivityName() + "' Has Begun At " 
    << logger.AccessCurrentDate() << " " << time + ".\n" << endl;

  cout << "Please Press Enter In This Console When You Are Done.\n" << endl;
}
//Action: outputs the time the activity ended at
void ActivityLoggerConsole::WriteEndTime(string time)
{
  cout << "\n Your Activity '" + logger.ActivityEntry.GetActivityName() + "' Has Ended At "
    << logger.AccessCurrentDate() << " " << time + ".\n" << endl;
}
//Action: output to ask user to enter a number for amount of people that worked with them on the activity
void ActivityLoggerConsole::WriteAmountOfPeopleRequest()
{
  cout << "\nEnter The Amount Of People In Your Group.\n" << endl;
}
//Action: output to ask user if they want to write or note. (or if they have to if activity is other)
void ActivityLoggerConsole::WriteNoteRequest()
{
  cout << "\nEnter A Note Describing Your Activity.\n" << endl;
  cout << "Required: This Is Required If Your Activity Is 'Other'.\n" << endl;
  cout << "Optional: This Is Optional If Your Activity Is Not 'Other'.\n" << endl;
  cout << "Please Type Nothing And Just Press Enter If You Do Not Want To Write A Note.\n" << endl;
}
//Action: Adds newly created activity logs to the csv file
void ActivityLoggerConsole::LogActivity()
{
  string addedLogs = logger.LogActivity();

  WriteResults(addedLogs);
}
//Action: Outputs a table to the console that defines the meaning of each activity code
//Action:Also asks the user to enter a activity code
void ActivityLoggerConsole::WriteActivityMenu()
{
  const int CODE_COLUMN_WIDTH = 3;
  const int NAME_COLUMN_WIDTH = 83;

  cout << "Please Choose An Activity.\n" << endl;
  cout << "To Select An Activity Enter The Single Character Key Associated With The Activity You Want To Do.\n" << endl;
  cout << " " << string(CODE_COLUMN_WIDTH, '-') << string(NAME_COLUMN_WIDTH + 7, '-') << endl;
  cout << " | " << left << setw(CODE_COLUMN_WIDTH) << "Key" << " | " << left << setw(NAME_COLUMN_WIDTH) << "Activity Type" << " | " << endl;
  cout << " | " << string(CODE_COLUMN_WIDTH, '-') << " | " << string(NAME_COLUMN_WIDTH, '-') << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::ReadTextbookOrCanvas)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Reading Canvas site or textbook" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::StudyPracticeQuiz)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Studying using a practice quiz" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::TakeScoringQuiz)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Taking a scoring quiz" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::CanvasDiscussion)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Participating in a Canvas discussion, DX" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::TeamMeeting)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Meeting with your team" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::DocumentationWork)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Working on documentation" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::WorkOnDesigns)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Working on designs" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::Programming)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Programming" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::ProgramTestingOrTestPlan)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Working on a test plan or doing testing" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::StudyForExam)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Studying for the final exam" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::ProfessorMeeting)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Conferring with the instructor (outside team meeting)" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::MiniLectureTask)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Working on a mini-lecture video or reading" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::ReadOrWatchOutsideContent)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Viewing a video or website that is not a mini - lecture, but relevant to the course" << " | " << endl;
  cout << " |  " << setw(CODE_COLUMN_WIDTH - 1) << static_cast<char>(Activity::Other)
    << " | " << left << setw(NAME_COLUMN_WIDTH) << "Other" << " | " << endl;
  cout << " " << string(CODE_COLUMN_WIDTH, '-') << string(NAME_COLUMN_WIDTH + 7, '-') << endl;
  cout << endl;

  return;
}
