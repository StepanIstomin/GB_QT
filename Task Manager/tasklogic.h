#ifndef TASKLOGIC_H
#define TASKLOGIC_H

#include <QObject>
#include <QString>
#include <QFile>


class TaskLogic : public QObject
{
    Q_OBJECT
public:
    explicit TaskLogic(QObject *parent = nullptr);
    Q_INVOKABLE int taskCount();
    Q_INVOKABLE void openFile();
    Q_INVOKABLE QString saveCheck(QString name,QString date,QString progress);
    Q_INVOKABLE void saveFile(QString name,QString date,QString progress);
    QString getCurTasks() const;

signals:
private:
    QString curTasks;
};

#endif // TASKLOGIC_H
