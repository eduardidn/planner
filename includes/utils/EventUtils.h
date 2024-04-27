#ifndef EVENT_UTILS_H
#define EVENT_UTILS_H

#include <map>
#include <string>

using namespace std;

namespace EventUtils
{
    bool validateEvent(const map<string, string> &eventData);
}

#endif // EVENT_UTILS_H