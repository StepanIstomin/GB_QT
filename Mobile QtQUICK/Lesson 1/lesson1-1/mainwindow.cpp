#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QBoxLayout>
#include <QLabel>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login = "login";
    password = "password";

    tmr = new QTimer();

    connect(ui->pushButton,SIGNAL(clicked(bool)),SLOT(buttonClicked()));
    connect(ui->loginLineEdit,SIGNAL(returnPressed()),SLOT(buttonClicked()));
    connect(ui->passwordLineEdit,SIGNAL(returnPressed()),SLOT(buttonClicked()));
    connect(tmr, SIGNAL(timeout()), this, SLOT(slotHideItems()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::buttonClicked()
{

    if(checkLP())
        successAnimation();
    else
        failAnimation();

}

bool MainWindow::checkLP()
{
    return ui->loginLineEdit->text() == login && ui->passwordLineEdit->text() == password;
}

void MainWindow::successAnimation()
{
    ui->pushButton->setEnabled(false);
    ui->loginLineEdit->setEnabled(false);
    ui->passwordLineEdit->setEnabled(false);


    auto *animGroup = new QSequentialAnimationGroup(this);

    int min = 0;
    int max = 255;
    int maxDuration = 600;

    {
        auto animation = new QPropertyAnimation(this, "opacityInputItem", this);
        animation->setDuration(400);
        animation->setStartValue(max);
        animation->setEndValue(min);
        animGroup->addAnimation(animation);
    }

    {
        auto animation = new QPropertyAnimation(this, "opacityInputWidget", this);
        animation->setDuration(maxDuration);
        animation->setStartValue(max);
        animation->setEndValue(min);
        animGroup->addAnimation(animation);
    }

    animGroup->insertPause(1,400);
    animGroup->start();

    tmr->setInterval(maxDuration);
    tmr->start();
}

void MainWindow::slotHideItems()
{
    ui->pushButton->hide();
    ui->loginLineEdit->hide();
    ui->passwordLineEdit->hide();
}

void MainWindow::failAnimation()
{
    auto *animGroupOne = new QSequentialAnimationGroup(this);

    QColor defaultColor(83,83,83);
    QColor darkRedColor("dark red");

    {
        auto animation = new QPropertyAnimation(this, "color", this);
        animation->setDuration(0);
        animation->setStartValue(defaultColor);
        animation->setEndValue(darkRedColor);
        animGroupOne->addAnimation(animation);
    }
    {
        auto animation = new QPropertyAnimation(this, "color", this);
        animation->setDuration(400);
        animation->setStartValue(darkRedColor);
        animation->setEndValue(defaultColor);
        animGroupOne->addAnimation(animation);
    }

    animGroupOne->start();

    auto *animGroupSecond = new QSequentialAnimationGroup(this);

    QPoint widgetPos = ui->inputWidget->pos();

    int x = widgetPos.x();
    int y = widgetPos.y();

    {
        auto animation = new QPropertyAnimation(ui->inputWidget, "pos",this);
        animation->setDuration(100);
        animation->setStartValue(QPoint(x, y));
        x+=5;
        animation->setEndValue(QPoint(x, y));
        animGroupSecond->addAnimation(animation);
    }
    {
        auto animation = new QPropertyAnimation(ui->inputWidget, "pos",this);
        animation->setDuration(200);
        animation->setStartValue(QPoint(x, y));
        x-=10;
        animation->setEndValue(QPoint(x, y));
        animGroupSecond->addAnimation(animation);
    }
    {
        auto animation = new QPropertyAnimation(ui->inputWidget, "pos",this);
        animation->setDuration(100);
        animation->setStartValue(QPoint(x, y));
        x+=5;
        animation->setEndValue(QPoint(x, y));
        animGroupSecond->addAnimation(animation);
    }

    animGroupSecond->start();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    QSize windowSize = this->size();
    QSize inputWidgetSize = ui->inputWidget->size();

    QSize newSize =  (windowSize / 2) - (inputWidgetSize / 2);
    QPoint newPos{ newSize.width(),newSize.height()};

    ui->inputWidget->move(newPos);
}


const QColor &MainWindow::color() const
{
    return m_color;
}

void MainWindow::setColor(const QColor &newColor)
{
    QString style = QString("color: rgb(%1, %2, %3);").
                    arg(newColor.red()).
                    arg(newColor.green()).
                    arg(newColor.blue());

    ui->loginLineEdit->setStyleSheet(style);
    ui->passwordLineEdit->setStyleSheet(style);

    m_color = newColor;
}


int MainWindow::opacityInputItem() const
{
    return m_opacityInputItem;
}

void MainWindow::setOpacityInputItem(int newOpacityInputItem)
{
    QString color =  QString("color: rgb(%1, %2, %3, %4); border: none").
                                    arg(m_color.red()).
                                    arg(m_color.green()).
                                    arg(m_color.blue()).
                                    arg((int)newOpacityInputItem);

    ui->loginLineEdit->setStyleSheet(color);
    ui->passwordLineEdit->setStyleSheet(color);
    ui->pushButton->setStyleSheet(color);

    m_opacityInputItem = newOpacityInputItem ;
}

int MainWindow::opacityInputWidget() const
{
    return m_opacityInputWidget;
}

void MainWindow::setOpacityInputWidget(int newOpacityInputWidget)
{

    QString style = QString("background-color: rgb(255, 255, 255, %1);").arg(newOpacityInputWidget);

    ui->inputWidget->setStyleSheet(style);

    m_opacityInputWidget = newOpacityInputWidget;
}
