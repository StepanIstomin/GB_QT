import QtQuick 2.15

BorderImage {
    id: saveButton
    signal clicked
    source: "qrc:///img/button.png"
    width: 100
    height: 30
    Text {
        id: saveButtonText
        text: qsTr("Submit Task")
        anchors.centerIn: parent
    }
    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
        onPressed: {saveButton.source = "qrc:///img/button_p.png"}
        onReleased: {saveButton.source = "qrc:///img/button.png"}
    }
}
