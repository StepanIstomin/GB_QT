import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Registration form")


    Rectangle {
        id: secondaryFrame
        color: "lightcyan"
        anchors.centerIn: parent // Размещение компонента внутри родительского
        radius: 5 // Закругление углов с выбранным радиусом
        width: 600
        height: 440

        Column {
            anchors.fill: parent // объект занимает все пространство родителя
        Row {
             spacing: 16 // отступы между элементами

            Column {
                id:selfInformation

                padding: 32 // отступы по 4 сторонам от родительского элемента
                spacing: 16 // отступы между элементами

                Label {
                    text: "About you:"
                }

                TextField {
                    id: name
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Name")
                    color: secondaryFrame.textColor
                }

                Row {
                    spacing: 15
                    Label {
                        text: "Sex"
                    }
                    ComboBox {
                        id: sex
                        model: ["Female", "Male"]
                    }
                }

                TextField {
                    id: age
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Age")
                    color: secondaryFrame.textColor
                }

                TextField {
                    id: education
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Level of education")
                    color: secondaryFrame.textColor
                }

                TextField {
                    id: hobby
                     anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Hobby")
                    color: secondaryFrame.textColor
                }

                TextField {
                    id: city
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("City")
                    color: secondaryFrame.textColor
                }
                TextField {
                    id: info
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Briefly about yourself")
                    color: secondaryFrame.textColor
                }
            } // End of Column selfInformation

            Column { // partnerInformation
                id:partnerInformation
                padding: 32 // отступы по 4 сторонам от родительского элемента
                spacing: 16 // отступы между элементами

                Label {
                    text: "About your future partner:"
                }

                Row { // Partner Age
                    spacing: 5
                    Label {
                        text: "Age"
                    }
                    TextField {
                        id: ageFrom
                        placeholderText: qsTr("From")
                        color: secondaryFrame.textColor
                        width: 40
                    }
                    Label {
                        text: " - "
                    }
                    TextField {
                        id: ageTill
                        placeholderText: qsTr("Till")
                        color: secondaryFrame.textColor
                        width: 40
                    }
                }

                Row { // Partner Sex
                    spacing: 15
                    Label {
                        text: "Sex"
                    }
                    ComboBox {
                        id: partSex
                        model: ["Female", "Male"]
                    }
                }

                TextField {
                    id: partEducation
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Level of education")
                    color: secondaryFrame.textColor
                }

            } // End of Column partnerInformation

        } // End of Row with columns
            Button {
                id: regButton
                width: 100
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                //anchors.top: parent.top
                text: qsTr("Registration")
                onClicked: {
                    console.log("User info - name: " + name.text + ", Sex: " + sex.currentText +
                                ", Age: " + age.text + ", Education: " + education.text +
                                ", Hobby: " + hobby.text + ", City: " + city.text +
                                "Brief info: " + info.text)
                    console.log("Partner info - age from: " + ageFrom.text + " till " + ageTill.text +
                                ", Sex: " + partSex.currentText + ", Education: " + partEducation.text)
                }
            }
        } // End of main column
    } //End of Rectangle
} //End of Window


