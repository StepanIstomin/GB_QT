#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //translator.load(":/QtLanguage_en.qm");
    //a.installTranslator(&translator);
    w.show();
    return a.exec();
}
