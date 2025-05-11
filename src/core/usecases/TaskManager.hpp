#ifndef TASK_MANAGER_HPP
#define TASK_MANAGER_HPP

#include "ITaskRepository.hpp"
#include <memory>

class TaskManager
{
public:
    TaskManager(std::shared_ptr<ITaskRepository> repository);

    void addTask(const std::string &description, const std::string &type, const std::chrono::system_clock::time_point &scheduledDate);
    std::vector<Task> getAllTasks() const;
    std::optional<Task> getTaskById(int id) const;
    void updateTask(int id, const std::string &description, const std::string &type, const std::chrono::system_clock::time_point &scheduledDate);
    void deleteTask(int id);

private:
    std::shared_ptr<ITaskRepository> repository_;
};

#endif // TASK_MANAGER_HPP
