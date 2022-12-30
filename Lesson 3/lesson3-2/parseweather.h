#ifndef PARSEWEATHER_H
#define PARSEWEATHER_H
#include <QString>

class ParseWeather
{
public:
    ParseWeather(QString);
    QString parse();
private:
    QString text;
};

#endif // PARSEWEATHER_H
