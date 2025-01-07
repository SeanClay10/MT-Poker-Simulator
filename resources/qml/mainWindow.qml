/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines main window UI
 ***********************************************/


import QtQuick
import QtQuick.Controls


ApplicationWindow {
    id: appWindow
    visible: true
    visibility: Window.Maximized
    title: "Poker Sim"
    color: "lightgray"
    minimumWidth: 1280
    minimumHeight: 720

    property alias loader: pageLoader

    Loader {
        id: pageLoader
        anchors.fill: parent
        active: true
        source: "qrc:/resources/qml/mainMenu.qml"
    }

    onClosing: {
        // Added to prevent premature exit warnings
        pageLoader.active = false;
        gameState.clearGameData();
    }
}
