#ifndef DATE_VALIDATOR_HPP
#define DATE_VALIDATOR_HPP

#include <string>
#include <regex>
#include <ctime>
#include <stdexcept>

class DateValidator
{
public:
    static std::string timePointToString(const std::chrono::system_clock::time_point &timePoint);
    static std::chrono::system_clock::time_point stringToTimePoint(const std::string &dateString);
    static std::string currentDate();
    static bool isValidFormat(const std::string &date);
    static bool isValidDate(const std::string &date);
};

#endif // DATE_VALIDATOR_HPP
