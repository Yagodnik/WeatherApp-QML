#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QStandardPaths>


class CityObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

public:
    CityObject(QObject *parent = nullptr, QString cName = "") : QObject(parent)
    {
        cityName = cName;
    }

    Q_INVOKABLE QString name() {
        return cityName;
    }

    QString cityName;
signals:
    void nameChanged();

};



class DataStorage : public QObject
{
    Q_OBJECT
public:
    explicit DataStorage(QObject *parent = nullptr);
    ~DataStorage();

    QFile *file;
    QString path;

    static const int CITY_NAME = 1;
    static const int CITY_LAT = 2;
    static const int CITY_LON = 3;
    static const int CITY_ID = 4;

    Q_INVOKABLE void addNewLine(QString data);
    Q_INVOKABLE QString findCityByName(QString name);
    Q_INVOKABLE QString getData(int dataType);
    Q_INVOKABLE void remove(int index);

    Q_INVOKABLE QList<QObject*> getCities();

};

#endif // DATASTORAGE_H
