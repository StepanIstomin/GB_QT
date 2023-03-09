#ifndef DIAGRAMLOGIC_H
#define DIAGRAMLOGIC_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QtQml/qqml.h>
#include "PropertyHelper.h"

enum class DiagTypes
  {
    Sin,    // y = sin(x)
    Line,    // y = x
    Abs,  // y = |x - 2.5|
    Square,   // y = x^2
    Log2    // y = log2(x)
  };

class DiagramLogic : public QObject
{
    Q_OBJECT
    QML_ELEMENT // Необходимый макрос

public:
    explicit DiagramLogic(QObject *parent = nullptr);

public slots:
    int getVectorSize();
    double getX(int pos);
    double getY(int pos);
    void diagTypeChange();
    QString diagTypeName();
    QColor diagColor();

    double volMaxMin(QString axis, QString type);
signals:

private slots:
    double vectorYcalc(double x);
    void vectorYfill();
private:
    QVector<double> vectorX;
    QVector<double> vectorY;
    DiagTypes diagramType = DiagTypes::Log2;
    QColor color = Qt::red;
};

#endif // DIAGRAMLOGIC_H
