#include "task.h"

task::task(QString title)
    : title(title),completed(false)
{
}

QString task::getTitle() const
{
    return title;
}

bool task::isCompleted() const
{
    return completed;
}

void task::setTitle(const QString& newTitle)
{
    title = newTitle;
}

void task::setCompleted(bool status)
{
    completed = status;
}

void task::markCompleted()
{
    completed = true;
}

void task::toggleCompleted()
{
    completed = !completed;
}