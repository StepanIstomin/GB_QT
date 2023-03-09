import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts
import QtQuick.Controls 2.12
import DiagramLogic 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 4-1")

    function diagReDraw() {
        yVL.min = diagLogic.volMaxMin("y","min")
        yVL.max = diagLogic.volMaxMin("y","max")
        for (var i = 0; i < diagLogic.getVectorSize(); i++) {
            series.remove(i);
            series.insert(i,diagLogic.getX(i), diagLogic.getY(i));
        }
        series.name = diagLogic.diagTypeName();
    }

    DiagramLogic {
        id: diagLogic
    }

    ChartView {
        id: spline
        x: 20
        y: 20
        width: 600
        height: 387

        LineSeries {
            id: series
            name: diagLogic.diagTypeName()
            color: diagLogic.diagColor()
            axisX: ValueAxis {
                id:xVL
                titleText: "X"
                min: diagLogic.volMaxMin("x","min")
                max: diagLogic.volMaxMin("x","max")
            }
            axisY: ValueAxis {
                id:yVL
                titleText: "Y"
                min: -1
                max: 1
            }
        }

        Component.onCompleted: {
            yVL.min = diagLogic.volMaxMin("y","min")
            yVL.max = diagLogic.volMaxMin("y","max")
            for (var i =0; i < diagLogic.getVectorSize(); i++) {
                series.append(diagLogic.getX(i), diagLogic.getY(i));
            }
        }
    }

    Button {
        id: button
        x: 241
        y: 424
        width: 158
        height: 38
        text: qsTr("Change function")
        onClicked: {
            diagLogic.diagTypeChange()
            diagReDraw()
        }
    }
}
