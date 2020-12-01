// Brian Hoerner
// 30 Novemember 2020
// Event Planner
// This is an event planning software that operates as a standard calendar.
// Users can add, remove, and view events.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MONTHS = 12;

void addEvent(bool);
void setLeapYear(int &, bool &);    //Checks for year, sets whether leap-year for February-related considerations

int main()
{
    bool eventPresent[12][31];  // Store whether an event exists on a calendar date
    string eventName[12][31];   // Store name of an event on a calendar date
    int eventHour[12][31];      // Store 24-hour format value for hour of event
    int eventMin[12][31];       // Store minute-specific time for event (00, 15, 30, 45)

    // read arrays in from previous save files (this should be a menu item and function)

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

        cout << "Please choose from the items above (1-4): ";
        while(!(cin >> userChoice) || userChoice < 0 || userChoice > 5)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }

        switch(userChoice)
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
            case 4: break;  // Use nested for loops to fill arrays from text files.
            case 5: break;  // Use nested for loops to use current arrays to overwrite save txts.
            case 0: dummyStop = true; break;  // Can I set a flag for unsaved changes? And offer to save them before leaving?
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
    //
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

/*int timeConvert(int asd)
{
    This function will convert 24-hour ints to 12-hour AM/PM times
}*/

/*string meridianGen(int asd)
{
    This function will be called at roughly the same time as timeConvert(), and will
    give a corresponding AM/PM to go along with the converted hour.
}*/
void loadUserData()
{
    // Use a for loop to populate various parallel arrays with data
    // This will include a string array for event names
    //                  an int array for hours of events
    //                  an int array for minutes of events
    // The value for each of these will be assigned to the same calendar-based row-column layout: [12][31]
    // For example, my birthday would look like this:
    //              boolArr[11][7] = true
    //              nameArr[11][7] = "Brian's Birthday";
    //              hourArr[11][7] = 14
    //              minArr[11][7] = 30
    // I could print it out by writing
    // cout << nameArr[11][7] << " is occurring at" << timeConvert(hourArr[11][7]) << ":"
    //      << minArr[11][7] << meridianGen(hourArr[11][7]) << "." << endl;
    // The above instances of this specific array element will be filled using variables.
    // Boy, I've gone way off-track, huh? This is healthy, though.
    // So say I'm using a nested for loop to like, look up events in December and this is the only one.
    // for(int e = 0; e < dayCount; e++)
    // {
    //      if(boolArr[monthChoice][e] == true)
    //      {
    //          cout << nameArr[monthChoice][e] << " at " << timeConvert(hourArr[monthChoice][e]) <<
    //               << ":" << minArr[monthChoice][e] << meridianGen(hourArr[monthChoice][e]) << "." << endl;
    //      }
    // }
    // ..........You know, that ain't half bad?
    // This is a change to try and get this shit talking to Github.
}