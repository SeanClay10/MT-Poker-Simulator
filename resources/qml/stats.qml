/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines settings stats UI
 ***********************************************/


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: stats
    width: Window.width
    height: Window.height
    color: "#00ffffff"

    Image {
        id: poker_background
        anchors.fill: parent
        source: "qrc:/resources/images/poker_background.png"
        fillMode: Image.PreserveAspectCrop
    }

    ColumnLayout {
        id: contentColumnLayout
        anchors.centerIn: parent

        Label {
            id: title
            text: qsTr("Player Stats")
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.underline: true
            font.bold: true
            font.family: "courier new"
            Layout.preferredHeight: Window.height * 0.2
            Layout.preferredWidth: Window.width * 0.75
            font.pixelSize: Window.height * 0.1
        }

        Rectangle {
            id: statsBox
            Layout.margins: 20
            Layout.preferredWidth: Window.width * 0.4
            Layout.preferredHeight: Window.height * 0.5
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: "#24741f"
            radius: 50
            border.width: 5

            Text {
                id: playerStats
                color: "#ffffff"
                text: gameState.getCurrentPlayerStats() || qsTr("No Player Stats")
                anchors.centerIn: parent
                font.pixelSize: Math.min(parent.width, parent.height) * 0.08
                padding: 25
                Layout.preferredWidth: parent.width * 0.9
                Layout.preferredHeight: parent.height * 0.9
                wrapMode: Text.WordWrap
                font.bold: false
                font.family: "courier new"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            id: back
            text: qsTr("Back")
            font.pixelSize: Window.height * 0.025
            Layout.margins: 20
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            font.italic: true
            font.family: "courier new"
            font.bold: true

            /*
             * Ignore if this line has ERROR/WARNING lines
             */
            onClicked: {
                pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
            }
        }
    }
}
