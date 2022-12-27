#include "parsetext.h"

ParseText::ParseText(QString txt)
{
    str = txt;
}
QString ParseText::parse(){
    std::map<QString, QString> specSymbs {
        {"COPYRIGHT", "©"},
        {"PERMILL", "‰"},
        {"TRADEMARK", "®"},
        {"EUR", "€"},
        {"DOLL", "$"},
        {"RUB", "₽"},
    };

    auto search = specSymbs.find(str);
        if (search != specSymbs.end()) {
            return search->second;
        } else {
            return str;
        }
}
