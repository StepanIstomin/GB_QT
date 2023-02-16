#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QNetworkAccessManager>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);
    void download(const QUrl &url);
signals:
    void done(const QUrl&);
    void error(int);
private slots:
    void slotFinished(QNetworkReply *reply);
private:
    QNetworkAccessManager* qnam;
    QUrl picUrl;
    void parsePicUrl(QString htmlMarkup);
};

#endif // PARSER_H
