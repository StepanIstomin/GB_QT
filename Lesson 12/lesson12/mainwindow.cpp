#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QFile>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    downloader = new Downloader(this);
    parser = new Parser(this);
    findtxt = new QLineEdit(this);
    button = new QPushButton("Find picture",this);
    qpb = new QProgressBar(this);
    label = new QLabel(this);

    connect(button,SIGNAL(clicked()),SLOT(slotGo()));
    connect(findtxt,SIGNAL(returnPressed()),SLOT(slotGo()));
    connect(parser,SIGNAL(done(const QUrl&)),SLOT(slotPicShow(const QUrl&)));
    connect(parser,SIGNAL(error()),SLOT(slotParseError()));
    connect(downloader,SIGNAL(downloadProgress(qint64,qint64)),SLOT(slotDownloadProgress(qint64,qint64)));
    connect(downloader,SIGNAL(done(const QUrl&, const QByteArray&)),SLOT(slotDone(QUrl,QByteArray)));
    connect(downloader,SIGNAL(error()),SLOT(slotPicError()));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(findtxt, 0,0);
    layout->addWidget(button, 0,1);
    layout->addWidget(qpb,1,0,1,2);
    layout->addWidget(label, 2,0,1,2);

    QWidget *wgt = new QWidget(this);
    wgt->setGeometry(0,0,800,600);
    setCentralWidget(wgt);
    wgt->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPic(const QString &path)
{
    QPixmap pix(path);
    if (!pix) {
        QMessageBox::critical(this,"Error","Page Blocked");
    }
    if (pix.width() > 780){
       pix = pix.scaledToWidth(780);
    }
    if (pix.height() > 500){
       pix = pix.scaledToHeight(500);
    }
    label->setPixmap(pix);
}

void MainWindow::slotGo()
{
    if (findtxt->text() != ""){
        parser->download(QUrl("https://yandex.ru/images/search?text=" + findtxt->text()));
    }
    else
        QMessageBox::critical(this,"Error","Request field must not be empty");
}

void MainWindow::slotPicShow(const QUrl &url)
{
    downloader->download(url); // Передаем в слот download текст из поля поиска
}

void MainWindow::slotDone(const QUrl &url, const QByteArray &ba)
{
    QFile file(url.path().section('/',-1)); // берем из урл последнюю секцию после слэша
    if(file.open(QIODevice::WriteOnly)){
        file.write(ba);
        file.close();
    }
    showPic(file.fileName());
}

void MainWindow::slotParseError()
{
    QMessageBox::critical(this,"Error","Error in image search");
}

void MainWindow::slotPicError()
{
    QMessageBox::critical(this,"Error","Image page not available");
}

void MainWindow::slotDownloadProgress(qint64 received, qint64 total)
{
    if (total<=0){
        slotPicError();
        return;
    }
    qpb->setValue(100*received/total);
}

