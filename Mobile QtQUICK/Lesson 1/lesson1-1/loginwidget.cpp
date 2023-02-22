#include "loginwidget.h"


#include <QLabel>

#include <QBoxLayout>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent}
{
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginEdit = new QLineEdit(this);

    QLabel *passwordLabel = new QLabel(tr("password"),this);
    QLabel *loginLabel = new QLabel(tr("login"),this);

    okButton = new QPushButton(tr("ok"),this);

    QHBoxLayout *passwordLayout = new QHBoxLayout(this);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    QHBoxLayout *loginLayout = new QHBoxLayout(this);
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(loginLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addWidget(okButton);
}
