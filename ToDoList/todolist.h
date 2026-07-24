# pragma once
#include <vector>
#include "task.h"

class todolist
{
private:
    std::vector<task> tasks;

public:
    todolist();

    void addTask(QString);
    void deleteTask(int index);
    const std::vector<task>& getTasks() const;
};