#include "utils/EventUtils.h"

#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace EventUtils
{
    bool validateEvent(const map<string, string> &eventData)
    {
        const string requiredKeys[] = {"title", "date", "time"};

        for (const auto &key : requiredKeys)
        {
            auto it = eventData.find(key);
            if (it == eventData.end() || it->second.empty())
            {
                cout << "Error: The '" << key << "' is a required field and cannot be empty." << endl;
                return false;
            }
        }
        return true;
    }
}