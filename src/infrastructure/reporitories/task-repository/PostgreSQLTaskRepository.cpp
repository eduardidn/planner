#include "PostgreSQLTaskRepository.hpp"
#include "DateValidator.hpp"
#include <iostream>
#include <string>

PostgreSQLTaskRepository::PostgreSQLTaskRepository()
{
    db_ = DatabaseManager::getInstance().getConnection();
    initializeSchema();

    db_->prepare("insert_task",
                 "INSERT INTO tasks (description, type, scheduled_date) VALUES ($1, $2, $3)");

    db_->prepare("select_all_tasks",
                 "SELECT * FROM tasks ORDER BY scheduled_date ASC");

    db_->prepare("select_task_by_id",
                 "SELECT * FROM tasks WHERE id = $1");

    db_->prepare("update_task",
                 "UPDATE tasks SET description = $1, type = $2, scheduled_date = $3 WHERE id = $4");

    db_->prepare("delete_task",
                 "DELETE FROM tasks WHERE id = $1");
}

void PostgreSQLTaskRepository::initializeSchema()
{
    try
    {
        pqxx::work trans(*db_);

        std::string createTableSQL = R"(
            CREATE TABLE IF NOT EXISTS tasks (
                id SERIAL PRIMARY KEY,
                description TEXT NOT NULL,
                type TEXT NOT NULL,
                scheduled_date DATE NOT NULL
            );
        )";

        trans.exec(createTableSQL);
        trans.commit();
        std::cout << "[PostgreSQLTaskRepository] Schema initialized successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PostgreSQLTaskRepository] Error initializing schema: " << e.what() << std::endl;
        throw;
    }
}

void PostgreSQLTaskRepository::addTask(const Task &task)
{
    std::string scheduledDate = DateValidator::timePointToString(task.getScheduledDate());

    if (!DateValidator::isValidDate(scheduledDate))
    {
        throw std::runtime_error("Invalid date format. Expected format: YYYY-MM-DD");
    }

    try
    {
        pqxx::work trans(*db_);

        trans.exec_prepared("insert_task", task.getDescription(), task.getType(), scheduledDate);

        trans.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PostgreSQLTaskRepository] Error adding task: " << e.what() << std::endl;
        throw;
    }
}

std::vector<Task> PostgreSQLTaskRepository::getAllTasks() const
{
    std::vector<Task> tasks;

    try
    {
        pqxx::work trans(*db_);
        pqxx::result results = trans.exec_prepared("select_all_tasks");

        for (const auto &row : results)
        {
            std::string scheduledDateStr = row["scheduled_date"].as<std::string>();

            auto scheduledDate = DateValidator::stringToTimePoint(scheduledDateStr);
            Task task(
                row["id"].as<int>(),
                row["description"].as<std::string>(),
                row["type"].as<std::string>(),
                scheduledDate);
            tasks.push_back(task);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PostgreSQLTaskRepository] Error fetching tasks: " << e.what() << std::endl;
        throw;
    }

    return tasks;
}

std::optional<Task> PostgreSQLTaskRepository::getTaskById(int id) const
{
    try
    {
        pqxx::work trans(*db_);
        pqxx::result results = trans.exec_prepared("select_task_by_id", id);

        if (!results.empty())
        {
            const auto &row = results[0];
            std::string scheduledDateStr = row["scheduled_date"].as<std::string>();

            auto scheduledDate = DateValidator::stringToTimePoint(scheduledDateStr);
            return Task(
                row["id"].as<int>(),
                row["description"].as<std::string>(),
                row["type"].as<std::string>(),
                scheduledDate);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PostgreSQLTaskRepository] Error fetching task by ID: " << e.what() << std::endl;
        throw;
    }

    return std::nullopt;
}

void PostgreSQLTaskRepository::updateTask(const Task &task)
{
    std::string scheduledDate = DateValidator::timePointToString(task.getScheduledDate());

    if (!DateValidator::isValidDate(scheduledDate))
    {
        throw std::runtime_error("Invalid date format. Expected format: YYYY-MM-DD");
    }

    try
    {
        pqxx::work trans(*db_);

        trans.exec_prepared("update_task", task.getDescription(), task.getType(), scheduledDate, task.getId());

        trans.commit();
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PostgreSQLTaskRepository] Error updating task: " << e.what() << std::endl;
        throw;
    }
}

void PostgreSQLTaskRepository::deleteTask(int id)
{
    try
    {
        pqxx::work trans(*db_);

        trans.exec_prepared("delete_task", id);
        trans.commit();
        std::cout << "[PostgreSQLTaskRepository] Task with ID " << id << " deleted successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[PostgreSQLTaskRepository] Error deleting task: " << e.what() << std::endl;
        throw;
    }
}
