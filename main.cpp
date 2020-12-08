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
void saveUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS], bool, bool &);
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
            cin.ignore(1000, '\n');
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
            cout << "\nPress 'Enter' to return to Main Menu...\n";
            cin.ignore(1000, '\n');
            cin.get();
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
            cout << "\n\n-----------------------------------Data Loaded----------------------------------\n\n";
            cout << "Data loaded successfully!" << endl;
            cout << "\nPress 'Enter' to return to Main Menu...\n";
            cin.ignore(1000, '\n');
            cin.get();
            break;
        }
        case 2: break;
    }
    return;
}

void saveUserData(bool eventPresent[][DAYS], string eventNames[][DAYS],
                  int eventHour[][DAYS], int eventMin[][DAYS], bool leapYear, bool &unsavedChanges)
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
            
            cout << "\n\n-----------------------------------Data Saved-----------------------------------\n\n";
            cout << "Data saved! Press 'Enter' to continue...\n";
            cin.ignore(1000, '\n');
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
             << "Press 'Enter' to return to the Main Menu...\n";
        cin.ignore(1000, '\n');
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
                    << hourConvert(eventHour[month - 1][d]) << ":" << setw(2) << setfill('0')
                    << eventMin[month - 1][d] << setfill(' ') << " ";
                getMeridian(eventHour[month - 1][d]);
                cout << endl;
                eventCounter++;
            }
        }
        eventCounter = 0;

    cout << "\nYou have " << eventAccumulator << " events in " << monthNames[userChoice - 1] << "."
         << endl << endl << "Which would you like to remove? (1-" << eventAccumulator
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
    cout << "\nEvent successfully removed!" << endl
         << "Press 'Enter' to return to the Main Menu...";
    cin.ignore(1000, '\n');
    cin.get();
    return;
}