#include "PostgreSQLTaskRepository.hpp"
#include "TaskManager.hpp"
#include "ConsoleUI.hpp"
#include <memory>

int main()
{
    auto repository = std::make_shared<PostgreSQLTaskRepository>();
    auto taskManager = std::make_shared<TaskManager>(repository);
    ConsoleUI ui(taskManager);
    ui.run();
    return 0;
}
