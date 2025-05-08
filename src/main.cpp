

/***********************************
 * Project Name: Poker Simulation
 * File Name: main.cpp
 * Description: Driver/main file for
 *              Poker Sim
 * Date: 11/13/2024
 * Author(s): The NULL Pointers
 ***********************************/


 #include <iostream>
 #include <QGuiApplication>
 #include <QQmlApplicationEngine>
 #include <QObject>
 #include <QQmlContext>
 #include "gameState.h"
 
 
 int main(int argc, char **argv) {
 
     QGuiApplication app(argc, argv);
     QQmlApplicationEngine engine;
 
     srand((unsigned) time(0));
 
     // Expose game data to UI
     GameState gameState;
 
     // Get PATH to main window
     const QUrl url(QStringLiteral("qrc:/resources/qml/mainWindow.qml"));
 
     engine.rootContext()->setContextProperty("gameState", &gameState);
 
     // Link window to engine and error check
     QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                      &app, [url](QObject *obj, const QUrl &objUrl) {
         if (!obj && url == objUrl) {
             qDebug() << "Failed to load QML file";
             QCoreApplication::exit(-1);
         }
     }, Qt::QueuedConnection);
 
     engine.load(url);
 
 
     // Run app
     return app.exec();
 }
 