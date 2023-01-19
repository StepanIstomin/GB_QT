#ifndef SUBLAYER_H
#define SUBLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QCursor>

class SubLayer : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)
public:
    explicit SubLayer(QObject *parent = nullptr);
    void setBrush(QBrush brush) {this->brush = brush; emit reDraw();}
    QPoint getCoord();

signals:
    void reDraw();
    void lClick();

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget) override;
    QRectF boundingRect() const override;
private:
    QBrush brush;
    QPoint cursorCoor;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // SUBLAYER_H
