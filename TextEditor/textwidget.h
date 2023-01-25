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
    void setCurAligment(Qt::Alignment a);
    void readOnly(bool ro);
    void print(QPrinter* printer);
    Qt::Alignment getAligment();
    QString name();
    QString path();
    QString text();
    QFont font();

signals:
private:
    QFont curFont;
    QString curName;
    QString filePath;
    Qt::Alignment curAligment;
};

#endif // TEXTWIDGET_H
