#ifndef CITYLISTMODEL_H
#define CITYLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QDebug>
#include "citydataobject.h"

enum Roles {
    NameRole = Qt::UserRole + 1,
};

class CityListModel : public QAbstractListModel
{
public:
    explicit CityListModel();

    void addData(const QString &unit);
    void addId(const QString &unit);
    void addCityObject(CityDataObject *object);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QString getId(int index);
    Q_INVOKABLE QString getLat(int index);
    Q_INVOKABLE QString getLon(int index);
    Q_INVOKABLE QString getName(int index);

    QList<CityDataObject *> *dataList = new QList<CityDataObject *>();
protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QStringList m_names;
};

#endif // CITYLISTMODEL_H
