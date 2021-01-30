import QtQuick 2.0

Row {
    id: appbar
    width: parent.width
    height: 40

    property var aTitle: ""
    property var aAction1: ""
    property var aAction2: ""
    property var aBackButton: 0

    Rectangle {
        anchors.fill: parent
        color: "#fff"
    }

    Text {
        id: back
        text: "<"
        anchors.left: parent.left
        anchors.leftMargin: (aBackButton === 0 ? 0 : 5)
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
        font.bold: true
        visible: aBackButton

        MouseArea {
            anchors.fill: parent

            onClicked: function() {
                view.currentIndex = 0;
            }
        }
    }

    Text {
        id: title
        anchors.left: back.right
        anchors.leftMargin: 10
        text: aTitle
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 15
        font.bold: true
        font.weight: Font.DemiBold
    }

    Text {
        id: action1
        anchors.right: action2.left
        anchors.rightMargin: 15
        text: aAction1
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 13
        font.bold: true
        font.weight: Font.Capitalize

        MouseArea {
            anchors.fill: parent

            onClicked: function() {
                view.currentIndex = 2;
            }
        }
    }

    Text {
        id: action2
        anchors.right: parent.right
        anchors.rightMargin: 8
        text: aAction2
        height: parent.height
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 13
        font.bold: true
        font.weight: Font.Capitalize

        MouseArea {
            anchors.fill: parent

            onClicked: function() {
                view.currentIndex = 1;
            }
        }
    }
}
