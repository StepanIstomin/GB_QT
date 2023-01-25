#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "help.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Текстовый редактор"));

    on_action_bright_triggered();

    curLanguage = "ru";

    //Toolbar
    QToolBar* toolBar = addToolBar("Toolbar");
    QAction* tbarFont = toolBar->addAction(tr("Шрифт"));
    QAction* tbarCopyFormat = toolBar->addAction(tr("Копировать стиль"));
    QAction* tbarPasteFormat = toolBar->addAction(tr("Применить стиль"));
    toolBar->addSeparator();
    QAction* tbarLeft = toolBar->addAction(tr("По левому краю"));
    QAction* tbarRight = toolBar->addAction(tr("По правому краю"));
    QAction* tbarCent = toolBar->addAction(tr("По центру"));
    QAction* tbarJust = toolBar->addAction(tr("По растянуть"));
    toolBar->addSeparator();
    QAction* tbarDate = toolBar->addAction(tr("Дата"));
    QAction* tbarTime = toolBar->addAction(tr("Время"));

    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->setTabsClosable(true);
    slotNewFile();

    //connect
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::slotCloseFile);
    connect(tbarFont,SIGNAL(triggered()),this,SLOT(setFont()));
    connect(tbarCopyFormat,SIGNAL(triggered()),this,SLOT(copyFormat()));
    connect(tbarPasteFormat,SIGNAL(triggered()),this,SLOT(pasteFormat()));
    connect(tbarDate,SIGNAL(triggered()),this,SLOT(slotInsDate()));
    connect(tbarTime,SIGNAL(triggered()),this,SLOT(slotInsTime()));

    QSignalMapper * signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(tbarLeft, 1);
    signalMapper->setMapping(tbarRight, 2);
    signalMapper->setMapping(tbarCent, 3);
    signalMapper->setMapping(tbarJust, 4);
    connect(tbarLeft, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(tbarRight, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(tbarCent, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(tbarJust, SIGNAL(triggered()), signalMapper, SLOT (map()));
    connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(alignText(int)));
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
    if (curWidget) {
    QPrinter printer;
    QPrintDialog printDlg(&printer,this);
    printDlg.setWindowTitle(tr("Печать"));
    if (printDlg.exec() != QDialog::Accepted) return;
    curWidget->print(&printer);
    }
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

void MainWindow::copyFormat()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    if(!curWidget) return void();
    QFont font = curWidget->pTextField->textCursor().charFormat().font();
    curWidget->setFont(font);
    curWidget->setCurAligment(curWidget->pTextField->alignment());
}

void MainWindow::pasteFormat()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    if(!curWidget) return void();
    QTextCharFormat fmt;
    fmt.setFont(curWidget->font());
    curWidget->pTextField->textCursor().setCharFormat(fmt);
    curWidget->pTextField->setAlignment(curWidget->getAligment());
}

void MainWindow::setFont()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    if(!curWidget) return void();
    QFont font;
    QFontDialog fntDlg(font,this);
    bool b[] = {true};
    font = fntDlg.getFont(b);
    if (b[0]){
        QTextCharFormat fmt = curWidget->pTextField->textCursor().charFormat();
        fmt.setFont(font);
        curWidget->pTextField->textCursor().setCharFormat(fmt);
        curWidget->pTextField->setCurrentFont(font);
    }

}

void MainWindow::alignText(int a)
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    if(!curWidget) return void();
    if (a == 1) curWidget->pTextField->setAlignment(Qt::AlignLeft);
    else if (a == 2) curWidget->pTextField->setAlignment(Qt::AlignRight);
    else if (a == 3) curWidget->pTextField->setAlignment(Qt::AlignCenter);
    else if (a == 4) curWidget->pTextField->setAlignment(Qt::AlignJustify);
}

void MainWindow::slotInsTime()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    if(!curWidget) return void();
    QString time = QTime::currentTime().toString("hh:mm");
    curWidget->pTextField->insertHtml(time);
}

void MainWindow::slotInsDate()
{
    TextWidget* curWidget = (TextWidget*)ui->tabWidget->currentWidget();
    if(!curWidget) return void();
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    curWidget->pTextField->insertHtml(date);
}

