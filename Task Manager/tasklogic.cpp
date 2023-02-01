#include "tasklogic.h"

#include <QTextStream>
#include <QDebug>

TaskLogic::TaskLogic(QObject *parent)
    : QObject{parent}
{
    openFile();
    qDebug() << curTasks;
}

void TaskLogic::openFile()
{
    QFile file ("tasks.txt");
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        curTasks = text;
        file.close();
    }
}

void TaskLogic::saveFile(QString name,QString date,QString progr)

{
    if (name != "") {
        QString str = name + "\t" + date + "\t" + progr + "\r\n"; // \r\n - windows variant

        QFile file ("tasks.txt");
        if (file.open(QIODevice::Append)){
            QTextStream stream(&file);
            stream << str;
            file.close();
        }
    }
}

QString TaskLogic::getCurTasks() const
{
    return curTasks;
}
