#include "tasklogic.h"

#include <QTextStream>
#include <QDate>
#include <QDebug>

TaskLogic::TaskLogic(QObject *parent)
    : QObject{parent}
{
    //openFile();
    //qDebug() << curTasks;
}

int TaskLogic::taskCount()
{
    int tCount = 0;
    QFile file ("tasks.txt");
    if (file.open(QIODevice::ReadOnly)){
        QByteArray ba = file.readAll();
        QString text(ba);
        tCount = text.count("\r\n", Qt::CaseSensitive);;
        file.close();
    }
    return tCount;
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

QString TaskLogic::saveCheck(QString name, QString date, QString progress)
{
    QString errorMsg = "";

    // Проверка названия задачи
    if(name == ""){
        errorMsg.append("Название задачи не должно быть пустым\r\n");
    }

    // Проверка даты
    QDate dateQdate = QDate::fromString(date,"dd.MM.yyyy");
    if (!dateQdate.QDate::isValid()) {
        errorMsg.append("Дата должна быть в формате dd.mm.yyyy\r\n");
    }

    // Проверка значения прогресса
    bool digit;
    qint16 decProgress = progress.toInt(&digit, 10);
    if (!digit || decProgress < 0 || decProgress > 10) {
        errorMsg.append("Прогресс задачи - число от 0 до 10 ");
    }

    return errorMsg;
}

void TaskLogic::saveFile(QString name, QString date, QString progress)

{
    QString str = name + "\t" + date + "\t" + progress + "\r\n"; // \r\n - windows variant

    QFile file ("tasks.txt");
    if (file.open(QIODevice::Append)){
        QTextStream stream(&file);
        stream << str;
        file.close();
    }
}

QString TaskLogic::getCurTasks() const
{
    return curTasks;
}
