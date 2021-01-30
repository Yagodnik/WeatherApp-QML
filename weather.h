#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = nullptr);

    QString apiKey;
    QFile *cityList;

    QJsonObject findJSONById(QString id);
    QString getWeatherBydId(QString id);
};

#endif // WEATHER_H
