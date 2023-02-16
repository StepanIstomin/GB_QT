#include "downloader.h"
#include <QNetworkReply>
#include <QMessageBox>

Downloader::Downloader(QObject *parent)
    : QObject{parent}
{
    qnam = new QNetworkAccessManager(this);
    connect(qnam,SIGNAL(finished(QNetworkReply*)),SLOT(slotFinished(QNetworkReply*)));
}

void Downloader::download(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = qnam->get(request);
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),SIGNAL(downloadProgress(qint64,qint64)));
}

void Downloader::slotFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NetworkError::NoError){
        emit error();
        qDebug() << "Can't download image";
    }
    else{
        emit done(reply->url(),reply->readAll());
    }
    reply->deleteLater(); // Команда на удаление
}
