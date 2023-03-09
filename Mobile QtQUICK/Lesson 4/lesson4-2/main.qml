import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts
import QtQuick.Controls 2.12
import LinearMNK 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Lesson 4-2")

    LinearMNK{
        id:linearMNK
    }
    ChartView {
        id: chartview
        x: 20
        y: 20
        width: 600
        height: 387

        LineSeries {
            id: lineSeries
            name: "linear dependence"
            color: "red"
            axisX: ValueAxis {
                id:xVL
                titleText: "X"
                min: 0
                max: 220
            }
            axisY: ValueAxis {
                id:yVL
                titleText: "Y"
                min: 0
                max: 30
            }
        }
        ScatterSeries {
            id: scatterSeries
            name: "Raw values"
            color: "blue"
            markerSize: 8
            markerShape: ScatterSeries.MarkerShapeRectangle
        }
        Component.onCompleted: {
            lineSeries.append(0, linearMNK.linearCalc(0));
            lineSeries.append(220, linearMNK.linearCalc(220));
            for (var i =0; i < linearMNK.getSize(); i++) {
                scatterSeries.append(linearMNK.getX(i), linearMNK.getY(i));
            }
        }
    }
}
