#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>

#include <downloader.h>
#include <parser.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Parser* parser;
    Downloader *downloader;
    QLineEdit *findtxt;
    QPushButton *button;
    QProgressBar *qpb;
    QLabel* label;

    void showPic(const QString&path);
    QUrl *url;

private slots:
    void slotGo();
    void slotPicShow(const QUrl&url);
    void slotDone(const QUrl&url, const QByteArray&ba);
    void slotParseError();
    void slotPicError();
    void slotDownloadProgress(qint64 received, qint64 total);
};
#endif // MAINWINDOW_H
