#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string>

namespace DateUtils
{
    int getCurrentYear();
    std::string getCurrentDate();
    int getMaxDaysInMonth(int month, int year);
}

#endif // DATE_UTILS_H