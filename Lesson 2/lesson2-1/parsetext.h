#ifndef PARSETEXT_H
#define PARSETEXT_H
#include <QString>
#include <map>

class ParseText
{
public:
    ParseText(QString);
    QString parse();
private:
    QString str;
};

#endif // PARSETEXT_H
