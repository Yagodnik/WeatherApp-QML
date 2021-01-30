QT += quick quickcontrols2
QT += location

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

android: include(/home/artem/Android/Sdk/android_openssl/openssl.pri)

SOURCES += \
        citydataobject.cpp \
        cityfiltermodel.cpp \
        citylistmodel.cpp \
        datastorage.cpp \
        httpweatherdata.cpp \
        main.cpp \
        weather.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    WeatherApp_en_001.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_ABIS = armeabi-v7a arm64-v8a x86 x86_64

HEADERS += \
    citydataobject.h \
    cityfiltermodel.h \
    citylistmodel.h \
    datastorage.h \
    httpweatherdata.h \
    weather.h
