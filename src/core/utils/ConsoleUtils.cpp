#include "utils/ConsoleUtils.h"

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

namespace ConsoleUtils
{
    void displayOption(const string &option, const string &action, const string &description)
    {
        cout << setw(15) << option
             << setw(30) << action
             << setw(50) << description << endl;
    }
}