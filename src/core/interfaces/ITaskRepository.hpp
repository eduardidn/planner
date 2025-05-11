#ifndef I_TASK_REPOSITORY_HPP
#define I_TASK_REPOSITORY_HPP

#include "Task.hpp"
#include <vector>
#include <optional>

class ITaskRepository
{
public:
    virtual ~ITaskRepository() = default;

    virtual void addTask(const Task &task) = 0;
    virtual std::vector<Task> getAllTasks() const = 0;
    virtual std::optional<Task> getTaskById(int id) const = 0;
    virtual void updateTask(const Task &task) = 0;
    virtual void deleteTask(int id) = 0;
};

#endif // I_TASK_REPOSITORY_HPP
