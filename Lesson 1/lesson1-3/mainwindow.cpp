#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lesson 1-3");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   ui->plainTextEdit_2->appendPlainText(ui->plainTextEdit->toPlainText());
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit_2->setPlainText(ui->plainTextEdit->toPlainText());
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->plainTextEdit->appendHtml("<font color='red'>Hello</font>");
}

