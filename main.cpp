// Brian Hoerner
// 30 Novemember 2020
// Event Planner
// This is an event planning software that operates as a standard calendar.
// Users can add, remove, and view events.


/***********************************ReWrite********************************/
// Below is a re-write to try and clean up the program and wrap my head
// around where I'm actually at in it, progress-wise.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// Global Constants
const int MONTHS = 12;
const int DAYS = 31;

// Main Function Prototypes
void displayMenu(bool [][DAYS], int [][DAYS], int [][DAYS], string [][DAYS], string [MONTHS]);
void loadUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS], bool &, bool &);
void saveUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS], bool, bool);
void removeEvent(bool [][DAYS], int eventHour[][DAYS], int [][DAYS], string [MONTHS], string [][DAYS]);

// Support Function Prototypes
void displayMonths();
void setLeapYear(int &, bool &);    // Checks for year, sets whether leap-year for February-related considerations
int hourConvert(int);
void getMeridian(int);

// Add Event Function Prototypes
int monthChoice();
int monthDaysCheck(int, bool);
int dayChoice(int);
int hourChoice();
int minuteChoice(int);
int saveChoice;
string getName();
void eventMake(// Arrays
               bool [][DAYS], int [][DAYS], int [][DAYS], string [MONTHS], string [][DAYS],
               // Variables
               int, int, int, int, string);

int main()
{
    // Arrays
    bool eventPresent[MONTHS][DAYS];
    int eventHour[MONTHS][DAYS];
    int eventMin[MONTHS][DAYS];
    string monthNames[MONTHS];
    string eventNames[MONTHS][DAYS];

    // Variables
    int userChoice;                 // Menu Selection
    int month, day, hour, minutes;  // Inform array assignment / lookup
    int dayCount;                   // Count of days in a month (28, 29, 30, 31)
    int year;                       // Informs setLeapYear

    bool leapYearSet = false;       // Whether a leap year has been set
    bool leapYear;                  // Whether it is or is not a leap year
    bool dummyStop;                 // Temp named variable for ending main menu
    bool unsavedChanges = false;    // Prompts user to save if they haven't before quitting

    string eventNameVar;            // Storage for event name in string variable

    // Load Month Names in from txt file before starting
    ifstream monthData;
    monthData.open("months.txt");
    for(int i = 0; i < MONTHS; i++)
    {
        monthData >> monthNames[i];
    }
    // monthData.close();

    do
    {
        cout << "\n\n----------------------------------Event Planner---------------------------------\n\n";
        cout << "Main Menu" << endl << endl;
        cout << "1. Add Event" << endl
             << "2. Remove Event" << endl
             << "3. Display Events" << endl
             << "4. Load Events" << endl
             << "5. Save Events" << endl << endl
             << "0. Quit" << endl << endl;
        cout << "Please choose from the items above (1-5, or 0 to Quit): ";

        while(!(cin >> userChoice) || userChoice < 0 || userChoice > 5)     //Get, validate userChoice
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }

        switch(userChoice)          // Main Menu options
        {
            case 1:
            {
                if(leapYearSet == false)
                {
                    setLeapYear(year, leapYear);
                    leapYearSet = true;
                }
                
                cout << "\n\n------------------------------------Add Event-----------------------------------\n\n\n";
                displayMonths();
                cout << "Please start by choosing a month for your event (1-12): ";

                month = monthChoice();
                dayCount = monthDaysCheck(month, leapYear);
                day = dayChoice(dayCount);
                hour = hourChoice();
                minutes = minuteChoice(hour);
                eventNameVar = getName();
                eventMake(// Arrays
                    eventPresent, eventHour, eventMin, monthNames, eventNames,
                    // Variables
                    month, day, hour, minutes, eventNameVar);
                unsavedChanges = true;
                break;
            }
            case 2:
            {
                removeEvent(eventPresent, eventHour, eventMin, monthNames, eventNames);
                break;
            }
            case 3: 
            {
                displayMenu(eventPresent, eventHour, eventMin, eventNames, monthNames);
                break;
            }
            case 4:
            {
                loadUserData(eventPresent, eventNames, eventHour, eventMin, leapYear, leapYearSet);
                break;
            }
            case 5:
            {
                saveUserData(eventPresent, eventNames, eventHour, eventMin, leapYear, unsavedChanges);
                break;
            }
            case 0:
                if(unsavedChanges == true)
                {
                    cout << "\n\n--------------------------------Unsaved Changes!--------------------------------\n\n\n";
                    cout << "1. Yes, Quit." << endl
                         << "2. No, stay in program." << endl << endl
                         << "You have unsaved changes. Are you sure you want to quit? ";
                    while(!(cin >> saveChoice) || saveChoice < 1 || saveChoice > 2)
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Please enter a valid option: ";
                    }
                    switch(saveChoice)
                    {
                        case 1: 
                            dummyStop = true;
                            break;
                        case 2: break;
                    }
                }
                else
                {
                    dummyStop = true;
                }
        }
    } while(dummyStop != true);
    monthData.close();              // Moving to the end of the program.
    cout << "\n\n------------------------------------Goodbye!------------------------------------\n\n";
    cout << "\nThank you for using this software!\n\n";
    return 0;
}

// Functions
void displayMonths()
{
    cout << setw(20) << left << "1. January" << setw(20) << "2. February" << setw(20) << "3. March" << setw(20) << "4. April" << endl
         << setw(20) << "5. May" << setw(20) << "6. June" << setw(20) << "7. July" << setw(20) << "8. August" << endl
         << setw(20) << "9. September" << setw(20) << "10. October" << setw(20) << "11. November" << setw(20) << "12. December"
         << endl << endl;
}
void setLeapYear(int &year, bool &leapYear)
{
    cout << "\n\n-----------------------------------Year Check-----------------------------------\n\n";
    cout << "\nPlease enter the year for this calendar: ";
    while(!(cin >> year) || year < 2020 || year > 2099)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    
    if(year % 4 == 0)
    {
        leapYear = true;
        return;
    }
    else
    {
        leapYear = false;
        return;
    }
    
}
void displayMenu(bool eventPresent[][DAYS], int eventHour[][DAYS], int eventMin[][DAYS],
                 string eventNames[][DAYS], string monthNames[MONTHS])
{
    int userChoice;
    int monthChoice;
    int eventCounter = 0;

    cout << "\n\n----------------------------------Display Menu----------------------------------\n\n";
    cout << "1. Display All Events" << endl
         << "2. Display Events by Month" << endl << endl
         << "0. Cancel" << endl << endl;
    cout << "Please enter your choice: ";

    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    switch(userChoice)
    {
        case 1:
        {
            cout << "\n\n-------------------------------Display All Events-------------------------------\n\n\n";
            for(int m = 0; m < MONTHS; m++)
            {
                for(int d = 0; d < DAYS; d++)
                {
                    if(eventPresent[m][d] == true)
                    {
                        cout << (eventCounter + 1) << ". " << eventNames[m][d] << " on " << monthNames[m]
                             << " " << (d + 1) << " at " << hourConvert(eventHour[m][d]) << ":" << setw(2)
                             << setfill('0') << eventMin[m][d] << " " << setfill(' ');
                        getMeridian(eventHour[m][d]);
                        cout << endl;
                        eventCounter++;
                    }
                }
            }
            if(eventCounter == 0)
                cout << "There are no events to display." << endl;
            eventCounter = 0;
            cout << "\nPress 'Enter' to return to Main Menu...\n";
            cin.get();
            break;
        }
        case 2:
        {
            cout << "\n\n-----------------------------Display Events By Month----------------------------\n\n\n";
            displayMonths();
            cout << "Which month would you like to display? (1-12, or 0 to Cancel): ";
            
            while(!(cin >> monthChoice) || monthChoice < 0 || monthChoice > 13)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter a valid option: ";
            }

            cout << "\n\n-----------------------------Display Events By Month----------------------------\n\n\n";

            for(int d = 0; d < DAYS; d++)
            {
                if(eventPresent[monthChoice - 1][d])
                {
                    cout << (eventCounter + 1) << ". " << eventNames[monthChoice -1][d] << " on "
                         << monthNames[monthChoice - 1] << " " << (d + 1) << " at "
                         << hourConvert(eventHour[monthChoice - 1][d]) << ":" << setw(2)
                         << setfill('0') << eventMin[monthChoice - 1][d] << setfill(' ') << " ";
                    getMeridian(eventHour[monthChoice - 1][d]);
                    cout << endl;
                    eventCounter++;
                }
            }
            if(eventCounter == 0)
                cout << "There are no events to display for this month." << endl;
            eventCounter = 0;
            break;
        }
        case 0: break;
    }
    return;
}

int hourConvert(int hour)
{
    if(hour > 12)
    {
        hour -= 12;
    }
    return hour;
}

void getMeridian(int hour)
{
    if(hour < 12)
    {
        cout << "AM";
    }
    else
    {
        cout << "PM";
    }
    return;
}

void loadUserData(bool eventPresent[][DAYS], string eventNames[][DAYS],
                  int eventHour[][DAYS], int eventMin[][DAYS], bool &leapYear, bool &leapYearSet)
{
    int userChoice;
    string line;

    // Establish ifstream objects
    ifstream readEventPresent, readEventName, readEventHour, readEventMin, readLeapYear;

    // Open associated text files
    readEventPresent.open("eventPresent.txt");
    readEventName.open("eventName.txt");
    readEventHour.open("eventHour.txt");
    readEventMin.open("eventMin.txt");
    readLeapYear.open("leapYear.txt");

    cout << "\n\n------------------------------------Load Data-----------------------------------\n\n";
    cout << "1. Load Data" << endl
         << "2. Cancel" << endl << endl;
    cout << "Would you like to load your calendar data? (1-2): " << endl;

    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    switch(userChoice)
    {
        case 1:
        {
            for(int m = 0; m < MONTHS; m++)
            {
                for(int d = 0; d < DAYS; d++)
                {
                    readEventPresent >> eventPresent[m][d];
                    readEventHour >> eventHour[m][d];
                    readEventMin >> eventMin[m][d];
                    getline(readEventName, line);
                    eventNames[m][d] = line;
                    readLeapYear >> leapYear;
                }
            }
            leapYearSet = true;
            readEventPresent.close();
            readEventName.close();
            readEventHour.close();
            readEventMin.close();
            readLeapYear.close();
            break;
        }
        case 2: break;
    }
    return;
}

void saveUserData(bool eventPresent[][DAYS], string eventNames[][DAYS],
                  int eventHour[][DAYS], int eventMin[][DAYS], bool leapYear, bool unsavedChanges)
{
    int userChoice;

    ofstream writeEventPresent, writeEventName, writeEventHour, writeEventMin, writeLeapYear;

    writeEventPresent.open("eventPresent.txt");
    writeEventName.open("eventName.txt");
    writeEventHour.open("eventHour.txt");
    writeEventMin.open("eventMin.txt");
    writeLeapYear.open("leapYear.txt");

    cout << "\n\n------------------------------------Save Data-----------------------------------\n\n";
    cout << "1. Save Data" << endl
         << "2. Cancel" << endl << endl;
    cout << "Would you like to save your calendar data? (1-2)" << endl;
    cout << "(This will overwrite ALL previous data): ";
    
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 2)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }

    switch(userChoice)
    {
        case 1:
        {
            for(int m = 0; m < MONTHS; m++)
            {
                for(int d = 0; d < DAYS; d++)
                {
                    writeEventPresent << eventPresent[m][d] << endl;
                    writeEventHour << eventHour[m][d] << endl;
                    writeEventMin << eventMin[m][d] << endl;
                    writeEventName << eventNames[m][d] << endl;
                    writeLeapYear << leapYear << endl;
                }
            }
            writeEventPresent.close();
            writeEventName.close();
            writeEventHour.close();
            writeEventMin.close();
            writeLeapYear.close();
            
            cout << "Data saved! Press 'Enter' to continue...";
            cin.get();
            unsavedChanges = false;
            break;
        }
        case 2: break;
    }
    return;
}

// Add Event Functions
int monthChoice()
{
    int userChoice;

    while(!(cin >> userChoice || userChoice < 1 || userChoice > 12))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

int monthDaysCheck(int month, bool leapYear)
{
    int daysCount;
    if(month == 2)
    {
        if(leapYear)
        {
            daysCount = 29;
        }
        else
        {
            daysCount = 28;
        }
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
        daysCount = 30;
    }
    else
    {
        daysCount = 31;
    }
    return daysCount;
    
}

int dayChoice(int dayCount)
{
    cout << "\nOn what day does your event occur? ";
    int userChoice;

    while(!(cin >> userChoice) || userChoice < 1 || userChoice > dayCount)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

int hourChoice()
{
    int userChoice;
    cout << "\nAt what hour does your event occur?" << endl
         << "\nPlease enter the hour in 24-hour format (military time) and" << endl
         << "the software will convert it to AM/PM for you: ";
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 23)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

int minuteChoice(int hour)
{
    int userChoice;
    cout << "\nIs there a more specific time? " << hourConvert(hour) << ":15? "
         << hourConvert(hour) << ":30? etc..." << endl << endl;
    cout << "Please add minutes: ";

    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 59)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

string getName()
{
    string eventName;
    cout << "\nPlease enter the name of your event: ";
    cin.ignore();
    getline(cin, eventName);
    return eventName;
}

void eventMake(// Arrays
               bool eventPresent[][DAYS], int eventHour[][DAYS], int eventMin[][DAYS],
               string monthNames[MONTHS], string eventNames[][DAYS],
               // Variables
               int month, int day, int hour, int minutes, string eventNameVar)
{
    cout << "\n\n---------------------------------Event Scheduled--------------------------------\n\n";
    cout << "\nYour event, " << eventNameVar << ", is scheduled for\n";
    cout << monthNames[month - 1] << " " << day << ", at ";
    cout << hourConvert(hour);
    cout << ":" << setw(2) << setfill('0') << minutes << setfill(' ') << " ";
    getMeridian(hour);
    cout << ". \n\nPress 'Enter' to return to the Main Menu...Don't forget to save!";
    cin.get();

    // Putting everything away
    eventPresent[month - 1][day - 1] = true;
    eventNames[month - 1][day - 1] = eventNameVar;
    eventHour[month - 1][day - 1] = hour;
    eventMin[month - 1][day - 1] = minutes;

    //Clear variables for next time
}

void removeEvent(// Arrays
               bool eventPresent[][DAYS], int eventHour[][DAYS], int eventMin[][DAYS],
               string monthNames[MONTHS], string eventNames[][DAYS]//,
               // Variables
               //int month, int day, int hour, int minutes, string eventNameVar
               )
{
    int userChoice;
    int eventAccumulator = 0;
    int eventCounter = 0;
    int removalCounter = 0;

    cout << "\n\n----------------------------------Remove Event----------------------------------\n\n";
    displayMonths();
    cout << "In which month is the event you want to remove? (1-12 or 0 to Cancel): ";
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 12)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    cout << endl;
    
    for(int d = 0; d < DAYS; d++)
        {
            if(eventPresent[userChoice - 1][d])
            {
                eventAccumulator++;
            }
        }
    if(eventAccumulator == 0)
    {
        cout << "\nYou don't have any events in this month." << endl
             << "Press 'Enter' to return to the Main Menu...";
        cin.get();
        return;
    }

    int month = userChoice;
    for(int d = 0; d < DAYS; d++)
        {
            if(eventPresent[month - 1][d])
            {
                cout << (eventCounter + 1) << ". " << eventNames[month -1][d] << " on "
                    << monthNames[month - 1] << " " << (d + 1) << " at "
                    << hourConvert(eventHour[month - 1][d]) << ":"
                    << eventMin[month - 1][d] << " ";
                getMeridian(eventHour[month - 1][d]);
                cout << endl;
                eventCounter++;
            }
        }
        eventCounter = 0;

    cout << "\nYou have " << eventAccumulator << " events in " << monthNames[userChoice - 1] << "."
         << endl << endl << "Which would you like to remove? (1 - " << eventAccumulator
         << " or 0 to Cancel...)" << endl;

    while(!(cin >> userChoice) || userChoice < 0 || userChoice > eventAccumulator)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    if(userChoice == 0) return;
    
    int day = userChoice;
    for(int d = 0; d < DAYS; d++)
    {
        if(eventPresent[month - 1][d])
            removalCounter++;
        if(removalCounter == day)
            eventPresent[month - 1][d - 1] = false;
    }
    return;
}

/*
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// ********** Global Constants **********
const int MONTHS = 12;
const int DAYS = 31;

// ********** Functions **********
void addEventDisplay();                    // Display Add Menu Header
void displayMonths();
int monthChoice();
int monthDaysCheck(int, bool);
int dayChoice(int);
int hourChoice();
int minuteChoice(int);
string getName();
// void monthReturn(int, string[MONTHS]);
void eventMake(bool [][DAYS], int [][DAYS], int [][DAYS], string [MONTHS], string [][DAYS], int, int, int, int, string);
// void addEvent(bool, bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS], string [MONTHS]);    // Adds events
void setLeapYear(int &, bool &);    // Checks for year, sets whether leap-year for February-related considerations
void saveUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS]);  // Saves data
void loadUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS]);  // Loads data
void displayMenu(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS], string[MONTHS]);             // Shows a menu for display options
int hourConvert(int);               // Converts 24-format hours to 12-hour for display purposes
void getMeridian(int);              // Gets appropriate AM or PM label for converted hour display

// ********** Main **********
int main()
{
    // ********** Arrays **********
    bool eventPresent[12][31];  // Store whether an event exists on a calendar date
    int eventHour[12][31];      // Store 24-hour format value for hour of event
    int eventMin[12][31];       // Store minute-specific time for event (00, 15, 30, 45)
    string monthNames[12];      // Store month names for output
    string eventName[12][31];   // Store name of an event on a calendar date

    // ********** Variables **********
    int userChoice;
    int minutes;
    int hour;
    int day = 0;
    int month = 0;
    int monthDayCount;
    int year = 0;
    bool leapYearSet = false;
    bool leapYear;           
    bool dummyStop;
    bool unsavedChanges = false;
    string eventNameVar;

    ifstream monthData;             // Load month names into array from txt
    monthData.open("months.txt");
    for(int i = 0; i < MONTHS; i++)
    {
        monthData >> monthNames[i];
    }
    monthData.close();

    do
    {
        cout << "\n\n----------------------------------Event Planner----------------------------------\n\n";
        cout << "Main Menu" << endl << endl;
        cout << "1. Add Event" << endl
             << "2. Remove Event" << endl
             << "3. Display Events" << endl
             << "4. Load Events" << endl
             << "5. Save Events" << endl << endl
             << "0. Quit" << endl << endl;

        cout << "Please choose from the items above (1-5 or 0 to Quit): ";
        while(!(cin >> userChoice) || userChoice < 0 || userChoice > 6)     //Get, validate userChoice
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }

        switch(userChoice)  //Each case represents a different main menu option
        {
            case 1: 
            {
                if(leapYearSet == false)
                {
                    setLeapYear(year, leapYear);
                    leapYearSet = true;
                }
                addEventDisplay();
                displayMonths();
                month = monthChoice();
                monthDayCount = monthDaysCheck(month, leapYear);
                day = dayChoice(monthDayCount);
                hour = hourChoice();
                minutes = minuteChoice(hour);
                eventNameVar = getName();
                eventMake(eventPresent, eventHour, eventMin, monthNames, eventName,
                          month, day, hour, minutes, eventNameVar);
                //addEvent(leapYear, eventPresent, eventName, eventHour, eventMin, monthNames);
                break;
            }
            case 2: break;
            case 3: displayMenu(eventPresent, eventName, eventHour, eventMin, monthNames); break;
            case 4: loadUserData(eventPresent, eventName, eventHour, eventMin); break;  // Use nested for loops to fill arrays from text files.
            case 5: saveUserData(eventPresent, eventName, eventHour, eventMin); break;  // Use nested for loops to use current arrays to overwrite save txts.
            case 6: cout << "Sneaky test: "; monthNames[5]; cout << endl; break;
            case 0: dummyStop = true;
                    break;  // Can I set a flag for unsaved changes? And offer to save them before leaving?
                            // Either way, this is where files are closed, goodbye message, and program exit.
            default: dummyStop = true; break;
        }
    } while(dummyStop != true);
}

void addEventDisplay()
{
    cout << "\n\n------------------------------------Add Event------------------------------------\n\n";
    return;
}

void displayMonths()
{
    cout << setw(20) << left << "1. January" << setw(20) << "2. February" << setw(20) << "3. March" << setw(20) << "4. April" << endl
         << setw(20) << "5. May" << setw(20) << "6. June" << setw(20) << "7. July" << setw(20) << "8. August" << endl
         << setw(20) << "9. September" << setw(20) << "10. October" << setw(20) << "11. November" << setw(20) << "12. December"
         << endl << endl;
    cout << "Please start by choosing a month for your event (1-12): ";
    return;
}

int monthChoice()
{
    int userChoice;
    while(!(cin >> userChoice || userChoice < 1 || userChoice > 12))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

int monthDaysCheck(int month, bool leapYear)
{
    int daysCount;
    if(month == 2)
    {
        if(leapYear)
        {
            daysCount = 29;
        }
        else
        {
            daysCount = 28;
        }
    }
    else if(month == 4 || month == 6 || month == 9 || month == 11)
    {
        daysCount = 30;
    }
    else
    {
        daysCount = 31;
    }
    return daysCount;
}

int dayChoice(int dayCount)
{
    cout << "\nOn what day does your event occur? ";
    int userChoice;
    while(!(cin >> userChoice) || userChoice < 1 || userChoice > dayCount)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

int hourChoice()
{
    int userChoice;
    cout << "\nAt what hour does your event occur?" << endl
         << "\nPlease enter the hour in 24-hour format (military time) and" << endl
         << "the software will convert it to AM/PM for you: ";
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 23)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

int minuteChoice(int hour)
{
    int userChoice;
    cout << "\nIs there a more specific time? " << hourConvert(hour) << ":15? " << hourConvert(hour) << ":30? etc.: " << endl
         << "Please add minutes: ";
    
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 59)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    return userChoice;
}

string getName()
{
    string eventName;
    cout << "\nPlease enter the name of your event: ";
    cin.ignore();
    getline(cin, eventName);
    return eventName;
}

void eventMake(// Arrays
               bool eventPresent[][DAYS], int eventHour[][DAYS], int eventMin[][DAYS],
               string monthNames[MONTHS], string eventName[][DAYS],
               // Variables
                int month, int day, int hour, int minutes, string eventNameVar)
{
    cout << "\nGreat. Your event, " << eventNameVar << ", \nis scheduled for ";
    cout << monthNames[month - 1] << " " << day << ", at ";
    cout << hourConvert(hour);
    cout << ":" << setw(2) << setfill('0') << minutes << setfill(' ') << " ";
    getMeridian(hour);
    cout << ". \n\nPress 'Enter' to return to the Main Menu...Don't forget to save!";
    cin.get();

    //Filing everything away in arrays
    eventPresent[month - 1][day - 1] = true;
    eventName[month - 1][day -1] = eventNameVar;
    eventHour[month - 1][day - 1] = hour;
    eventMin[month - 1][day - 1] = minutes;

    //Clear variables out
    eventNameVar = " ";
    hour = 0;
    minutes = 0;    

    return;//**************************************Not done
}

/* void functionRemove()
    In which month?
        List events for month
        Which event? 1., 2., 3...
*/
/*
void displayMenu(bool eventPresent[][DAYS], string eventName[][DAYS],  // Reads all user data to several txt files
                  int eventHour[][DAYS], int eventMin[][DAYS], string monthNames[MONTHS])
{
    int userChoice;
    int monthChoice;
    int eventCounter;

    cout << "\n\n----------------------------------Display Menu-----------------------------------\n\n";
    cout << "1. Display All Events" << endl
         << "2. Display Events by Month" << endl << endl
         << "0. Cancel" << endl << endl;
    cout << "Please enter your choice: ";
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 2)     // while input bad, moar input
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    switch(userChoice)
    {
        case 1:
        {
            cout << "\n\n-------------------------------Display All Events--------------------------------\n\n";
            for(int m = 0; m < MONTHS; m++)
            {
                for(int d = 0; d < DAYS; d++)
                {
                    if(eventPresent[m][d] == true)
                    {
                        cout << ++eventCounter << ". " << eventName[m][d] << " on " << monthNames[m] << " " << (d + 1)
                             << " at " << hourConvert(eventHour[m][d]) << ":" << setw(2) << setfill('0') << eventMin[m][d] << endl;
                        cout << setfill(' ');
                    }
                }
            }
            eventCounter = 0;
        break;
        }
        case 2: 
        {
            cout << "\n\n----------------------------Display Events by Month------------------------------\n\n";
            cout << setw(20) << left << "1. January" << setw(20) << "2. February" << setw(20) << "3. March" << setw(20) << "4. April" << endl
                 << setw(20) << "5. May" << setw(20) << "6. June" << setw(20) << "7. July" << setw(20) << "8. August" << endl
                 << setw(20) << "9. September" << setw(20) << "10. October" << setw(20) << "11. November" << setw(20) << "12. December"
                 << endl << endl;

            cout << "Which month would you like to display? (1-12 or 0 to Cancel): ";
            while(!(cin >> monthChoice) || monthChoice < 0 || monthChoice > 13)     // while input bad, moar input
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter a valid option: ";
            }
            for(int d = 0; d < DAYS; d++)
            {
                if(eventPresent[monthChoice - 1][d])
                {
                    cout << ++eventCounter << ". " << eventName[monthChoice - 1][d] << " on " << monthNames[monthChoice - 1] << " " << (d + 1)
                         << " at " << hourConvert(eventHour[monthChoice - 1][d]) << ":" << eventMin[monthChoice - 1][d] << endl;
                }
            }
            eventCounter = 0;
            break;
        }
        case 0: break;
    }
}

void setLeapYear(int &year, bool &leapYear)
{
    cout << "\nPlease enter the year for this calendar: ";    // cout
    while(!(cin >> year) || year < 2020 || year > 2099)     // while input bad, moar input
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }

    if(year % 4 == 0)           // if year (cin above) has a remainder of 0
    {
        leapYear = true;        // then set leapYear (reference back to main) true
        return;
    }
    else
    {
        leapYear = false;       // else set leapYear (reference back to main) false
        return;
    }
}

int hourConvert(int hour)
{
    if(hour > 12)
    {
        hour -= 12;
    }
    return hour;
}

void getMeridian(int hour)
{
    if(hour < 12)
    {
        cout << "AM";
    }
    else
    {
        cout << "PM";
    }
    return
}

void loadUserData(bool eventPresent[][DAYS], string eventName[][DAYS],  // Reads all user data to several txt files
                  int eventHour[][DAYS], int eventMin[][DAYS])
{
    int userChoice;

    ifstream readEventPresent;                     // Establish ifstream objects
    ifstream readEventName;
    ifstream readEventHour;
    ifstream readEventMin;
    
    readEventPresent.open("eventPresent.txt");     // Open objects' .txt files
    readEventName.open("eventName.txt");
    readEventHour.open("eventHour.txt");
    readEventMin.open("eventMin.txt");

    cout << "\n\n------------------------------------Load Data------------------------------------\n\n";
    cout << "1. Load Data" << endl
         << "2. Cancel" << endl << endl;
    cout << "Would you like to load your calendar data? (1-2): " << endl;
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 2)     //Get, validate userChoice
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    switch(userChoice)
    {
        case 1:
        {
            for(int m = 0; m < MONTHS; m++)
            {
                for(int d = 0; d < DAYS; d++)
                {
                    readEventPresent >> eventPresent[m][d];
                    readEventName >> eventName[m][d];
                    readEventHour >> eventHour[m][d];
                    readEventMin >> eventMin[m][d];
                }
            }
            readEventPresent.close();
            readEventName.close();
            readEventHour.close();
            readEventMin.close();
            break;
        }
        case 2: break;
    }
    return;
}

void saveUserData(bool eventPresent[][DAYS], string eventName[][DAYS], // Writes all user data to several txt files
                  int eventHour[][DAYS], int eventMin[][DAYS])
{
    int userChoice;

    ofstream writeEventPresent;                     // Establish ifstream objects
    ofstream writeEventName;
    ofstream writeEventHour;
    ofstream writeEventMin;
    
    writeEventPresent.open("eventPresent.txt");     // Open objects' .txt files
    writeEventName.open("eventName.txt");
    writeEventHour.open("eventHour.txt");
    writeEventMin.open("eventMin.txt");

    cout << "\n\n------------------------------------Save Data------------------------------------\n\n";
    cout << "1. Save Data" << endl
         << "2. Cancel" << endl << endl;
    cout << "Would you like to save your calendar data? (1-2): " << endl;
    while(!(cin >> userChoice) || userChoice < 0 || userChoice > 2)     //Get, validate userChoice
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid option: ";
    }
    switch(userChoice)
    {
        case 1:
        {
            for(int m = 0; m < MONTHS; m++)
            {
                for(int d = 0; d < DAYS; d++)
                {
                    writeEventPresent << eventPresent[m][d] << endl;
                    writeEventName << eventName[m][d] << endl;
                    writeEventHour << eventHour[m][d] << endl;
                    writeEventMin << eventMin[m][d] << endl;
                }
            }
            writeEventPresent.close();
            writeEventName.close();
            writeEventHour.close();
            writeEventMin.close();
            break;
        }
        case 2: break;
    }
    return;
}

*/
/******************************FUNCTION GRAVEYARD*********************************
 * 
/*void monthReturn(int month, string monthNames[MONTHS])
{
    for(int i = 0; i == (month - 1); i++)
    {
        cout << monthNames[i];
    }
    return;
}   This function didn't work out the way I hoped it would. Its purpose was better
    served by just doing some basic stuff in the spot where I was calling it. */
/*void addEvent(bool leapYear, bool eventPresent[MONTHS][DAYS], string eventName[MONTHS][DAYS],
              int eventHour[MONTHS][DAYS], int eventMin[MONTHS][DAYS], string monthNames[MONTHS])
{
    int monthChoice;    // User's chosen month
    int dayChoice;      // User's choice of day
    int daysCount;      // Count of days for a given month (prevents Feb 30th, etc.)
    int hourChoice;     // Hour of the day for user's event
    int minChoice;      // Minutes of the hour for user's event
    string eventNameChoice; //Chosen name of user's event

    cout << "\n\n------------------------------------Add Event------------------------------------\n\n";

    cout << setw(20) << left << "1. January" << setw(20) << "2. February" << setw(20) << "3. March" << setw(20) << "4. April" << endl
         << setw(20) << "5. May" << setw(20) << "6. June" << setw(20) << "7. July" << setw(20) << "8. August" << endl
         << setw(20) << "9. September" << setw(20) << "10. October" << setw(20) << "11. November" << setw(20) << "12. December"
         << endl << endl;

    cout << "Please start by choosing a month for your event (1-12): ";
    //Get, validate month
    while(!(cin >> monthChoice) || monthChoice < 1 || monthChoice > 12)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }
    //Assign daysCount based on month choice; this will be used to keep from adding an event to Feb 30, Sep 31, etc.
    if(monthChoice == 2)
    {
        if(leapYear)
        {
            daysCount = 29;
        }
        else
        {
            daysCount = 28;
        }
    }
    else if(monthChoice == 4 || monthChoice == 6 || monthChoice == 9 || monthChoice == 11)
    {
        daysCount = 30;
    }
    else
    {
        daysCount = 31;
    }
    cout << "\nPlanning for " << monthNames[monthChoice - 1] << "..." << endl << endl;
    cout << "What day does your event take place on? (1 - " << daysCount << "): ";
    while(!(cin >> dayChoice) || dayChoice < 1 || dayChoice > daysCount)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }

    cout << "\nPlanning for " << monthNames[monthChoice - 1] << " " << dayChoice << "..." << endl;
    cout << "\nAt what hour does your event take place? (We'll get the minutes momentarily)" << endl;
    cout << "Input your hour in 24-hour format; we'll handle the conversion (13 = 1PM): ";
    while(!(cin >> hourChoice) || hourChoice < 0 || hourChoice > 23)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }
    //eventHour[monthChoice][dayChoice] = hourChoice;

    cout << "\nPlanning for " << monthNames[monthChoice - 1] << " "
         << dayChoice << " at " << hourConvert(hourChoice) << "..." << endl;
    cout << "\nWhat minutes go with your hour? (00, 15, 30, 45...): ";
    cin.clear();
    while(!(cin >> minChoice) || minChoice < 0 || minChoice > 59)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }
    
    cout << "What is the name of your event on " << monthNames[monthChoice - 1] << " "
         << dayChoice << " at " << hourConvert(hourChoice) << "? ";

    getline(cin, eventNameChoice);
    //cin >> eventNameChoice;

    //Assignment to arrays
    eventPresent[monthChoice][dayChoice] = true;
    eventName[monthChoice][dayChoice] = eventNameChoice;
    eventHour[monthChoice][dayChoice] = hourChoice;
    eventMin[monthChoice][dayChoice] = minChoice;

    cout << "Your event, " << eventName[monthChoice-1][dayChoice-1] << ", on " << monthNames[monthChoice - 1] << " "
         << dayChoice << " at " << hourConvert(hourChoice) << " ";
         getMeridian(hourChoice);
         cout << " is set.";
    return;
}
******************************FUNCTION GRAVEYARD*********************************/