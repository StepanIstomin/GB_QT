import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import TaskLogic 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Планировщик задач")

    /*TaskLogic{
        id: _taskLogic
    }*/
    onClosing: {
        if (_taskLogic.saveCheck(name.text,deadline.text,progress.text) === ""){
            _taskLogic.insertTask(name.text,deadline.text,progress.text)
        }
        else {
            close.accepted = false
            quitDialog.open()
        }
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
        TextArea {
            id: tasksCount
            Layout.row: 1
            Layout.column: 0
            Layout.leftMargin: 10
            placeholderText: "Количество существующих задач: " + _taskLogic.taskCount()
        }

        SaveButton{
            Layout.row: 1
            Layout.column: 2
            width: 100
            height: 30
            onClicked: {
                if (_taskLogic.saveCheck(name.text,deadline.text,progress.text) === ""){
                    _taskLogic.insertTask(name.text,deadline.text,progress.text)
                    name.text = ""
                    deadline.text = ""
                    progress.text = ""
                    tasksCount.placeholderText = "Количество существующих задач: " + _taskLogic.taskCount()
                }
                else {
                    errorDialog.text = _taskLogic.saveCheck(name.text,deadline.text,progress.text)
                    errorDialog.open()
                }
            }
        }
        Button{
            Layout.row: 2
            Layout.column: 0
            text: "Посмотреть существующие задачи"
            Layout.leftMargin: 10
            width: 250
            height: 30
            onClicked: {
                _taskLogic.getModel()
                tableView.show()
            }
        }
    }
    MessageDialog{
        id: errorDialog
        title: "Ошибка"
        buttons: MessageDialog.Ok
        onAccepted: this.close
    }
    MessageDialog{
        id: quitDialog
        title: "Ошибка"
        text: qsTr("В данных ошибка, хотите исправить перед закрытием?")
        buttons: MessageDialog.Yes | MessageDialog.No
        onAccepted: this.close
        onRejected: Qt.exit(0)
    }


    TaskWindow {
            id: tableView
            title: qsTr("Задачи")
    }
}
