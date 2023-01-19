#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QContextMenuEvent>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QCursor>
#include <QTimer>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QBrush brush)
public:
    explicit Figure(QObject *parent = nullptr);
    void setBrush(QBrush brush) {this->brush = brush;emit reDraw();}

    setGeometry(int geom);
    setCoord(QPoint coord);
public slots:
    void rotate();

signals:
    void reDraw();

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget) override;
    QRectF boundingRect() const override;

private:
    enum Geometry {RECTANGLE,ELLIPS,STAR};
    Geometry geometry;
    QBrush brush;
    bool rotateFlag = false;
    QTimer* rotateTimer;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // FIGURE_H
