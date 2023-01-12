#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Текстовый редактор"));
    setStyleSheet("\
        QWidget {background-color: lightGray;}\
        QTextEdit {background-color: white;}\
        QMenuBar {background-color: white; color: black}\
        QMenu::item:selected {background-color: white; color: black}\
        ");
    curLanguage = "ru";

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->setTabsClosable(true);
    slotNewFile();

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::slotCloseFile);
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

        ui->retranslateUi(this);
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


void MainWindow::slotOpenFile(bool readOnly) {
    pTextWidget = new TextWidget();
    if (readOnly)
        pTextWidget->readOnly(true);
    else
        pTextWidget->readOnly(false);
    QString filePath = QFileDialog::getOpenFileName(this,tr("Открыть файл для чтения"),"","Text files (*.txt)");
    QFile file(filePath);
    QFileInfo fileInfo(filePath);
    if (file.open(QIODevice::ReadOnly)){
        QString filename = fileInfo.fileName();
        QByteArray ba = file.readAll();
        QString text(ba);
        pTextWidget->setText(text);
        pTextWidget->setName(filename);
        pTextWidget->setPath(file.fileName());
        ui->tabWidget->addTab(pTextWidget,QIcon(QString("")),filename);
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    }

 }

void MainWindow::slotSaveFile()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    QString filename = curWidget->name();
    QString path = curWidget->path();
    QString filePath = QFileDialog::getSaveFileName(ui->tabWidget->currentWidget(),tr("Сохранить файл"),path,"Text files (*.txt)");
    QFile file (filePath);
    QFileInfo fileInfo(filePath);
    if (file.open(QIODevice::WriteOnly)){
        filename = fileInfo.fileName();
        QTextStream stream(&file);
        QString str = curWidget->text();
        stream << str;
        file.close();
        curWidget->setName(filename);
        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),filename);
    }
}

void MainWindow::slotNewFile()
{
    pTextWidget = new TextWidget();
    ui->tabWidget->addTab(pTextWidget,QIcon(QString("")),tr("Новый Документ"));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    pTextWidget->setName(tr("Новый Документ"));
}

void MainWindow::slotCloseFile()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

void MainWindow::slotPrint()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    QPrinter printer;
    QPrintDialog printDlg(&printer,this);
    printDlg.setWindowTitle(tr("Печать"));
    if (printDlg.exec() != QDialog::Accepted) return;
    curWidget->print(&printer);
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

