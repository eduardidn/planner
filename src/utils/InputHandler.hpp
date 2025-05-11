#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <functional>
#include <string>

class InputHandler
{
private:
    static std::string
    getInput(const std::string &prompt,
             std::function<bool(const std::string &)> validator,
             const std::string &errorMessage);

public:
    static std::string getValidatedString(const std::string &prompt);
    static std::string getValidatedDate(const std::string &prompt);
    static int getValidatedInt(const std::string &prompt);
};

#endif // INPUT_HANDLER_HPP
