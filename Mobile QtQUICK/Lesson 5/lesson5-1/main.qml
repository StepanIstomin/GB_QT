import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 6.3

import "FigureDraw.js" as DrawScript

Window {
    width: 640
    height: 640
    visible: true
    title: qsTr("Lesson 5-1")

    ComboBox {
        id: comboBox
        x: 30
        y: 15
        model: ["Star", "Circle", "House", "Sandglass", ]
        onActivated: {
            //mycanvas.clear();
            mycanvas.requestPaint();
        }
    }


    Canvas {
        id: mycanvas
        anchors.fill: parent
        anchors.topMargin: 0
        property int xStep
        property int yStep
        onPaint: {
            var object = new DrawScript.Coordinates();
            var coord = object.getCoord(comboBox.currentText);
            var params = object.getParams();

            xStep = width / params[1];
            yStep = height / params[2];

            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.fillStyle = Qt.rgba(1, 0, 0, 1); // Красный

            ctx.beginPath()

            if (comboBox.currentText === "Circle") {
                ctx.arc(xStep * coord[0][0],yStep * coord[0][1],xStep * coord[1],0,Math.PI*2,true);
            }
            else {
                for (var i =0; i < params[0]; i++) {
                    if (i == 0){
                        ctx.moveTo(xStep * coord[i][0], yStep * coord[i][1]);
                     }
                    else {
                        ctx.lineTo(xStep * coord[i][0], yStep * coord[i][1]);
                    }
                }
            }
            ctx.closePath()
            ctx.lineWidth = 15;
            ctx.stroke();
            //ctx.fill()
        }
    }
}
