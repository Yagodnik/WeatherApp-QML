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
    QString apiKey = "key here";
};

#endif // HTTPWEATHERDATA_H
