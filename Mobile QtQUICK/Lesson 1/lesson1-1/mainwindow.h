#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

#include <QPaintEngine>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(int opacityInputItem READ opacityInputItem WRITE setOpacityInputItem)
    Q_PROPERTY(int opacityInputWidget READ opacityInputWidget WRITE setOpacityInputWidget)
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const QColor &color() const;
    void setColor(const QColor &newColor);

    int opacityInputItem() const;
    void setOpacityInputItem(int newOpacityInputItem);

    int opacityInputWidget() const;
    void setOpacityInputWidget(int newOpacityInputWidget);

private slots:
    void buttonClicked();
    void slotHideItems();

private:
    Ui::MainWindow *ui;

    QString login;
    QString password;

    QColor m_color;

    int m_opacityInputItem;
    int m_opacityInputWidget;

    bool checkLP();
    void successAnimation();

    void failAnimation();

    QTimer *tmr;
protected:
    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
