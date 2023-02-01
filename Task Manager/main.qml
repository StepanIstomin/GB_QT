import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import TaskLogic 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Planner")

    TaskLogic{
        id: _taskLogic
    }
    onClosing: {
        _taskLogic.saveFile(name.text,deadline.text,progress.text)
    }

    GridLayout{
        rows: 3
        columns: 3
        //width: parent.width
        //height: parent.height

        TextField {
            Layout.topMargin: 10
            Layout.leftMargin: 10
            Layout.row: 0
            Layout.column: 0
            id: name
            placeholderText: qsTr("Task name")
            background: Rectangle {
                implicitWidth: 400
                implicitHeight: 25
                color: "white"
                border.color: "gray"
            }

        }
        TextField {
            Layout.topMargin: 10
            Layout.row: 0
            Layout.column: 1
            id: deadline
            placeholderText: qsTr("Deadline date")
            background: Rectangle {
                implicitWidth: 85
                implicitHeight: 25
                color: "white"
                border.color: "gray"
            }
        }
        TextField {
            Layout.topMargin: 10
            Layout.row: 0
            Layout.column: 2
            id: progress
            placeholderText: qsTr("Progress (1-10)")
            background: Rectangle {
                implicitWidth: 115
                implicitHeight: 25
                color: "white"
                border.color: "gray"
            }
        }
        SaveButton{
            Layout.row: 1
            Layout.column: 2
            width: 100
            height: 30
            onClicked: {
                _taskLogic.saveFile(name.text,deadline.text,progress.text)
                name.text = ""
                deadline.text = ""
                progress.text = ""
            }
        }
    }
}
