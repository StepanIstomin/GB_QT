#include "figure.h"

Figure::Figure(QObject *parent)
    : QObject{parent} , QGraphicsItem ()
{
    brush.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
    brush.setStyle(Qt::BrushStyle::SolidPattern); // Полностью закрашивать

    geometry = Geometry::RECTANGLE; // Форма по умолчанию
    setPos(0,0); // Координаты по умолчанию

    rotateTimer = new QTimer(this);
    connect(rotateTimer,SIGNAL(timeout()),this,SLOT(rotate()));
}

Figure::setGeometry(int geom)
{
    switch (geom) { // Выбор геометрии
    case 0:
        geometry = Geometry::RECTANGLE;
        break;
    case 1:
        geometry = Geometry::ELLIPS;
        break;
    case 2:
        geometry = Geometry::STAR;
        break;
    default:
        break;
    }
}

Figure::setCoord(QPoint coord)
{
    setPos(coord.x(),coord.y()); // Координаты
}

void Figure::rotate()
{
    this->setRotation(rotation() + 2);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush);
    if(geometry == Geometry::RECTANGLE) painter->drawRect (-100,-50,200,100);
    if(geometry == Geometry::ELLIPS) painter->drawEllipse (-100,-50,200,100);
    if(geometry == Geometry::STAR) {
        QPolygon star;
        star << QPoint(0, 50) << QPoint(10, 10) << QPoint(50, 0) << QPoint(10, -10)
             << QPoint(0, -50) << QPoint(-10, -10) << QPoint(-50, 0) << QPoint(-10, 10);
        painter->drawPolygon(star);
    }
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Figure::boundingRect() const
{
    if(geometry == Geometry::STAR) return QRectF(-50,-50,100,100);
    else return QRectF(-100,-50,200,100);
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {// Левая кнопка, режим перемещения
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
    }
    if (event->button() == Qt::RightButton) delete this; // Правая кнопка, удаление

    if (event->button() == Qt::MiddleButton) {
        rotateFlag = true; // Флаг вращения
        rotateTimer->start(1000/60);
    }
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
        Q_UNUSED(event);
        emit reDraw();
    }
    if (event->button() == Qt::MiddleButton) {
        rotateFlag = false;
        rotateTimer->stop();
    }
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!rotateFlag) {
        this->setPos(mapToScene(event->pos()));
        emit reDraw(); // Переотрисовываем
    }
}
