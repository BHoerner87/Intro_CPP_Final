// Brian Hoerner
// 30 Novemember 2020
// Event Planner
// This is an event planning software that operates as a standard calendar.
// Users can add, remove, and view events.

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// ********** Global Constants **********
const int MONTHS = 12;
const int DAYS = 31;

// ********** Functions **********
void addEvent(bool);            // Adds events
void setLeapYear(int &, bool &);// Checks for year, sets whether leap-year for February-related considerations
void saveUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS]);  // Saves data
void loadUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS]);  // Loads data
void displayMenu(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS], string[MONTHS]);             // Shows a menu for display options
int hourConvert(int);           // Converts 24-format hours to 12-hour for display purposes

// ********** Main **********
int main()
{
    // ********** Arrays **********
    bool eventPresent[12][31];  // Store whether an event exists on a calendar date
    string eventName[12][31];   // Store name of an event on a calendar date
    int eventHour[12][31];      // Store 24-hour format value for hour of event
    int eventMin[12][31];       // Store minute-specific time for event (00, 15, 30, 45)
    string monthNames[12];      // Store month names for output

    // ********** Variables **********
    int userChoice;
    int year = 0;
    bool leapYearSet = false;
    bool leapYear;           
    bool dummyStop;
    bool unsavedChanges = false;

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
                addEvent(leapYear);
                break;
            }
            case 2: break;
            case 3: displayMenu(eventPresent, eventName, eventHour, eventMin, monthNames); break;
            case 4: loadUserData(eventPresent, eventName, eventHour, eventMin); break;  // Use nested for loops to fill arrays from text files.
            case 5: saveUserData(eventPresent, eventName, eventHour, eventMin); break;  // Use nested for loops to use current arrays to overwrite save txts.
            case 6: cout << "Sneaky test: the value of eventPresent[0][0] is: " << eventPresent[0][0] << endl; break;
            case 0: dummyStop = true;
                    break;  // Can I set a flag for unsaved changes? And offer to save them before leaving?
                            // Either way, this is where files are closed, goodbye message, and program exit.
            default: dummyStop = true; break;
        }
    } while(dummyStop != true);
}

void addEvent(bool leapYear, bool eventPresent[][DAYS], string eventName[][DAYS],
              int eventHour[][DAYS], int eventMin[][DAYS], string monthNames[MONTHS])
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
    cout << "Planning for " << monthNames[monthChoice - 1] << "..." << endl << endl;
    cout << "What day does your event take place on? (1 - " << daysCount << "): ";
    while(!(cin >> dayChoice) || dayChoice < 1 || dayChoice > daysCount)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }

    cout << "Planning for " << monthNames[monthChoice - 1] << " " << dayChoice << "..." << endl;
    cout << "At what hour does your event take place? (We'll get the minutes momentarily)" << endl;
    cout << "Input your hour in 24-hour format; we'll handle the conversion (13 = 1PM): ";
    while(!(cin >> hourChoice) || hourChoice < 0 || hourChoice > 23)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }

    cout << "Planning for " << monthNames[monthChoice - 1] << " "
         << dayChoice << " at " << hourConvert(hourChoice) << "..." << endl;
    cout << "What minutes go with your hour? (00, 15, 30, 45...): ";
    while(!(cin >> minChoice) || minChoice < 0 || minChoice > 59)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }
    
    cout << "What is the name of your event on " << monthNames[monthChoice - 1] << " "
         << dayChoice << " at " << hourConvert(hourChoice) << "? ";

    getline(cin, eventNameChoice);

    // Assignment to arrays
    eventPresent[monthChoice][dayChoice] = true;
    eventName[monthChoice][dayChoice] = eventNameChoice;
    eventHour[monthChoice][dayChoice] = hourChoice;
    eventMin[monthChoice][dayChoice] = minChoice;

    cout << "Your event, " << eventNameChoice << ", on " << monthNames[monthChoice - 1] << " "
         << dayChoice << " at " << hourConvert(hourChoice) << " " << getMeridian(hourChoice) << " is set.";
}
/* void functionRemove()
    In which month?
        List events for month
        Which event? 1., 2., 3...
*/

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
                             << " at " << hourConvert(eventHour[m][d]) << ":" << eventMin[m][d] << endl;
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
    cout << "Please enter the year for this calendar: ";    // cout
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

string getMeridian(int hour)
{
    if(hour < 12)
    {
        cout << "AM";
    }
    else
    {
        cout << "PM";
    }
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