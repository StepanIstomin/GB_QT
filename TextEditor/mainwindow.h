#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTranslator>
#include <QString>
#include <QKeyEvent>
#include <QPrinter>
#include <QPrintDialog>

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
    void on_action_open_triggered();

    void on_action_help_triggered();

    void on_action_save_triggered();

    void on_action_readonly_triggered();

    void on_action_lang_ru_triggered();

    void on_action_lang_en_triggered();

    void setTitle();
    void slotOpenFile(bool readOnly);
    void slotSaveFile();
    void slotNewFile();
    void slotPrint();

    void on_action_dark_triggered();

    void on_action_bright_triggered();

    void on_action_print_triggered();

protected:
    void keyReleaseEvent(QKeyEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::MainWindow *ui;

    QString title;
    QString curFilename = "";
    QString curLanguage;
    QTranslator translator; // Объект перевода
    void switchLanguage(QString language); //Метод переключения языка

    bool pressCTRL = false;
};
#endif // MAINWINDOW_H
