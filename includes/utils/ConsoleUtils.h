#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <string>

using namespace std;

namespace ConsoleUtils
{
    void displayOption(const string &option, const string &action, const string &description);
    string getEventStringField(const string &field, const string &value);
    string getEventDateField();
    string getEventTimeField();
    string getEventFrequencyField();
    string getEventPriorityField();
    void clearScreen();
}

#endif // CONSOLE_UTILS_H