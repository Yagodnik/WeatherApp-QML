import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

MapQuickItem {
    id: marker
    anchorPoint.x: markerText.width/4
    anchorPoint.y: markerText.height

    property var city: ""
    property var weatherData: "Temperature: 3 *C \nBroken clouds"
    property var pos: QtPositioning.coordinate(0, 0)

    coordinate: pos

    sourceItem: MapMarker {
        id: markerText
        hText: city
        aText: weatherData
    }
}
