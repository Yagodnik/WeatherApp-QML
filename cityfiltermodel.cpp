#include "cityfiltermodel.h"

CityFilterModel::CityFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

void CityFilterModel::setModel(CityListModel *model)
{
    this->model = model;
}

void CityFilterModel::setFilterString(QString string)
{
    this->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->setFilterFixedString(string);
}

void CityFilterModel::setSortOrder(bool checked)
{
    if(checked)
    {
        this->sort(0, Qt::DescendingOrder);
    }
    else
    {
        this->sort(0, Qt::AscendingOrder);
    }
}

QString CityFilterModel::getCityName(int index)
{
    return model->getName(index);
}

QString CityFilterModel::getCityLat(int index)
{
    return model->getLat(index);
}

QString CityFilterModel::getCityLon(int index)
{
    return model->getLon(index);
}

QString CityFilterModel::getCityId(int index)
{
    return model->getId(index);
}

QString CityFilterModel::getIdByCity(QString name)
{
    for (int i = 0;i < model->dataList->length();i++) {
        if (name == model->dataList->at(i)->cityName) {
            return QString::number(i);
        }
    }
}

