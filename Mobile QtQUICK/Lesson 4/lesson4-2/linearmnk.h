#ifndef LINEARMNK_H
#define LINEARMNK_H

#include <QObject>
#include <QtQml/qqml.h>

class LinearMNK : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit LinearMNK(QObject *parent = nullptr);

public slots:
    double linearCalc(int x);
    int getX(int pos);
    int getY(int pos);
    int getSize();

signals:

private:
    std::vector<int> xNumbers{7,31,61,99,140,178,209};
    std::vector<int> yNumbers{13,10,9,10,12,20,26};
    int size;
};

#endif // LINEARMNK_H
