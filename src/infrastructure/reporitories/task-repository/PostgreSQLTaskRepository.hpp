#ifndef POSTGRESQL_TASK_REPOSITORY_HPP
#define POSTGRESQL_TASK_REPOSITORY_HPP

#include "ITaskRepository.hpp"
#include "Task.hpp"
#include "DatabaseManager.hpp"
#include <vector>
#include <optional>

class PostgreSQLTaskRepository : public ITaskRepository
{
public:
    PostgreSQLTaskRepository();

    void addTask(const Task &task) override;
    std::vector<Task> getAllTasks() const override;
    std::optional<Task> getTaskById(int id) const override;
    void updateTask(const Task &task) override;
    void deleteTask(int id) override;

private:
    pqxx::connection *db_;
    void initializeSchema();
};

#endif // POSTGRESQL_TASK_REPOSITORY_HPP