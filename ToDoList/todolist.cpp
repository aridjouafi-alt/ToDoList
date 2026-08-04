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
void todolist::toggleTask(int index)
{
    if (index < 0 || index >= tasks.size())
        throw std::out_of_range("Invalid index");

    tasks[index].toggleCompleted();
}
void todolist::editTask(int index, QString newTitle)
{
    if (index < 0 || index >= tasks.size())
        throw std::out_of_range("Invalid task index.");

    if (newTitle.trimmed().isEmpty())
        throw std::invalid_argument("Task title cannot be empty.");

    tasks[index].setTitle(newTitle);
}
void todolist::saveTasks()
{
    std::ofstream file ("tasks.txt") ;
    if (!file)
    {
        throw std::runtime_error("the file cannot be opened.");
    }
    else
    {
        for (const task & task : tasks)
        {        QString qstring = task.getTitle() ;
            file << qstring.toStdString() << ":" << task.isCompleted() << "\n" ;
        }
    }
}
void todolist::loadTasks()
{
    std::ifstream file ("tasks.txt") ;
    if (!file)
    {
        throw std::runtime_error("the file is not found.");
    }
    else
    {
        tasks.clear();
        std::string line ;
        while (getline(file,line))
        {
            std::size_t separator = line.find(':') ;
            if ( separator == std::string::npos )
            {
                throw std::runtime_error("invalid format used .");
            }
            bool status;
            std::string strtitle = line.substr(0,separator);
            if (line.substr(separator+1,line.size()- separator ) == "1")
            {    status = true ;}
            else {
                if (line.substr(separator+1,line.size() - separator ) == "0")
                {    status = false ;}
                else
                {
                    throw std::runtime_error("the status is wrong in the file .");
                }}
                task newtask(QString::fromStdString(strtitle));
                newtask.setCompleted(status) ;
                tasks.push_back(newtask);
    }
}
}


