import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.LocalStorage 2.12
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0 // Для отображения TableModel

import "DBFunctions.js" as DbFunctions

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 7")

    property int cellHorizontalSpacing: 10

    function dbDraw() {
        var db = LocalStorage.openDatabaseSync("DBExample", "1.0", "Пример локальной базы данных", 1000)
        var tableName = tableNameComBox.currentText
        try {
            db.transaction((tx) => { DbFunctions.readContacts(tx, tableName, table.model) })
        } catch (err) {
            console.log("Error creating or updating table in database: " + err)
        }
    }
    Row {
        id: row
        x: 20
        spacing: 5

        ComboBox {
            id: tableNameComBox
            x: 20
            y: 15
            model: ["contacts", "table2", "table3"]
            onActivated: {
                dbDraw()
            }
        }

        TextField {
            x: 100
            y: 15
            width: 40
            id: textIdEdit
            placeholderText: qsTr("row")
        }

        Button {
            id: button
            y: 15
            text: "Edit entry"
            onClicked: {
                var db = LocalStorage.openDatabaseSync("DBExample", "1.0", "Пример локальной базы данных", 1000)
                try {
                    db.transaction((tx) => { DbFunctions.readEntry(tx, tableNameComBox.currentText, textIdEdit.text) })
                } catch (err) {
                    console.log("Error read table in database: " + err)
                }
                updateDialog.open()
            }
        }
    }

    Column {
        id: column1
        x: 20
        y: 50
        width: 600
        height: 400
        TableModel {
            id: tableModel
            TableModelColumn { display: "id" }
            TableModelColumn { display: "first_name" }
            TableModelColumn { display: "last_name" }
            TableModelColumn { display: "email" }
            TableModelColumn { display: "phone" }
            rows: []



        }
        TableView {
            id: table
            anchors.fill: parent
            columnSpacing: 1
            rowSpacing: 1
            model: tableModel
            ItemSelectionModel {
                id: ism
                model: table.model
            }
            delegate: Rectangle {
                implicitWidth: Math.max(100, /*left*/ cellHorizontalSpacing + innerText.width + /*right*/ cellHorizontalSpacing)
                implicitHeight: 50
                border.width: 1
                Text {
                    id: innerText
                    text: display
                    anchors.centerIn: parent
                }

            }
        }
    }

    Dialog {
        id: updateDialog
        anchors.centerIn: parent
        title: "Update person"
        standardButtons: Dialog.Save | Dialog.Cancel
        Column {
            anchors.fill: parent
            spacing: 5
            TextField {
                id: updateFirstName
            }
            TextField {
                id: updateLastName
            }
            TextField {
                id: updateEmail
            }
            TextField {
                id: updatePhone
            }
        }
        onAccepted: {
            var db = LocalStorage.openDatabaseSync("DBExample", "1.0", "Пример локальной базы данных", 1000)
            try {
                db.transaction((tx) => { DbFunctions.updateEntry(tx, tableNameComBox.currentText, textIdEdit.text)})
            } catch (err) {
                console.log("Error updating table in database: " + err)
            }
            dbDraw()
        }
    }



    Component.onCompleted: {
        //var data_array = ListModel
        /*var tableName = tableNameComBox.currentText
        var db = LocalStorage.openDatabaseSync("DBExample", "1.0", "Пример локальной базы данных", 1000)
        try {
            db.transaction((tx) => { DbFunctions.createSimpleTable(tx, tableName) });
        } catch (err) {
            console.log("Error creating table in database: " + err)
        }
        try {
            db.transaction((tx) => {
            DbFunctions.addContact(tx, tableName, "Smith3", "John", "Johny33@yahoo.com",
            "+3(988)37333112")
            DbFunctions.addContact(tx, tableName, "Pan3", "Peter", "p3p@google.com",
            "+3(977)98373331")
            DbFunctions.addContact(tx, tableName, "Talk3", "Maxim", "max333T@google.com",
            "+3(977)3311111")
            })
        } catch (err) {
            console.log("Error updating table in database: " + err)
        }*/

        dbDraw()
    }
}
