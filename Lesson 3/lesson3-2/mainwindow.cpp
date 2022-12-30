#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parseweather.h"
#include "parsecurrents.h"

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


void MainWindow::on_ButtoChoseFile_clicked()
{
    //QString filePath;
    filePath = QFileDialog::getOpenFileName(this,"Открыть файл с HTML-кодом","","Text files (*.txt)");
    ui->labelFilePath->setText(filePath);
}


void MainWindow::on_ButtonParseFile_clicked()
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        ParseWeather weather(text);
        ui->textBrowser->setText(weather.parse());
        ParseCurrents currents(text);
        ui->lineEdit_usd->setText(currents.parseCur("USD"));
        ui->lineEdit_eur->setText(currents.parseCur("EUR"));
    }

}

