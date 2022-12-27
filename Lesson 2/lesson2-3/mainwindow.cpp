#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "No" << "Имя компьютера" << "IP адрес" << "MAC адрес");
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(i));
        ui->tableWidget->setItem(i,0,item);
        QTableWidgetItem *item1 = new QTableWidgetItem(QString("Name%1").arg(i));
        ui->tableWidget->setItem(i,1,item1);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString("0.0.0.00%1").arg(i));
        ui->tableWidget->setItem(i,2,item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(QString(""));
        ui->tableWidget->setItem(i,3,item3);
    }

        //ui->tableWidget->item(0,0)->setBackground(Qt::green);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
             ui->tableWidget->item(i,j)->setBackground(Qt::transparent);
        }
    }
    QList<QTableWidgetSelectionRange> rangesList = ui->tableWidget->selectedRanges();
    foreach (QTableWidgetSelectionRange range, rangesList)
    {
        int startRow = range.topRow();
        int endRow = range.bottomRow();

        for (int i = startRow; i <= endRow; ++i) {
            for (int j = 0; j < ui->tableWidget->columnCount(); ++j) {
                 ui->tableWidget->item(i,j)->setBackground(Qt::darkGreen);
            }
        }
    }
}

