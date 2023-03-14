import QtQuick 2.15
import QtQuick.Controls 2.12
import "LoadScript.js" as Js

Rectangle {
    id: pageTwo
    x: 0
    y: 0
    width: 640
    height: 480
    color: "lightcyan"
    Component.onCompleted: {
        print("page 2 loaded")
        //print("Parent of page 2: " + parent)
    }
    Component.onDestruction: print("page 2 destroyed")

    MouseArea {
        anchors.fill: parent
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 320
        anchors.bottomMargin: 0
        onClicked: {
            Js.createSpriteObjects(mainWindow, "page1")
            //parent.destroy()
        }

        Text {
            id: text1
            x: 158
            y: 191
            width: 324
            height: 98
            text: qsTr("Dynamic page 2")
            font.pixelSize: 40
            font.bold: true
        }
    }
}
