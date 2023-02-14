#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>

#include "tasklogic.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<TaskLogic>("TaskLogic",1,0,"TaskLogic"); // Регистрация класса для использования в QML файле

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    TaskLogic taskLogic;
    engine.rootContext()->setContextProperty("_taskLogic", &taskLogic);
    engine.rootContext()->setContextProperty("tableModel", taskLogic.getModel());
    engine.load(url);

    return app.exec();
}
