// Brian Hoerner
// 30 Novemember 2020
// Event Planner
// This is an event planning software that operates as a standard calendar.
// Users can add, remove, and view events.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
    // Main Menu
    // 1. Add an Event
    // 2. Remove an Event
    // 3. View Events
    // 4. Quit
    
    //cout << "----------------------------------------|----------------------------------------";
    int userChoice;
    do
    {
        cout << "\n\n----------------------------------Event Planner----------------------------------\n\n";
        cout << "Main Menu" << endl << endl;
        cout << "1. Add Event" << endl
            << "2. Remove Event" << endl
            << "3. View Events" << endl
            << "4. Quit" << endl << endl;

        cout << "Please choose from the items above (1-4): ";
        while(!(cin >> userChoice) || userChoice < 1 || userChoice > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid option: ";
        }
    } while(userChoice != 4);
}

/* void functionAdd()
*/

/* void functionRemove()
    In which month?
        List events for month
        Which event? 1., 2., 3...
*/

/* void functionDisplay
    Display All
    Display by Month
    Display by day (still have to pick a month or maybe take two cins?)*/