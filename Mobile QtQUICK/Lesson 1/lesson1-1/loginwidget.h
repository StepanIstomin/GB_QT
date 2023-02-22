#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);

signals:
private:
    QLineEdit *passwordEdit;
    QLineEdit *loginEdit;
    QPushButton *okButton;
};

#endif // LOGINWIDGET_H
