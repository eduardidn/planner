#include "TaskManager.hpp"
#include <iostream>

TaskManager::TaskManager(std::shared_ptr<ITaskRepository> repository)
    : repository_(repository) {}

void TaskManager::addTask(const std::string &description, const std::string &type, const std::chrono::system_clock::time_point &scheduledDate)
{
    Task task(0, description, type, scheduledDate);
    repository_->addTask(task);
}

std::vector<Task> TaskManager::getAllTasks() const
{
    return repository_->getAllTasks();
}

std::optional<Task> TaskManager::getTaskById(int id) const
{
    return repository_->getTaskById(id);
}

void TaskManager::updateTask(int id, const std::string &description, const std::string &type, const std::chrono::system_clock::time_point &scheduledDate)
{
    Task task(id, description, type, scheduledDate);
    repository_->updateTask(task);
}

void TaskManager::deleteTask(int id)
{
    repository_->deleteTask(id);
}
