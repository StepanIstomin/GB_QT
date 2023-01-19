#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPoint>
#include <QWheelEvent>
#include <QKeyEvent>
#include "figure.h"
#include "sublayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void reDraw();
    void addFigure();
    void zoom(bool in);

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    int figCount = 0;
    SubLayer* subLayer;
    Figure* figure;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};
#endif // MAINWINDOW_H
