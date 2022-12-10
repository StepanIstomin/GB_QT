#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lesson 1-2");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    double side1 = ui->lineEdit_side1->text().toDouble();
    double side2 = ui->lineEdit_side2->text().toDouble();
    double angle = ui->lineEdit_angle->text().toDouble();
    if (ui->radioButton_grad->isChecked())  angle = (angle * (M_PI/180));


    double side3 = pow(side1*side1+side2*side2-2*side1*side2*cos(angle),0.5);
    QString answer = QStringLiteral("3-я сторона = %1").arg(side3);
    ui->textEdit->setText(answer);
}

