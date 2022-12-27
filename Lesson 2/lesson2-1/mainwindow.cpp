#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "parsetext.h"

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


void MainWindow::on_plainTextEdit_textChanged()
{
    QString txt = ui->plainTextEdit->toPlainText();

    qint32 pos = 0;
    while (1) {
        qint32 fnd = txt.indexOf("#@", pos);
        if (fnd==-1) return;
        pos = fnd+2;
        int endTag = txt.indexOf("@", pos);
        int space = txt.indexOf(" ", pos);
        if((endTag < space || space == -1) && endTag != -1){
            ParseText parseText(txt.mid(pos,endTag-pos));
            QString answer = parseText.parse();
            txt.remove(fnd,endTag-fnd+1);
            txt.insert(fnd,answer);
            ui->plainTextEdit->setPlainText(txt);
        }
    }
}

