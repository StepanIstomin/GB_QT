QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    help.cpp \
    main.cpp \
    mainwindow.cpp \
    textwidget.cpp

HEADERS += \
    help.h \
    mainwindow.h \
    textwidget.h

FORMS += \
    help.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

TRANSLATIONS += QtLanguage_ru.ts QtLanguage_en.ts
#TRANSLATIONS += switchlang_ru.ts switchlang_en.ts
CODECFORSRC = UTF-8
