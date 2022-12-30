#ifndef PARSECURRENTS_H
#define PARSECURRENTS_H
#include <QString>

class ParseCurrents
{
public:
    ParseCurrents(QString);
    QString parseCur(QString);
private:
    QString text;
};

#endif // PARSECURRENTS_H
