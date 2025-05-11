#include "DateValidator.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

std::string DateValidator::timePointToString(const std::chrono::system_clock::time_point &timePoint)
{
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    std::tm *tm = std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d"); // Formato YYYY-MM-DD
    return oss.str();
}

std::chrono::system_clock::time_point DateValidator::stringToTimePoint(const std::string &dateString)
{
    std::tm tm = {};
    strptime(dateString.c_str(), "%Y-%m-%d", &tm);
    time_t time = std::mktime(&tm);
    return std::chrono::system_clock::from_time_t(time);
}

bool DateValidator::isValidFormat(const std::string &date)
{
    std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, datePattern);
}

bool DateValidator::isValidDate(const std::string &date)
{
    if (!isValidFormat(date))
    {
        return false;
    }

    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (isLeapYear ? 29 : 28))
            return false;
    }

    return true;
}

std::string DateValidator::currentDate()
{
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);
    std::ostringstream oss;
    oss << (now->tm_year + 1900) << '-'
        << (now->tm_mon + 1) << '-'
        << now->tm_mday;
    return oss.str();
}
