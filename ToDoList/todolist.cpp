#include "todolist.h"
#include <stdexcept>

todolist::todolist()
{
}

void todolist::addTask(QString title)
{
    if (title.trimmed().isEmpty())
    {
        throw std::invalid_argument("Task title cannot be empty.");
    }

    tasks.push_back(task(title));
}

void todolist::deleteTask(int index)
{
    if (index < 0 || index >= tasks.size())
    {
        throw std::out_of_range("Invalid task index.");
    }
    else
    {
        tasks.erase(tasks.begin() + index);
    }
}

const std::vector<task>& todolist::getTasks() const
{
    return tasks;
}