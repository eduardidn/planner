#include "utils/DateUtils.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

namespace ConsoleUtils
{
    void displayOption(const string &option, const string &action, const string &description)
    {
        cout << setw(15) << option
             << setw(30) << action
             << setw(50) << description << endl;
    }

    void displayMonths()
    {
        cout << "Select a month:" << endl
             << " 1: January" << endl
             << " 2: February" << endl
             << " 3: March" << endl
             << " 4: April" << endl
             << " 5: May" << endl
             << " 6: June" << endl
             << " 7: July" << endl
             << " 8: August" << endl
             << " 9: September" << endl
             << "10: October" << endl
             << "11: November" << endl
             << "12: December" << endl;
    }

    /* -------------------------------------------------------------------------- */
    /*                               Form Functions                               */
    /* -------------------------------------------------------------------------- */

    string getEventStringField(const string &field, const string &value)
    {
        cout << value << " (max 255 caracteres)"
             << ": ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string fieldValue;
        getline(cin, fieldValue);

        if (fieldValue.length() > 255)
        {
            fieldValue = fieldValue.substr(0, 255);
        }
        return fieldValue;
    }

    string getEventDateField()
    {
        int year, month, day;
        int currentYear = DateUtils::getCurrentYear();

        cout << "Enter year (" << currentYear << " to " << currentYear + 5 << "): ";
        cin >> year;
        while (cin.fail() || year < currentYear || year > currentYear + 5)
        {
            cout << "Invalid year, please enter a valid year (" << currentYear << " to " << currentYear + 5 << "): ";
            cin >> year;
        }

        displayMonths();
        cout << "Enter the number of the month (1-12): ";
        cin >> month;
        while (cin.fail() || month < 1 || month > 12)
        {
            cout << "Invalid month, please enter a valid number (1-12): ";
            cin >> month;
        }

        int maxDays = DateUtils::getMaxDaysInMonth(month, year);
        cout << "Enter day of the month (1-" << maxDays << "): ";
        cin >> day;
        while (cin.fail() || day < 1 || day > maxDays)
        {
            cout << "Invalid day, please enter a valid day of the month (1-" << maxDays << "): ";
            cin >> day;
        }

        ostringstream dateFormatted;
        dateFormatted << year << "-"
                      << setw(2) << setfill('0') << month << "-"
                      << setw(2) << setfill('0') << day;

        return dateFormatted.str();
    }

    string getEventTimeField()
    {
        int hour, minute;
        string ampm;

        cout << "You will enter the time in a 12-hour format." << endl;
        cout << "Enter the hour (1-12): ";
        cin >> hour;
        while (cin.fail() || hour < 1 || hour > 12)
        {
            cout << "Invalid hour, please enter a valid hour (1-12): ";
            cin >> hour;
        }

        cout << "Enter minute (0-59): ";
        cin >> minute;
        while (cin.fail() || minute < 0 || minute > 59)
        {
            cout << "Invalid minute, please enter a valid minute (0-59): ";
            cin >> minute;
        }

        cout << "Enter AM or PM (a/p): ";
        cin >> ampm;
        while (cin.fail() || (ampm != "a" && ampm != "p"))
        {
            cout << "Invalid input, please enter 'AM' or 'PM': ";
            cin >> ampm;
        }

        string ampmString = ampm == "a" ? "AM" : "PM";
        ostringstream timeFormatted;
        timeFormatted << hour << ":"
                      << setw(2) << setfill('0') << minute << " "
                      << ampmString;

        return timeFormatted.str();
    }

    string getEventFrequencyField()
    {
        char frequency;
        cout << " [O]nce" << endl;
        cout << " [D]aily" << endl;
        cout << " [W]eekly" << endl;
        cout << " [M]onthly" << endl;
        cout << "Enter your choice (o/d/w/m): ";
        cin >> frequency;
        frequency = tolower(frequency);

        while (cin.fail() || (frequency != 'o' && frequency != 'd' && frequency != 'w' && frequency != 'm'))
        {
            cout << "Invalid input, please enter a valid option (o/d/w/m): ";
            cin >> frequency;
            frequency = tolower(frequency);
        }

        switch (frequency)
        {
        case 'o':
            return "once";
        case 'd':
            return "daily";
        case 'w':
            return "weekly";
        case 'm':
            return "monthly";
        default:
            return "unknown";
        }
    }

    string getEventPriorityField()
    {
        char priority;
        cout << " [L]ow" << endl;
        cout << " [M]edium" << endl;
        cout << " [H]igh" << endl;
        cout << " [C]ritical" << endl;
        cout << "Enter your choice (l/m/h/c): ";
        cin >> priority;
        priority = tolower(priority);

        while (cin.fail() || (priority != 'l' && priority != 'm' && priority != 'h' && priority != 'c'))
        {
            cout << "Invalid input, please enter a valid option (l/m/h/c): ";
            cin >> priority;
            priority = tolower(priority);
        }

        switch (priority)
        {
        case 'l':
            return "low";
        case 'm':
            return "medium";
        case 'h':
            return "high";
        case 'c':
            return "critical";
        default:
            return "unknown";
        }
    }

    void clearScreen()
    {
        system(CLEAR);
    }
}