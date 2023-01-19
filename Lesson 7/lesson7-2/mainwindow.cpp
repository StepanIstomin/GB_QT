#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(clock());

    scene = new QGraphicsScene(0,0,780,540,this);
    scene->setSceneRect(0,0,780,540);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    subLayer = new SubLayer(this);
    scene->addItem(subLayer);

    connect(subLayer,SIGNAL(lClick()),this,SLOT(addFigure()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reDraw()
{
    scene->update();
    update();
}

void MainWindow::addFigure()
{
    figure = new Figure(this);
    figure->setGeometry(figCount++);
    if (figCount > 2) figCount = 0;
    figure->setCoord(subLayer->getCoord());
    scene->addItem(figure);
    connect(figure,SIGNAL(reDraw()),this,SLOT(reDraw()));
}

void MainWindow::zoom(bool in)
{
    if (in){
        ui->graphicsView->scale(1.1,1.1);
    }
    else
        ui->graphicsView->scale(0.9,0.9);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Plus)
        zoom(true);
    if (event->key() == Qt::Key_Minus)
        zoom(false);
}
void MainWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
        zoom(true);
    if (event->angleDelta().y() < 0)
        zoom(false);
}
