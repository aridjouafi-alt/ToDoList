#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    try{
    QString addedTitle = ui->lineEdit->text() ;

    task addedTask(addedTitle);
    todoList.addTask(addedTitle);

    ui->listWidget->addItem(addedTitle) ;

    ui->lineEdit->clear();
    }
    catch (const std::exception &e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }

}

