#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDir>
#include "findfile.h"
#include "findwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listView_left_doubleClicked(const QModelIndex &index);

    void on_actionFind_triggered();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;

    FindWindow findWindow;

};
#endif // MAINWINDOW_H
