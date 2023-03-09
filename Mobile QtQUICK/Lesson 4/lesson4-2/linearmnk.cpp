#include "linearmnk.h"
#include <QDebug>

LinearMNK::LinearMNK(QObject *parent)
    : QObject{parent}
{
    size = xNumbers.size();
}

double LinearMNK::linearCalc(int x)
{
    int sumXY = 0;
    int sumX2 = 0;
    for (int i = 0; i < size;++i){
        sumXY += xNumbers[i]*yNumbers[i];
        sumX2 += xNumbers[i]*xNumbers[i];
    }
    int sumX = std::accumulate(xNumbers.begin(), xNumbers.end(), 0);
    int sumY = std::accumulate(yNumbers.begin(), yNumbers.end(), 0);
    double a = (size*sumXY - sumX * sumY) / static_cast<double>(size*sumX2 - sumX*sumX);
    double b = (sumY - a*sumX) / size;
    return a * x + b;
}

int LinearMNK::getX(int pos)
{
    return xNumbers[pos];
}

int LinearMNK::getY(int pos)
{
    return yNumbers[pos];
}

int LinearMNK::getSize()
{
    return size;
}
