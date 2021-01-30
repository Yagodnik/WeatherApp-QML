#ifndef HTTPWEATHERDATA_H
#define HTTPWEATHERDATA_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class HttpWeatherData : public QObject
{
    Q_OBJECT
public:
    explicit HttpWeatherData(QObject *parent = nullptr);

    QNetworkAccessManager *manager;

    Q_INVOKABLE QString getDataFromCity(QString id);

public slots:
    void onReceived(QNetworkReply *reply);

private:
    QString apiKey = "38fc95d3e8022eed2ac829478c1d6b18";
};

#endif // HTTPWEATHERDATA_H
