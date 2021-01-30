import QtQuick 2.15
import QtQuick.Window 2.15
import QtLocation 5.6
import QtQml.Models 2.15
import QtPositioning 5.6
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import DataStorage 1.0
import HttpWeatherData 1.0

Window {
    id: window
    width: 360
    height: 720
    visible: true
    title: qsTr("Hello World")

    property var lastState: 0

    DataStorage {
        id: myData

        Component.onCompleted: {
            //addNewLine("Oslo 59.91 10.75 100");
            if (findCityByName("Oslo") === "") {
                console.log("No such city");
            }
        }
    }

    SwipeView {
        id: view
        anchors.fill: parent
        currentIndex: 0
        interactive: false


        Item {
            HttpWeatherData {
                id: httpWeatherData

                Component.onCompleted: {
                   // console.log("Weather = " + getDataFromCity("536203"));
                }
            }

            Plugin {
                id: mapPlugin
                name: "osm"
            }

            AppBar {
                id: appbar

                aTitle: "Weather"
                aAction1: "CITY LIST"
                aAction2: "ADD CITY"
            }

            Map {
                id: map
                anchors.top: appbar.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                plugin: mapPlugin

                copyrightsVisible: false

                gesture.acceptedGestures: MapGestureArea.PanGesture | MapGestureArea.FlickGesture | MapGestureArea.PinchGesture | MapGestureArea.RotationGesture | MapGestureArea.TiltGesture
                gesture.flickDeceleration: 3000
                gesture.enabled: true

                function initCities() {
                    var cityNames = myData.getData(1).split(" ");
                    var cityLats = myData.getData(2).split(" ");
                    var cityLons = myData.getData(3).split(" ");
                    var cityIdList = myData.getData(4).split(" ");

                    console.log(cityNames)

                    for (var i = 0;i < cityNames.length-1;i++) {
                        var cityName = cityNames[i];
                        var lat  = cityLats[i];
                        var lon  = cityLons[i];
                        var cityId = cityIdList[i];

                        console.log("City = " + cityName);

                        var component = Qt.createComponent("MapMarkerObject.qml");
                        var item = component.createObject(map, {
                            pos: QtPositioning.coordinate(lat, lon),
                            city: cityName,
                            weatherData: httpWeatherData.getDataFromCity(cityId)
                        });

                        map.addMapItem(item);
                    }
                }

                Component.onCompleted: {
                    initCities();
                }
            }
        }

        Item {
            id: selectNewCity

            AppBar {
                id: appbar2
                aTitle: "Add city"
                aBackButton: 1
            }

            Row {
                id: row
                anchors.top: appbar2.bottom
                anchors.left: selectNewCity.left

                width: parent.width
                height: 40

                TextField {
                    id: cityTextField
                    anchors.right: row.right
                    anchors.left: row.left

                    anchors.topMargin: 3
                    anchors.leftMargin: 3
                    anchors.rightMargin: 3

                    onTextChanged: {
                        filterModel.setFilterString(text);
                        filterModel.setSortOrder(true);
                    }
                }
            }


            ListView {
                id: citiesList
                anchors.top: row.bottom
                anchors.bottom: selectNewCity.bottom
                width: parent.width
                anchors.topMargin: 3
                flickableDirection: Flickable.VerticalFlick

                delegate: Rectangle {
                    id: itemRoot
                    width: window.width
                    height: 40
                    property var idV: index

                   //property var cityId: filterModel.getCityId(index)

                    Text {
                        text: name
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: itemRoot.left
                        anchors.leftMargin: 3
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: function() {
                           var iNum = parseInt(filterModel.getIdByCity(name));
                            console.log(filterModel.getCityName(iNum));
                            console.log(filterModel.getCityLat(iNum));
                            console.log(filterModel.getCityLon(iNum));
                            console.log(filterModel.getCityId(iNum));
                            var newCityName = filterModel.getCityName(iNum);
                            var newCityLat = filterModel.getCityLat(iNum);
                            var newCityLon = filterModel.getCityLon(iNum);
                            var newCityId = filterModel.getCityId(iNum);

                            var query = newCityName + " " + newCityLat + " " +
                                        newCityLon + " " + newCityId;

                            myData.addNewLine(query.toString());
                            map.initCities()

                            view.currentIndex = 0;
                        }
                    }
                }

                model: filterModel
            }
        }

        Item {
            AppBar {
                id: appbar3
                aTitle: "Saved cities"
                aBackButton: 1
            }

            ListView {
                id: savedCityList
                anchors.top: appbar3.bottom

                delegate: Rectangle {
                    id: savedItemRoot
                    width: window.width
                    height: 40

                    Text {
                        text: name
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        anchors.left: savedItemRoot.left
                        anchors.leftMargin: 3
                    }

                    Text {
                        text: "-"
                        height: parent.height
                        verticalAlignment: Text.AlignVCenter
                        anchors.right: savedItemRoot.right
                        anchors.rightMargin: 3
                        font.pixelSize: 30
                    }

                    MouseArea {
                        anchors.fill: parent

                        onClicked: function() {
                        }
                    }
                }

                Component.onCompleted: function() {
                    var cityNames = myData.getData(1).split(" ");

                    console.log("Names = " + cityNames.toString())
                    var model1 = Qt.createQmlObject('import QtQuick 2.4; ListModel {}', parent);

                    //append({ name: "111" });
                    for (var j = 0;j < cityNames.length;j++) {
                        var cityName = cityNames[j];

                        model1.append({
                            name: cityName
                        });
                    }

                    model = model1;

                    //WorkerScript.sync();
                }
            }
        }
    }
}
