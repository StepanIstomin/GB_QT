import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls
import QtQuick.Layouts 1.15

Window {
    id: anotherWindow
    width:480
    height:320
    GridLayout{
        rows: 1
        columns: 1
        TableView {
            Layout.row: 0
            Layout.column: 0
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: tableModel
        }
    }
}
