#ifndef TASKLOGIC_H
#define TASKLOGIC_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QSqlDatabase>
#include <tablewindow.h>
#include <QSqlQueryModel>

class TaskLogic : public QObject
{
    Q_OBJECT
public:
    explicit TaskLogic(QObject *parent = nullptr);
    Q_INVOKABLE int taskCount();
    Q_INVOKABLE QString saveCheck(QString name,QString date,QString progress);
    Q_INVOKABLE bool insertTask(QString name,QString date,QString progress);
    Q_INVOKABLE QSqlQueryModel* getModel();

signals:
private:
    bool createConnection();
    bool createTable();
    QSqlDatabase db;
    QSqlQueryModel *tableModel;
};

#endif // TASKLOGIC_H
