#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Текстовый редактор");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_open_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Открыть файл","","Text files (*.txt)");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        ui->textEdit->setText(text);
    }
}

void MainWindow::on_action_save_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this,"Сохранить файл","","Text files (*.txt)");
    QFile file (filePath);
    if (file.open(QIODevice::WriteOnly))
    {
    QTextStream stream(&file);
    QString str = ui->textEdit->toPlainText();
    stream << str;
    file.close();
    }

}

void MainWindow::on_action_2_triggered()
{
    Help helpWindow;
    helpWindow.setModal(true);
    helpWindow.exec();

}




