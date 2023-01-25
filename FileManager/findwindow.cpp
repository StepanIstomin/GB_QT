#include "findwindow.h"
#include "ui_findwindow.h"

FindWindow::FindWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindWindow)
{
    ui->setupUi(this);
    setWindowTitle("File Search");

    findFile = new FindFile(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(findFile);
}

FindWindow::~FindWindow()
{
    delete ui;
}
