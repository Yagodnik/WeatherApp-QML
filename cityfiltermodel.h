#ifndef CITYFILTERMODEL_H
#define CITYFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>
#include "citylistmodel.h"

class CityFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    CityFilterModel(QObject* parent = 0);

    void setModel(CityListModel *model);

    Q_INVOKABLE void setFilterString(QString string);
    Q_INVOKABLE void setSortOrder(bool checked);
    Q_INVOKABLE QString getCityName(int index);
    Q_INVOKABLE QString getCityLat(int index);
    Q_INVOKABLE QString getCityLon(int index);
    Q_INVOKABLE QString getCityId(int index);
    Q_INVOKABLE QString getIdByCity(QString name);

    CityListModel *model;
};

#endif // CITYFILTERMODEL_H
