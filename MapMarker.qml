import QtQuick 2.0

Item {
    width: 16
    height: 32

    property var hText: ""
    property var aText: ""

    Item {
        id: text
        width: 128
        height: 54

        anchors.bottom: icon.top
        anchors.bottomMargin: 4

        anchors.horizontalCenter: icon.horizontalCenter

        Rectangle {
            color: "#FFF"
            anchors.fill: parent
            radius: 3
        }

        Text {
            id: headerText
            text: hText
            font.bold: true
            font.pointSize: 9
            font.pixelSize: 9

            anchors.top: text.top
            anchors.topMargin: 1
            anchors.left: text.left
            anchors.leftMargin: 2
        }

        Text {
            id: subText
            text: aText
            font.pointSize: 9

            anchors.top: headerText.bottom
            anchors.left: text.left
            anchors.leftMargin: 2
        }
    }

    Image {
        id: icon
        anchors.fill: parent
        source: "marker.png"
    }
}
