#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QSslSocket>
#include "cityfiltermodel.h"
#include "citylistmodel.h"
#include "weather.h"
#include "datastorage.h"
#include "httpweatherdata.h"
#include "citydataobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();

    CityListModel listModel;
    QFile *file = new QFile(":/citylist.json");
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << "ERROR!!!";
        return 0;
    }

    QByteArray buffer = file->readAll();
    QJsonDocument document = QJsonDocument::fromJson(buffer);
    QJsonArray cityArray = document.array();
    qDebug() << cityArray.count();
    for (int i = 0;i < 30240;i++) {
        //listModel.addId(QString::number(cityArray.at(i).toObject().value("id").toInt()));

        QString name = (cityArray.at(i).toObject().value("name").toString());
        QString id = QString::number(cityArray.at(i).toObject().value("id").toInt());
        QString lat = QString::number(cityArray.at(i).toObject().value("coord").toObject().value("lat").toDouble());
        QString lon = QString::number(cityArray.at(i).toObject().value("coord").toObject().value("lon").toDouble());

        CityDataObject *object = new CityDataObject();
        object->cityId = id;
        object->cityLat = lat;
        object->cityLon = lon;
        object->cityName = name;
        object->index = i;

        listModel.addCityObject(object);
    }

    file->close();

    CityFilterModel filterModel;
    filterModel.setModel(&listModel);
    filterModel.setSourceModel(&listModel);
    filterModel.setFilterRole(Qt::UserRole + 1);
    filterModel.setSortRole(Qt::UserRole + 1);

    qmlRegisterType<DataStorage>("DataStorage", 1, 0, "DataStorage");
    qmlRegisterType<HttpWeatherData>("HttpWeatherData", 1, 0, "HttpWeatherData");

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("material");
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("filterModel", &filterModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
