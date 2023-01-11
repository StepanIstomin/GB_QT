#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyleSheet("\
        QWidget {background-color: lightGray;}\
        QTextEdit {background-color: white;}\
        QMenuBar {background-color: white; color: black}\
        QMenu::item:selected {background-color: white; color: black}\
        ");
    curLanguage = "ru";
    setTitle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    slotOpenFile(false);
}
void MainWindow::on_action_readonly_triggered()
{
    slotOpenFile(true);
}

void MainWindow::on_action_save_triggered()
{
    slotSaveFile();
}

void MainWindow::on_action_help_triggered()
{
    Help helpWindow;
    helpWindow.setModal(true);
    helpWindow.exec();
}

void MainWindow::switchLanguage(QString language)
{
    if (curLanguage != language){
        qApp->removeTranslator(&translator);
        translator.load(":/QtLanguage_" + language + ".qm");
        qApp->installTranslator(&translator);

        setTitle();
        ui->menu->setTitle(tr("Файл"));
        ui->action_open->setText(tr("Открыть"));
        ui->action_readonly->setText(tr("Открыть только для чтения"));
        ui->action_save->setText(tr("Сохранить"));
        ui->action_print->setText(tr("Печать"));

        ui->menu_3->setTitle(tr("Язык"));
        ui->action_lang_ru->setText(tr("Русский"));
        ui->action_lang_en->setText(tr("Английский"));

        ui->menu_2->setTitle(tr("О программе"));
        ui->action_help->setText(tr("Справка"));

        ui->menu_style->setTitle(tr("Тема"));
        ui->action_bright->setText(tr("Светлая"));
        ui->action_dark->setText(tr("Темная"));

        curLanguage = language;
        QLocale locale = QLocale(curLanguage);
        QLocale::setDefault(locale);
        QString languageName = QLocale::languageToString(locale.language());
        ui->statusbar->showMessage(tr("Текущий язык переключен на %1").arg(languageName));
    }
}


void MainWindow::on_action_lang_ru_triggered()
{
    switchLanguage("ru");
}

void MainWindow::on_action_lang_en_triggered()
{
    switchLanguage("en");
}

void MainWindow::setTitle()
{
    if (curFilename != "")
        title = tr("Текстовый редактор - ") + curFilename;
    else
        title = tr("Текстовый редактор");
    setWindowTitle(title);
}

void MainWindow::slotOpenFile(bool readOnly) {
    if (readOnly)
        ui->textEdit->setReadOnly(true);
    else
        ui->textEdit->setReadOnly(false);
    QString filePath = QFileDialog::getOpenFileName(this,tr("Открыть файл для чтения"),"","Text files (*.txt)");
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)){
        curFilename = file.fileName();
        QByteArray ba = file.readAll();
        QString text(ba);
        ui->textEdit->setText(text);
        setTitle();
    }
 }

void MainWindow::slotSaveFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("Сохранить файл"),curFilename,"Text files (*.txt)");
    QFile file (filePath);
    if (file.open(QIODevice::WriteOnly)){
        curFilename = file.fileName();
        QTextStream stream(&file);
        QString str = ui->textEdit->toPlainText();
        stream << str;
        file.close();
        setTitle();
    }
}

void MainWindow::slotNewFile()
{
    ui->textEdit->setText("");
    QString filePath = QFileDialog::getSaveFileName(this,tr("Создать новый документ"),"","Text files (*.txt)");
    QFile file (filePath);
    if (file.open(QIODevice::WriteOnly)){
        curFilename = file.fileName();
        QTextStream stream(&file);
        QString str = ui->textEdit->toPlainText();
        stream << str;
        file.close();
        setTitle();
    }
}

void MainWindow::slotPrint()
{
    QPrinter printer;
    QPrintDialog printDlg(&printer,this);
    printDlg.setWindowTitle(tr("Печать"));
    if (printDlg.exec() != QDialog::Accepted) return;
    ui->textEdit->print(&printer);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        pressCTRL = true;
    if (event->key() == Qt::Key_O && pressCTRL) //Open
        slotOpenFile(false);
    if (event->key() == Qt::Key_S && pressCTRL) //Save
        slotSaveFile();
    if (event->key() == Qt::Key_N && pressCTRL) //New
        slotNewFile();
    if (event->key() == Qt::Key_P && pressCTRL) //Print
        slotPrint();
    if (event->key() == Qt::Key_Q && pressCTRL) //Quit
        qApp->quit();
}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control )
        pressCTRL = false;
}



void MainWindow::on_action_dark_triggered()
{
    setStyleSheet("\
QWidget {background-color: gray;}\
QTextEdit {background-color: black; color: white}\
QMenuBar {background-color: black; color: white}\
QMenuBar::item:selected {background-color: gray; color: white}\
QMenu::item {background-color: gray; color: white}\
QMenu::item:selected {background-color: darkGray; color: black}\
");

}


void MainWindow::on_action_bright_triggered()
{
    setStyleSheet("\
QWidget {background-color: lightGray;}\
QTextEdit {background-color: white;}\
QMenuBar {background-color: white; color: black}\
QMenu::item:selected {background-color: white; color: black}\
");
}


void MainWindow::on_action_print_triggered()
{
    slotPrint();
}

