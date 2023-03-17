import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "GetAPI.js" as GetInfo

// source - weatherbit.io

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 6-3")


    Button {
        id: button
        x: 287
        y: 413
        width: 66
        height: 25
        text: qsTr("Get Data")
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
                text: qsTr("Location: ")
                font.pixelSize: 12
            }

            Text {
                id: city
                text: qsTr("")
                font.pixelSize: 12
            }
        }
        Row {
            width: 600
            height: 30

            Text {
                text: qsTr("weather: ")
                font.pixelSize: 12
            }

            Text {
                id: weather
                text: qsTr("")
                font.pixelSize: 12
            }
        }
        Row {
            width: 600
            height: 30

            Text {
                text: qsTr("temperature: ")
                font.pixelSize: 12
            }

            Text {
                id: temp
                text: qsTr("")
                font.pixelSize: 12
            }
        }
        Row {
            width: 600
            height: 30

            Text {
                text: qsTr("wind: ")
                font.pixelSize: 12
            }

            Text {
                id: wind_cdir_full
                text: qsTr("")
                font.pixelSize: 12
            }
            Text {
                id: wind_spd
                text: qsTr("")
                font.pixelSize: 12
            }
        }
    }
}
