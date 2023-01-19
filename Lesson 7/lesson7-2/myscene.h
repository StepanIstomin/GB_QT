#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class MyScene : public QGraphicsScene
{
public:
    explicit MyScene(QObject *parent = nullptr);

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // MYSCENE_H
