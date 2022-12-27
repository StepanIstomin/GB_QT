#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    ui->listView->setModel(model);
    model->appendRow(new QStandardItem(QIcon(":/img/icons8-c++.png"),"С++"));
    model->appendRow(new QStandardItem(QIcon(":/img/icons8-python.png"), "Python"));
    model->appendRow(new QStandardItem(QIcon(":/img/icons8-java.png"), "Java"));
    model->appendRow(new QStandardItem(QIcon(":/img/icons8-c-sharp.png"), "C#"));
    model->appendRow(new QStandardItem(QIcon(":/img/icons8-php.png"), "PHP"));
    model->appendRow(new QStandardItem(QIcon(":/img/icons8-javascript.png"), "JavaScript"));

    ui->listView->setMovement(QListView::Free);
    ui->listView->setDefaultDropAction(Qt::MoveAction);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString newItem = ui->lineEdit->text();
    model->appendRow(new QStandardItem(QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),newItem));
}


void MainWindow::on_deleteButton_clicked()
{
    int row = ui->listView->currentIndex().row();
    model->removeRow(row);
}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->listView->setViewMode(QListView::IconMode);
    }
    else
        ui->listView->setViewMode(QListView::ListMode);
}

