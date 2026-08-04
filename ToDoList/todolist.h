# pragma once
#include <vector>
#include "task.h"
#include <fstream>

class todolist
{
private:
    std::vector<task> tasks;

public:
    todolist();

    void addTask(QString);
    void deleteTask(int index);
    const std::vector<task>& getTasks() const;
    void completeTask ( int index ) ;
    void editTask(int index, QString newTitle);
    void toggleTask ( int index ) ;
    void saveTasks();
    void loadTasks();
};