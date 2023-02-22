import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Triangle square")
    property real x1: 0
    property real x2: 0
    property real x3: 0
    property real y1: 0
    property real y2: 0
    property real y3: 0
    property real answer: 0

    function areaCount() {
        x1 = xA.text
        x2 = xB.text
        x3 = xC.text
        y1 = yA.text
        y2 = yB.text
        y3 = yC.text
        answer = Math.abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2
        answer = answer.toFixed(2)
        resultAnswer.text = "Площадь: " + answer
    }
    Rectangle {
        id: secondaryFrame
        color: "lightgray"
        anchors.centerIn: parent // Размещение компонента
        radius: 5 // Закругление углов с выбранным радиусом
        width: 600
        height: 440
        property string textColor: "#535353"

        Column {
            anchors.fill: parent // объект занимает все пространство родителя
            padding: 32 // отступы по 4 сторонам от родительского элемента
            spacing: 32 // отступы между элементами
            Text {
                id: text1
                text: qsTr("Введите длины трех сторон треугольника")
            }
            Row {
                spacing: 20 // отступы между элементами
                TextField {
                    id: xA
                    placeholderText: qsTr("А - x")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: xB
                    placeholderText: qsTr("B - x")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: xC
                    placeholderText: qsTr("C - x")
                    color: secondaryFrame.textColor
                }
            }
            Row {
                spacing: 20 // отступы между элементами
                TextField {
                    id: yA
                    placeholderText: qsTr("А - y")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: yB
                    placeholderText: qsTr("B - y")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: yC
                    placeholderText: qsTr("C - y")
                    color: secondaryFrame.textColor
                }
            }
            Row {
                spacing: 20 // отступы между элементами
                Button {
                    id: submitButton
                    width: 200
                    height: 40
                    background: Rectangle {
                        color: parent.down ? "#bbbbbb" : (parent.hovered ? "#d6d6d6" : "#f6f6f6")
                    }
                    text: qsTr("Расчёт")
                    onClicked: areaCount()
                }
                Text {
                    id: resultAnswer
                    text: qsTr("Площадь:")
                }
            }
        }
    }
}
