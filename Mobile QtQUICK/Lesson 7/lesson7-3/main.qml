import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 7-3")

    TCombobox {
        id: tCombobox
        x: 30
        y: 30
        model: ["First", "Second", "Third"]

    }

    Button {
        text: "Show popup"
        onClicked: popup.open()
        x: 200
        y: 30
        width: 100
        height: 30
    }

    Popup {
        id: popup
        x: 200
        y: 100
        width: 200
        height: 200
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background: Rectangle {
            //anchors.fill: parent
            radius: 20
            border.color: "black"
        }
        Text {
            anchors.centerIn: parent
            text: "Rounded popup"
        }
    }
}
