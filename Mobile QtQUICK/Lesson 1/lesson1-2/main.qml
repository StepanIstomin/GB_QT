import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Triangle square")
    property real p: 0
    property real a: 0
    property real b: 0
    property real c: 0
    property real answer: 0

    function areaCount() {
        a = sideA.text
        b = sideB.text
        c = sideC.text
        p = (a+b+c)/2
        answer = Math.sqrt(p *(p-a)*(p-b)*(p-c))
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
                    id: sideA
                    placeholderText: qsTr("Сторона А")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: sideB
                    placeholderText: qsTr("Сторона B")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: sideC
                    placeholderText: qsTr("Сторона C")
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
