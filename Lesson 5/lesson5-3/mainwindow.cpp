#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("File Viewer");
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath("");
    ui->listView_left->setModel(model);
    ui->listView_right->setModel(model);
    connect(ui->listView_right,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_listView_left_doubleClicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listView_left_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName()==".."){
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if (fileInfo.fileName()=="."){
        listView->setRootIndex(model->index(""));
    }
    else if (fileInfo.isDir()){
        listView->setRootIndex(index);
    }
    if (listView == ui->listView_left){
        ui->lineEdit_pathL->setText(fileInfo.absoluteFilePath());
    } else {
        ui->lineEdit_pathR->setText(fileInfo.absoluteFilePath());
    }
}

