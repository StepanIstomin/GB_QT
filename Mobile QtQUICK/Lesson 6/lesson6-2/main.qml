import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "GetAPI.js" as GetInfo

// source - cbr.ru

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 6-2")
    color: "gray"

    Button {
        id: button
        x: 287
        y: 413
        width: 60
        height: 25
        text: qsTr("Convert")
        onClicked: {
            GetInfo.getInfo()
        }
    }

    Column {
        id: column
        x: 21
        y: 18
        width: 600
        height: 400

        Row {
            id: row
            width: 600
            height: 30

            Text {
                text: qsTr("Currency convertation: ")
                font.pixelSize: 12
            }

        }
        Row {
            width: 600
            height: 30

            Text {
                text: qsTr("RUB ")
                font.pixelSize: 12
            }

            TextField {
                id: rubInput
            }
        }
        Row {
            width: 600
            height: 30
            Text {
                text: qsTr("USD ")
                font.pixelSize: 12
            }

            TextField {
                id: usdInput
            }

        }

    }
}
