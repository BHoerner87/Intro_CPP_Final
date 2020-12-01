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

const int MONTHS = 12;
const int DAYS = 31;

void addEvent(bool);                // Adds events
void setLeapYear(int &, bool &);    // Checks for year, sets whether leap-year for February-related considerations
void saveUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS]);  // Saves data
void loadUserData(bool [][DAYS], string [][DAYS], int [][DAYS], int [][DAYS]);  // Loads data

int main()
{
    bool eventPresent[12][31];  // Store whether an event exists on a calendar date
    string eventName[12][31];   // Store name of an event on a calendar date
    int eventHour[12][31];      // Store 24-hour format value for hour of event
    int eventMin[12][31];       // Store minute-specific time for event (00, 15, 30, 45)

    int userChoice;
    int year = 0;
    bool leapYearSet = false;
    bool leapYear;           
    bool dummyStop;          

    do
    {
        cout << "\n\n----------------------------------Event Planner----------------------------------\n\n";
        cout << "Main Menu" << endl << endl;
        cout << "1. Add Event" << endl
             << "2. Remove Event" << endl
             << "3. View Events" << endl
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
            case 2: setLeapYear(year, leapYear); break;
            case 3: break;  // Sub-Menu: View all events? View by month?
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

void addEvent(bool leapYear)
{
    int monthChoice;
    int daysCount;

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
        monthChoice = 31;
    }
}

/* void functionRemove()
    In which month?
        List events for month
        Which event? 1., 2., 3...
*/

/* void functionDisplay
    Display All
    Display by Month
    Display by day (still have to pick a month or maybe take two cins?)*/

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

/*int timeConvert(int asd)*******************
{
    This function will convert 24-hour ints to 12-hour AM/PM times
}*/

/*string meridianGen(int asd)**********************
{
    This function will be called at roughly the same time as timeConvert(), and will
    give a corresponding AM/PM to go along with the converted hour.
}*/

void loadUserData(bool eventPresent[][DAYS], string eventName[][DAYS],
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
            break;
        }
        case 2: break;
    }
    return;
}

void saveUserData(bool eventPresent[][DAYS], string eventName[][DAYS],
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
            break;
        }
        case 2: break;
    }
    return;
}