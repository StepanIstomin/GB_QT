import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
//import QtQuick.Dialogs // для MessageDialog
import "GetYear.js" as GetYear

// source numbersapi.com

Window {
    id: root
    width: 1000
    height: 300
    visible: true
    title: qsTr("Lesson 6-1")

    function randomNumber(min, max) {
        return Math.floor(Math.random() * (max - min) + min);
    }

    Item {
        anchors.fill: parent
        ListModel {
            id: model
        }

        ListView {
            id: listview
            anchors.fill: parent
            model: model
            header: Rectangle {
                height: 35
                width: parent.width
                color: "dark green"
                Text {
                    anchors.centerIn: parent
                    text: "Data from server"
                    color: "white"
                }

            }
            delegate: Rectangle {
                width: parent.width
                height: 30
                Text {
                    text: event
                    anchors.centerIn: parent
                }
            }
        }
    }
    Button {
        id: button
        x: 467
        y: 246
        width: 66
        height: 25
        text: qsTr("Get Data")
        onClicked: {
            for (var i = 0; i < 5 ; ++i){
                GetYear.getYearInfo(randomNumber(1, 2023))
            }
        }
    }
}
