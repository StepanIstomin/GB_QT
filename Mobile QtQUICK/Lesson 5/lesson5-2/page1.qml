import QtQuick 2.15
import QtQuick.Controls 2.12
import "LoadScript.js" as Js

Rectangle {
    id: pageOne
    x: 0
    y: 0
    width: 640
    height: 480
    color: "peachpuff"
    Component.onCompleted: {
        print("page 1 loaded: " + pageOne)
        //print("Parent of page 1: " + parent)
    }
    Component.onDestruction: print("page 1 destroyed")

    MouseArea {
        anchors.fill: parent
        anchors.leftMargin: 320
        anchors.topMargin: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        onClicked: {
            Js.createSpriteObjects(mainWindow, "page2")
            //parent.destroy()
        }
    }

    Text {
        id: text2
        x: 158
        y: 191
        width: 324
        height: 98
        text: qsTr("Dynamic page 1")
        font.pixelSize: 40
        font.bold: true
    }
}
