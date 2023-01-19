#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPrinter>
#include <QFontDialog>

class TextWidget : public QWidget
{
    Q_OBJECT
public:
    QTextEdit* pTextField;

    explicit TextWidget(QWidget *parent = nullptr);
    void setName(QString name);
    void setPath(QString path);
    void setText(QString text);
    void setFont(QFont font);
    void readOnly(bool ro);
    void print(QPrinter* printer);
    QString name();
    QString path();
    QString text();
    QFont font();

signals:
private:
    QFont curFont;
    QString curName;
    QString filePath;
};

#endif // TEXTWIDGET_H
