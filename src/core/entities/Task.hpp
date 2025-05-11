#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <chrono>

class Task
{
private:
    int id_;
    std::string description_;
    std::string type_;
    std::chrono::system_clock::time_point scheduledDate_;

public:
    Task(int id, const std::string &description, const std::string &type, const std::chrono::system_clock::time_point &scheduledDate)
        : id_(id), description_(description), type_(type), scheduledDate_(scheduledDate) {}

    int getId() const { return id_; }
    const std::string &getDescription() const { return description_; }
    const std::string &getType() const { return type_; }
    const std::chrono::system_clock::time_point &getScheduledDate() const { return scheduledDate_; }

    void setDescription(const std::string &description) { description_ = description; }
    void setType(const std::string &type) { type_ = type; }
    void setScheduledDate(const std::chrono::system_clock::time_point &date) { scheduledDate_ = date; }
};

#endif // TASK_HPP