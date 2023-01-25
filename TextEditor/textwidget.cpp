#include "textwidget.h"

TextWidget::TextWidget(QWidget *parent)
    : QWidget{parent}
{
    pTextField = new QTextEdit(this);
    pTextField->resize(800, 600);
}

void TextWidget::setName(QString name)
{
    curName = name;
}

void TextWidget::setPath(QString path)
{
    filePath = path;
}

void TextWidget::setText(QString text)
{
    pTextField->setText(text);
}

void TextWidget::setFont(QFont font)
{
    curFont = font;
}

void TextWidget::setCurAligment(Qt::Alignment a)
{
    curAligment = a;
}

void TextWidget::readOnly(bool ro)
{
    pTextField->setReadOnly(true);
}

void TextWidget::print(QPrinter* printer)
{
    pTextField->print(printer);
}

Qt::Alignment TextWidget::getAligment()
{
    return curAligment;
}

QString TextWidget::name()
{
    return curName;
}

QString TextWidget::path()
{
    return filePath;
}

QString TextWidget::text()
{
    return pTextField->toPlainText();
}

QFont TextWidget::font()
{
    return curFont;
}
