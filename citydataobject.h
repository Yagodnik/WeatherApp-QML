#ifndef CITYDATAOBJECT_H
#define CITYDATAOBJECT_H

#include <QObject>
#include <QString>

class CityDataObject : public QObject
{
    Q_OBJECT
public:
    CityDataObject(QObject *parent = nullptr);

    QString cityName;
    QString cityLat;
    QString cityLon;
    QString cityId;
    int index;
};

#endif // CITYDATAOBJECT_H
