#include "ConsoleUI.hpp"
#include "InputHandler.hpp"
#include "DateValidator.hpp"
#include <iostream>
#include <iomanip>
#include <string>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

ConsoleUI::ConsoleUI(std::shared_ptr<TaskManager> taskManager)
    : taskManager_(taskManager) {}

void ConsoleUI::run()
{
    bool running = true;
    while (running)
    {
        clearScreen();
        handleViewTasks();
        showMenu();
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            handleAddTask();
            break;
        case 2:
            handleEditTask();
            break;
        case 3:
            handleDeleteTask();
            break;
        case 4:
            running = false;
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
    }
}

void ConsoleUI::showMenu()
{
    std::cout << "\nTask Manager Menu:\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Edit Task\n";
    std::cout << "3. Delete Task\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void ConsoleUI::handleAddTask()
{
    std::cin.ignore();

    std::string description = InputHandler::getValidatedString("Enter Task Description");
    if (description.empty())
        return;

    std::string type = InputHandler::getValidatedString("Enter Task Type (e.g., Work, Personal)");
    if (type.empty())
        return;

    std::string dateInput = InputHandler::getValidatedDate("Enter Scheduled Date (YYYY-MM-DD)");
    if (dateInput.empty())
        return;

    std::tm tm = {};
    strptime(dateInput.c_str(), "%Y-%m-%d", &tm);
    auto scheduledDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    if (confirmChanges(description, type, dateInput))
    {
        try
        {
            taskManager_->addTask(description, type, scheduledDate);
            std::cout << "✅ Task added successfully!" << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "❌ Error adding task: " << e.what() << std::endl;
        }
    }
    else
    {
        std::cout << "❌ Operation cancelled. Returning to the main menu.\n";
        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
}

void ConsoleUI::handleViewTasks()
{
    clearScreen();
    std::vector<Task> tasks = taskManager_->getAllTasks();

    if (tasks.empty())
    {
        std::cout << "⚠️  No tasks found." << std::endl;
        return;
    }

    int dashLength = 85;
    std::cout << "\n";
    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(25) << "Description"
              << std::setw(20) << "Type"
              << std::setw(25) << "Scheduled Date" << std::endl;

    std::cout << std::string(dashLength, '-') << std::endl;

    for (const auto &task : tasks)
    {
        std::cout << std::left
                  << std::setw(5) << task.getId()
                  << std::setw(25) << truncate(task.getDescription(), 24)
                  << std::setw(20) << truncate(task.getType(), 19)
                  << std::setw(25) << DateValidator::timePointToString(task.getScheduledDate())
                  << std::endl;
    }
    std::cout << std::string(dashLength, '-') << std::endl;
}

void ConsoleUI::handleEditTask()
{
    handleViewTasks();
    std::cin.ignore();

    int id = InputHandler::getValidatedInt("Enter the ID of the task to edit");
    if (id == -1)
        return;

    auto taskOpt = taskManager_->getTaskById(id);
    if (!taskOpt.has_value())
    {
        std::cout << "❌ Task not found. Returning to main menu." << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();
        return;
    }

    Task task = taskOpt.value();

    std::string newDescription = task.getDescription();
    std::string newType = task.getType();
    std::string newDate = DateValidator::timePointToString(task.getScheduledDate());

    std::cout << "\n--- Current Task Information ---\n";
    std::cout << "1. Description: " << task.getDescription() << "\n";
    std::cout << "2. Type: " << task.getType() << "\n";
    std::cout << "3. Scheduled Date: " << DateValidator::timePointToString(task.getScheduledDate()) << "\n";
    std::cout << "--------------------------------\n";

    std::cout << "Do you want to edit the Description? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 'y' || choice == 'Y')
    {
        newDescription = InputHandler::getValidatedString("Enter new Task Description");
        if (newDescription.empty())
        {
            std::cout << "❌ Operation cancelled.\n";
            return;
        }
    }

    std::cout << "Do you want to edit the Type? (y/n): ";
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 'y' || choice == 'Y')
    {
        newType = InputHandler::getValidatedString("Enter new Task Type");
        if (newType.empty())
        {
            std::cout << "❌ Operation cancelled.\n";
            return;
        }
    }

    std::cout << "Do you want to edit the Scheduled Date? (y/n): ";
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 'y' || choice == 'Y')
    {
        newDate = InputHandler::getValidatedDate("Enter new Scheduled Date (YYYY-MM-DD)");
        if (newDate.empty())
        {
            std::cout << "❌ Operation cancelled.\n";
            return;
        }
    }

    std::tm tm = {};
    strptime(newDate.c_str(), "%Y-%m-%d", &tm);
    auto scheduledDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));

    if (confirmChanges(newDescription, newType, newDate))
    {
        try
        {
            taskManager_->updateTask(id, newDescription, newType, scheduledDate);
            std::cout << "✅ Task updated successfully!" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        catch (const std::exception &e)
        {
            std::cerr << "❌ Error updating task: " << e.what() << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }
    else
    {
        std::cout << "❌ Operation cancelled. Returning to the main menu.\n";
        std::cout << "Press Enter to continue...";
        std::cin.get();
    }
}

void ConsoleUI::handleDeleteTask()
{
    handleViewTasks();
    std::cin.ignore();

    int id = InputHandler::getValidatedInt("Enter the ID of the task to edit");
    if (id == -1)
        return;

    auto taskOpt = taskManager_->getTaskById(id);
    if (!taskOpt.has_value())
    {
        std::cout << "❌ Task not found. Returning to main menu." << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();
        return;
    }

    Task task = taskOpt.value();

    std::cout << "\n--- Current Task Information ---\n";
    std::cout << "1. Description: " << task.getDescription() << "\n";
    std::cout << "2. Type: " << task.getType() << "\n";
    std::cout << "3. Scheduled Date: " << DateValidator::timePointToString(task.getScheduledDate()) << "\n";
    std::cout << "--------------------------------\n";

    std::cout << "Do you want to delete the task? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 'y' || choice == 'Y')
    {
        try
        {
            taskManager_->deleteTask(id);
            std::cout << "✅ Task deleted successfully!" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        catch (const std::exception &e)
        {
            std::cerr << "❌ Error deleting task: " << e.what() << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                                   Helpers                                  */
/* -------------------------------------------------------------------------- */
void ConsoleUI::clearScreen()
{
    system(CLEAR);
}

std::string ConsoleUI::truncate(const std::string &str, int width)
{
    if (str.length() > width)
    {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

bool ConsoleUI::confirmChanges(const std::string &description, const std::string &type, const std::string &scheduledDate)
{
    clearScreen();
    std::cout << "⚠️  You are about to save the following information:\n";
    std::cout << "------------------------------------------\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Scheduled Date: " << scheduledDate << "\n";
    std::cout << "------------------------------------------\n";
    std::cout << "Do you want to proceed? (y/n): ";

    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return (choice == 'y' || choice == 'Y');
}