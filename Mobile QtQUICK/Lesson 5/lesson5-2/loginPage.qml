import QtQuick 2.15
import QtQuick.Controls 2.12

Item {
    Rectangle {
        id: secondaryFrame
        color: "white"
        anchors.centerIn: parent // Размещение компонента внутри родительского
        radius: 5 // Закругление углов с выбранным радиусом
        width: 300
        height: 250
        Component.onDestruction: print("LoginPage destroyed")

        Column {
            anchors.fill: parent
            padding: 32
            spacing: 32
            TextField {
                id: loginTextField
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("Логин")
                color: secondaryFrame.textColor
                // onEnterPressed и onReturnPressed – две кнопки Enter на стандартной клавиатуре
                Keys.onEnterPressed: Check.checkCredentials(loginTextField.text, passwordTextField.text)
                Keys.onReturnPressed: Check.checkCredentials(loginTextField.text, passwordTextField.text)
            }
            TextField {
                id: passwordTextField
                echoMode: TextInput.Password
                anchors.horizontalCenter: parent.horizontalCenter
                placeholderText: qsTr("Пароль")
                color: secondaryFrame.textColor
                Keys.onEnterPressed: Check.checkCredentials(loginTextField.text, passwordTextField.text)
                Keys.onReturnPressed: Check.checkCredentials(loginTextField.text, passwordTextField.text)
            }
            Button {
                id: submitButton
                width: 200
                height: 40
                background: Rectangle {
                    color: parent.down ? "#bbbbbb" :
                    (parent.hovered ? "#d6d6d6" : "#f6f6f6")
                }
                text: qsTr("Вход")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: Check.checkCredentials(loginTextField.text, passwordTextField.text)
            }
        }
    }

    ParallelAnimation{
        id: failAnimation

        SequentialAnimation {
            // Группа анимаций внутри SequentialAnimation будет выполнена последовательно
            PropertyAnimation {
            // Текст внутри полей логина и пароля моментально изменит цвет на темно-красный
            targets: [loginTextField, passwordTextField]
            property: "color"
            to: "dark red"
            duration: 0
            }
            PropertyAnimation {
                // После этого за 400 миллисекунд вернется к обычному цвету
                targets: [loginTextField, passwordTextField]
                property: "color"
                to: secondaryFrame.textColor
                duration: 400
            }
        }

        SequentialAnimation {
            // Подложка secondaryFrame сместится на -5 пикселей относительно центра, затем передвинется на позицию +5, а потом вернётся в исходное положение. Произойдет “потрясывание” формы.
            NumberAnimation { target: secondaryFrame; property:
            "anchors.horizontalCenterOffset"; to: -5; duration: 50 }
            NumberAnimation { target: secondaryFrame; property:
            "anchors.horizontalCenterOffset"; to: 5; duration: 100 }
            NumberAnimation { target: secondaryFrame; property:
            "anchors.horizontalCenterOffset"; to: 0; duration: 50 }
        }

    }
    SequentialAnimation{
        id: successAnimation
        PropertyAnimation {
            targets: [loginTextField, passwordTextField, submitButton]
            property: "opacity"
            to: 0
            duration: 400
        }
        PropertyAnimation {
            target: secondaryFrame
            property: "opacity"
            to: 0
            duration: 600
        }
    }
}
