#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

    QFile fileHelp(":/help/Help.txt");
    if (fileHelp.open(QIODevice::ReadOnly)){
        QByteArray ba = fileHelp.readAll();
        QString textHelp(ba);
        //ui->text->setText(textHelp);
        ui->textBrowser->setText(textHelp);
    }
}

Help::~Help()
{
    delete ui;
}
