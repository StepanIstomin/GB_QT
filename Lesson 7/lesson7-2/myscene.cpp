#include "myscene.h"

MyScene::MyScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

/*void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "left click";
        QPoint coord = event->pos().toPoint();
        qDebug() << "x = " << coord.x() << " y = " << coord.y();

        //figure1 = new Figure(figCount++,coord,this);
        figure2 = new Figure(this);
        figure2->setGeometry(1);
        figure2->setCoord(coord);
        scene->addItem(figure2);
        if (figCount > 1) figCount = 0;
    }
}
*/
