#include "parser.h"
#include <QNetworkReply>

Parser::Parser(QObject *parent)
    : QObject{parent}
{
    qnam = new QNetworkAccessManager(this);
    connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotFinished(QNetworkReply*)) );
}

void Parser::download(const QUrl &url)
{
    // url - адрес склеенный из текстового поля
    QNetworkRequest request(url);  // создаем объект для запроса
    QNetworkReply* reply = qnam->get(request); // Выполняем запрос, получаем указатель на объект ответственный за ответ
}

void Parser::slotFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray content= reply->readAll(); // Получаем содержимое ответа
        parsePicUrl(content.data());
        emit done(picUrl);
    }
    else {
        emit error(1);// Выводим описание ошибки, если она возникает.
        qDebug() << "Error in image search";
    }
    reply->deleteLater();  // разрешаем объекту-ответа "удалится"
}

void Parser::parsePicUrl(QString htmlMarkup)
{
    QString fnd = "<a class=\"serp-item__link";
    if (htmlMarkup.contains(fnd, Qt::CaseSensitive)){
        htmlMarkup.remove(0,htmlMarkup.indexOf(fnd));
        QString fnd = "img_url=";
        if (htmlMarkup.contains(fnd, Qt::CaseSensitive)){
            htmlMarkup.remove(0,htmlMarkup.indexOf(fnd)+fnd.length());
            htmlMarkup.remove(htmlMarkup.indexOf("&amp"),htmlMarkup.length()-htmlMarkup.indexOf("&amp"));

            const std::string str = htmlMarkup.toUtf8().constData(); // Для избавления кодировки адреса со знаками % сначала переводим в const std::string
            picUrl = QUrl::fromPercentEncoding(QByteArray::fromStdString(str)); // Убираем %
            qDebug() << "picUrl: " << picUrl;
            return;
        }
    }
    qDebug() << "Error getting url image address";
}
