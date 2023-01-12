#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPrinter>

class TextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextWidget(QWidget *parent = nullptr);
    void setName(QString name);
    void setPath(QString path);
    void setText(QString text);
    void readOnly(bool ro);
    void print(QPrinter* printer);
    QString name();
    QString path();
    QString text();

signals:
private:
    QTextEdit* pTextField;
    QString curName;
    QString filePath;
};

#endif // TEXTWIDGET_H
