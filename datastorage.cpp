#include "datastorage.h"

DataStorage::DataStorage(QObject *parent) : QObject(parent)
{
    path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug() << path;

    QDir dir(path);
    if (!dir.exists(path)) {
        qDebug() << "Creating dir";
        dir.mkpath(path);
    }

    file = new QFile(path + "/data.txt");
    if (!file->open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Cant load data!";
        return;
    }
}

DataStorage::~DataStorage()
{
    file->close();
    path = "";
}

void DataStorage::addNewLine(QString data)
{
    QTextStream stream(file);
    QString content = stream.readAll();

    if (content.contains(data)) {
        qDebug() << "Already contain!";
        return;
    }

    stream << data << "\n";
}

QString DataStorage::findCityByName(QString name)
{
    file->seek(0);
    QTextStream stream(file);

    QString line = "";
    QString result = "";
    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.contains(name)) {
            result = line;
            break;
        }
    }

    return result;
}

QString DataStorage::getData(int dataType)
{
    QString result = "";
    file->seek(0);
    QTextStream stream(file);

    switch (dataType) {
    case CITY_NAME:
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" ");

            qDebug() << parts[0];
            result += parts[0];
            result += " ";
        }
        break;
    case CITY_LAT:
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" ");

            result += parts[1];
            result += " ";
        }
        break;
    case CITY_LON:
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" ");

            result += parts[2];
            result += " ";
        }
        break;
    case CITY_ID:
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList parts = line.split(" ");

            result += parts[3];
            result += " ";
        }
        break;
    }

    return result;
}
