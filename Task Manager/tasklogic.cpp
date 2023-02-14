#include "tasklogic.h"

#include <QTextStream>
#include <QDate>
#include <QDebug>
#include <QSqlQuery>


TaskLogic::TaskLogic(QObject *parent)
    : QObject{parent}
{
    createConnection();
    createTable();

    tableModel = new QSqlQueryModel(this);
}

int TaskLogic::taskCount()
{
    QSqlQuery query;
    query.exec(tr("SELECT COUNT(*) FROM taskslist"));
    query.next ();
    return query.value(0).toInt();
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

bool TaskLogic::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tasks.db");
    if (db.open()){
        //qDebug() << "DB connection success";
        return true;
    }
    else{
        qDebug() << "DB connection error";
        return false;
    }
}

bool TaskLogic::createTable()
{
    QSqlQuery query;
    QString request = "CREATE TABLE IF NOT EXISTS taskslist ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, "
                      "name TEXT, date VARCHAR(10), progress INTEGER(1));";
    if (!query.exec(request)){
        //qDebug() << "Unable to create table";
        return false;
    }
    //qDebug() << "Table created";
    return true;
}

bool TaskLogic::insertTask(QString name, QString date, QString progress)
{
    QString sample = "INSERT INTO taskslist (name, date, progress) "
                     "VALUES ('%1','%2',%3);";
    bool digit;
    qint16 decProgress = progress.toInt(&digit, 10);
    QString request = sample.arg(name).arg(date).arg(decProgress);
    //qDebug() << request;
    QSqlQuery query;
    if (!query.exec(request)){
        //qDebug() << "error adding task to table";
        return false;
    }
    //qDebug() << "the task was added to the table successfully";
    return true;
}

QSqlQueryModel* TaskLogic::getModel()
{
    tableModel->setQuery("SELECT * FROM tasks");
    //engine.rootContext()->setContextProperty("tableModel", tableModel);
    return tableModel;
}
