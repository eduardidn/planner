#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

namespace DateUtils
{
    int getCurrentYear()
    {
        auto now = chrono::system_clock::now();
        auto nowCrono = chrono::system_clock::to_time_t(now);
        auto localTime = localtime(&nowCrono);
        int currentYear = 1900 + localTime->tm_year;
        return currentYear;
    }

    string getCurrentDate()
    {
        auto now = chrono::system_clock::now();
        auto nowCrono = chrono::system_clock::to_time_t(now);
        auto localTime = localtime(&nowCrono);
        ostringstream dateStream;
        dateStream << (localTime->tm_year + 1900) << "-"
                   << setw(2) << setfill('0') << (localTime->tm_mon + 1) << "-"
                   << setw(2) << setfill('0') << localTime->tm_mday;

        string currentDate = dateStream.str();
        return currentDate;
    }

    bool isLeapYear(int year)
    {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    int getMaxDaysInMonth(int month, int year)
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
        }
    }
}