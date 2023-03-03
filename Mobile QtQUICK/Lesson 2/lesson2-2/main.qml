import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson2-2 homework")

    Rectangle {
        id: centerRect
        height: 200
        width: 200
        color: "red"
        anchors.centerIn: parent

        MouseArea {
            id:mouseArea
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if(mouse.button === Qt.LeftButton)
                     parent.color = Qt.rgba(Math.random(),Math.random(),Math.random())
                else if(mouse.button === Qt.RightButton)
                    rotation360.start()
            }
            onDoubleClicked: {
                parent.radius = 200
                rotation360.stop()
            }
        }
        RotationAnimation
           {id: rotation360;
           target: centerRect;
           to: centerRect.rotation + 360;
           duration: 2500
           loops: Animation.Infinite}
    }



}
