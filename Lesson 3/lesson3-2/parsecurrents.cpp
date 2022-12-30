#include "parsecurrents.h"

ParseCurrents::ParseCurrents(QString txt)
{
    text = txt;
}

QString ParseCurrents::parseCur(QString code){
    QString answer;
    QString fnd = "\"type\":\""+code+"\",\"rate\":";
    if (text.contains(fnd, Qt::CaseSensitive)){
        answer = text;
        answer.remove(0,answer.indexOf(fnd)+20);
        answer.remove(answer.indexOf(",\""),text.length()-answer.indexOf(",\""));
    }else {
        answer = "-";
    }
    return answer;
}
