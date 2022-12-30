#include "parseweather.h"

ParseWeather::ParseWeather(QString txt)
{
    text = txt;
}

QString ParseWeather::parse(){
    QString city;
    QString temp;
    QString tempFeelsLike;
    QString description;
    QString windDescription;
    QString pressure;
    QString humidity;
    QString answer;

    if (text.contains("\"weather\":", Qt::CaseSensitive)){
        text.remove(0,text.indexOf("\"weather\":"));
        text.remove(text.indexOf(",\"near\":"),text.length()-text.indexOf(",\"near\":"));
        city = text;
        city.remove(0,city.indexOf("\"city\":\"")+8);
        city.remove(city.indexOf("\","),text.length()-city.indexOf("\","));
        temp = text;
        temp.remove(0,temp.indexOf("\"temp\":\"")+8);
        temp.remove(temp.indexOf("\","),text.length()-temp.indexOf("\","));
        tempFeelsLike = text;
        tempFeelsLike.remove(0,tempFeelsLike.indexOf("\"tempFeelsLike\":\"")+17);
        tempFeelsLike.remove(tempFeelsLike.indexOf("\","),text.length()-tempFeelsLike.indexOf("\","));
        description = text;
        description.remove(0,description.indexOf("\"description\":\"")+15);
        description.remove(description.indexOf("\","),text.length()-description.indexOf("\","));
        windDescription = text;
        windDescription.remove(0,windDescription.indexOf("\"wind_description\":\"")+20);
        windDescription.remove(windDescription.indexOf("\","),text.length()-windDescription.indexOf("\","));
        pressure = text;
        pressure.remove(0,pressure.indexOf("\"pressure\":\"")+12);
        pressure.remove(pressure.indexOf("\","),text.length()-pressure.indexOf("\","));
        humidity = text;
        humidity.remove(0,humidity.indexOf("\"humidity\":\"")+12);
        humidity.remove(humidity.indexOf("\","),text.length()-humidity.indexOf("\","));

        answer = QString("%1, %2, %3\r\nТемпература: %4, ощущается как %5\r\nДавление: %6\r\nВлажность: %7")
                .arg(city)
                .arg(description)
                .arg(windDescription)
                .arg(temp)
                .arg(tempFeelsLike)
                .arg(pressure)
                .arg(humidity);

    }   else {
       answer = "Информация не найдена";
    }
    return answer;

}
