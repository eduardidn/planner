#include "InputHandler.hpp"
#include "../utils/DateValidator.hpp"

std::string InputHandler::getInput(const std::string &prompt,
                                   std::function<bool(const std::string &)> validator,
                                   const std::string &errorMessage)
{
    std::string input;
    while (true)
    {
        std::cout << prompt << " (or type 'q' to go back): ";
        std::getline(std::cin, input);

        if (input == "q")
        {
            std::cout << "❌ Operation cancelled. Returning to the main menu.\n";
            return "";
        }

        if (validator(input))
        {
            return input;
        }
        else
        {
            std::cerr << "❌ " << errorMessage << "\n";
        }
    }
}

std::string InputHandler::getValidatedString(const std::string &prompt)
{
    return getInput(prompt, [](const std::string &input)
                    { return !input.empty(); }, "Input cannot be empty.");
}

std::string InputHandler::getValidatedDate(const std::string &prompt)
{
    return getInput(prompt, [](const std::string &input)
                    { return DateValidator::isValidFormat(input) && DateValidator::isValidDate(input); }, "Invalid date format. Please use YYYY-MM-DD and ensure the date exists.");
}

int InputHandler::getValidatedInt(const std::string &prompt)
{
    std::string input = getInput(prompt, [](const std::string &input)
                                 { return !input.empty() && input.find_first_not_of("0123456789") == std::string::npos; }, "Invalid number format. Please enter a valid integer.");

    if (input.empty())
    {
        return -1;
    }

    return std::stoi(input);
}
