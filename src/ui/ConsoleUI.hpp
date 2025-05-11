#ifndef CONSOLE_UI_HPP
#define CONSOLE_UI_HPP

#include "TaskManager.hpp"
#include <memory>
#include <string>

class ConsoleUI
{
public:
    ConsoleUI(std::shared_ptr<TaskManager> taskManager);
    void run();

private:
    std::shared_ptr<TaskManager> taskManager_;
    void showMenu();
    void handleAddTask();
    void handleViewTasks();
    void handleEditTask();
    void handleDeleteTask();
    /* --------------------------------- Helpers -------------------------------- */
    void clearScreen();
    bool confirmChanges(const std::string &description, const std::string &type, const std::string &scheduledDate);
    std::string truncate(const std::string &str, int width);
};

#endif // CONSOLE_UI_HPP
