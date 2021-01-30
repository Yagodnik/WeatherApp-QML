#include "weather.h"

Weather::Weather(QObject *parent) : QObject(parent)
{
    apiKey = "38fc95d3e8022eed2ac829478c1d6b18";
    cityList = new QFile(":/citylist.json");

    if (!cityList->open(QIODevice::ReadOnly)) {
        qDebug() << "Cant open weather list";
        return;
    }
}

QJsonObject Weather::findJSONById(QString id)
{
    QJsonDocument document = QJsonDocument::fromJson(cityList->readAll());
    QJsonArray list = document.array();
    QJsonObject obj;

    for (int i = 0;i < list.count();i++) {
        obj = list.at(i).toObject();
        if (obj.find("id").value() == id.toInt()) {
            qDebug() << "True";
            break;
        }
    }

    return obj;
}

QString Weather::getWeatherBydId(QString id)
{

}
