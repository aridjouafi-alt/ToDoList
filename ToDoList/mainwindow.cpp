#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    try
    {
        todoList.loadTasks();
        refreshList();
    }
    catch (const std::runtime_error& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    try
    {
        todoList.saveTasks();
    }
    catch (const std::runtime_error& e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::on_pushButton_clicked()
{
    try{
    QString addedTitle = ui->lineEdit->text() ;
    todoList.addTask(addedTitle);
    refreshList();
    ui->lineEdit->clear();
    }
    catch (const std::exception &e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }

}

void MainWindow::refreshList()
{
    ui->listWidget->clear();
    for (int i = 0; i < todoList.getTasks().size(); i++)
    {
        const task& task = todoList.getTasks()[i];
        QListWidgetItem *item = new QListWidgetItem();
        QWidget *rowWidget = new QWidget;
        QHBoxLayout *layout = new QHBoxLayout(rowWidget);
        QCheckBox *checkBox = new QCheckBox;
        checkBox->setChecked(task.isCompleted());
        connect(checkBox, &QCheckBox::toggled,
                this,
                [this, i](bool)
                {
                    todoList.toggleTask(i);
                    refreshList();
                });
        QLabel *label = new QLabel(task.getTitle());
        QPushButton *editButton = new QPushButton("Edit");
        connect(editButton, &QPushButton::clicked,
                this,
                [this, i]()
                {
                    bool ok;

                    QString newTitle = QInputDialog::getText(
                        this,
                        "Edit Task",
                        "The new title:",
                        QLineEdit::Normal,
                        todoList.getTasks()[i].getTitle(),
                        &ok
                        );

                    if (ok)
                    {
                        try
                        {
                            todoList.editTask(i, newTitle);
                            refreshList();
                        }
                        catch (const std::exception& e)
                        {
                            QMessageBox::warning(this, "Error", e.what());
                        }
                    }
                });
        QPushButton *deleteButton = new QPushButton("Delete");
        connect(deleteButton, &QPushButton::clicked,
                this,
                [this, i]()
                {
                    try
                    {
                        todoList.deleteTask(i);
                        refreshList();
                    }
                    catch (const std::exception& e)
                    {
                        QMessageBox::warning(this, "Error", e.what());
                    }
                });
        checkBox->setChecked(task.isCompleted());

        layout->addWidget(checkBox);
        layout->addWidget(label);
        layout->addStretch();
        layout->addWidget(editButton);
        layout->addWidget(deleteButton);
        item->setSizeHint(rowWidget->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, rowWidget);
    }
}








