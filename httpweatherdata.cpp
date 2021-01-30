#include "httpweatherdata.h"

HttpWeatherData::HttpWeatherData(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}

QString HttpWeatherData::getDataFromCity(QString id)
{
    QString url = "http://api.openweathermap.org/data/2.5/weather?id=" + id + "&appid=" + apiKey;
    QString result = "";
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, "");
    QObject::connect(reply, SIGNAL(QNetworkReply::finished()), this, SLOT(HttpWeatherData::onReceived(reply)));

    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    timer.start(10000);   // 10 secs. timeout
    loop.exec();

    if(timer.isActive())
    {
        timer.stop();
        if(reply->error() == QNetworkReply::NoError)
        {
            // Success
            QByteArray buffer = reply->readAll();

            qDebug() << "Data:";
            qDebug() << buffer;

            QJsonDocument document = QJsonDocument::fromJson(buffer);
            QJsonObject jsonObject = document.object();

            QJsonArray weatherArray = jsonObject["weather"].toArray();
            QJsonObject weather = weatherArray.at(0).toObject();
            QJsonObject mainData = jsonObject["main"].toObject();

            QString temperature = QString::number(qRound((mainData["temp"].toDouble() - 273.15)));
            result += "Temperature: " + temperature + "\n" + weather["description"].toString();

            return result;
        }
        else
        {
            // handle error
            QString error = reply->errorString();
            qDebug()<< "reply->errorString() " << error;
        }
    }
    else
    {
        disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        reply->abort();
    }

    reply->deleteLater();
}

void HttpWeatherData::onReceived(QNetworkReply *reply)
{
    qDebug() << "Data: ";
    qDebug() << QString::fromStdString(reply->readAll().toStdString());
}
