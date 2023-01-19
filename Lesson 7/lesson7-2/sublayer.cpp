#include "sublayer.h"

SubLayer::SubLayer(QObject *parent)
    : QObject{parent} , QGraphicsItem ()
{
    brush.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать
    setPos(0,0); // Координаты
}

QPoint SubLayer::getCoord()
{
    return cursorCoor;
}

void SubLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    //painter->setPen(Qt::NoPen);
    painter->drawRect(0,0,780,540);
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF SubLayer::boundingRect() const
{
    return QRectF (0,0,780,540);
}

void SubLayer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        cursorCoor = event->pos().toPoint();
        emit lClick();
    }
}
