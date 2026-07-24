#pragma once
#include <QString>
class task
{
private:
    QString title ;
    bool completed ;

public:
    task(QString = "" );
    QString getTitle() const ;
    bool isCompleted() const;
    void setTitle (const QString& ) ;
    void setCompleted(bool);
    void markCompleted () ;
    void toggleCompleted();
};
