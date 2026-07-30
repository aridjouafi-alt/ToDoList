#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget,
            &QListWidget::itemChanged,
            this,
            &MainWindow::onItemChanged);
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

void MainWindow::on_pushButton_4_clicked()
{
    try
    {
        int row = ui->listWidget->currentRow();
        todoList.deleteTask(row);
        delete ui->listWidget->takeItem(row);
    }
    catch (const std::out_of_range& e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    try
    {
        int row = ui->listWidget->currentRow();
        todoList.completeTask(row);
        ui->listWidget->item(row)->setText(
            "✓ " + ui->listWidget->item(row)->text()
            );
    }
    catch (const std::out_of_range& e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onItemChanged(QListWidgetItem *item)
{
    int index = ui->listWidget->row(item);
    todoList.toggleTask(index);

}
void MainWindow::refreshList()
{
    ui->listWidget->blockSignals(true);
    ui->listWidget->clear();

    for (const auto& task : todoList.getTasks())
    {
        QString title = task.getTitle();
        QListWidgetItem *item = new QListWidgetItem(title);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if (task.isCompleted())
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);

        ui->listWidget->addItem(item);
    }
    ui->listWidget->blockSignals(false);
}
