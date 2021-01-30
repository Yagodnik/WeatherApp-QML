#include "citylistmodel.h"

CityListModel::CityListModel()
{

}

void CityListModel::addData(const QString &unit)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_names.append(unit);
    endInsertRows();
}

void CityListModel::addId(const QString &unit)
{
    // ids.append(unit);
}

void CityListModel::addCityObject(CityDataObject *object)
{
    dataList->push_back(object);
    addData(object->cityName);
}

int CityListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataList->count();
}

QVariant CityListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= dataList->count())
        return QVariant();

   // qDebug() << dataList->at(index.row()).cityName;

    const QString &name = m_names[index.row()];
    if (role == NameRole) {
        return name;
    }
    return QVariant();
}

QString CityListModel::getName(int index)
{
    return dataList->at(index)->cityName;
}

QString CityListModel::getId(int index)
{
    return dataList->at(index)->cityId;
}

QString CityListModel::getLat(int index)
{
    return dataList->at(index)->cityLat;
}

QString CityListModel::getLon(int index)
{
    return dataList->at(index)->cityLon;
}

QHash<int, QByteArray> CityListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "name";
    return roles;
}
