import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 6.3

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 8")

    Rectangle {
        id: rectangle
        x: (parent.width-width)/2
        y: 60
        width: 200
        height: 200
        color: "#d3b4b4"

        Text {
            id: text1
            x: 20
            y: 30
            text: qsTr("This is lesson 8 app")
            font.pixelSize: 12
        }
    }

    Button {
        id: button
        y: 401
        height: 40
        text: qsTr("Close App")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        display: AbstractButton.TextOnly
        onClicked: Qt.quit()
    }



}
