#include "todolist.h"
#include <stdexcept>
#include <string>
#include <QString>
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

void todolist::completeTask(int index)
{
    if (index < 0 || index >= tasks.size())
        throw std::out_of_range("Invalid index");

    tasks[index].markCompleted();
}

void todolist::saveTasks()
{
    std::ofstream file("tasks.txt");
    if (!file)
    {
        throw std::runtime_error("File could not be opened.");
    }
    for (const auto& task : tasks)
    {
        QString str = task.getTitle() ;
        file << str.toStdString() << ':' << task.isCompleted() << '\n';
    }
    file.close();
}
void todolist::loadTasks()
{
    std::ifstream file("tasks.txt");
    if (!file)
    {
        throw std::runtime_error("File could not be opened.");
    }

    tasks.clear();

    std::string line;

    bool status;

    while (std::getline(file, line))
    {
        std::string title = "";
        std::string statusStr = "";
        int i = 0;

        // Read the title
        while (i < line.size() && line[i] != ':')
        {
            title += line[i];
            i++;
        }

        i++; // Skip the ':'

        // Read the status
        while (i < line.size())
        {
            statusStr += line[i];
            i++;
        }
        QString qtitle = QString::fromStdString(title) ;
        if (statusStr == "0")
            status = false;
        else if (statusStr== "1")
            status = true;
        else
            throw std::runtime_error("Invalid task status in file.");

        task t (qtitle);
        t.setCompleted (status) ;
        tasks.push_back(t);
    }
}





