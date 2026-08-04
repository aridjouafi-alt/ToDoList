#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QCloseEvent>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QInputDialog>
#include "ToDoList.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onItemChanged(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    todolist todoList;
    void refreshList();
};
#endif // MAINWINDOW_H
