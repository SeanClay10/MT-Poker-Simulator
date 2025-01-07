/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines main menu
 ***********************************************/


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: mainMenu
    width: Window.width
    height: Window.height
    color: "#b6b6b6"

    Image {
        id: pokerBackground
        anchors.fill: parent
        source: "qrc:/resources/images/poker_background.png"
        clip: true
        fillMode: Image.PreserveAspectCrop
    }

    Image {
        id: topLeftLogo
        source: "qrc:/resources/images/rewards.png"
        width: Window.width * 0.08 
        height: Window.height * 0.10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10 
        fillMode: Image.PreserveAspectFit
        opacity: 0.5

        MouseArea {
            anchors.fill: parent // Cover the entire image
            onClicked: {
                pageLoader.source = "qrc:/resources/qml/rewards.qml"
            }
            cursorShape: Qt.PointingHandCursor 
        }
    }

    ColumnLayout {
        id: menuColumnLayout
        anchors.fill: parent

        Label {
            id: title
            color: "#ddffffff"
            text: qsTr("Welcome To Poker Sim!")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.underline: true
            font.bold: true
            font.family: "courier new"
            Layout.preferredHeight: Window.height * 0.2
            Layout.preferredWidth: Window.width * 0.75
            font.pixelSize: Window.height * 0.1
        }

        RowLayout {
            id: contentRowLayout
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: Window.height * 0.75
            Layout.preferredWidth: Window.width * 0.8

            ColumnLayout {
                id: buttonColumnLayout
                spacing: 15
                Layout.fillHeight: true
                Layout.fillWidth: true

                /*
                 * Play game button
                 */
                Button {
                    id: playGameButton
                    text: gameState.inProgress == true ? qsTr("Resume Game") : qsTr("Play Game")
                    font.italic: true
                    font.bold: true
                    font.family: "courier new"
                    icon.color: "#dd000000"
                    Layout.preferredWidth: Window.width * 0.25
                    Layout.preferredHeight: Window.height * 0.1
                    font.pixelSize: Window.height * 0.05

                    onClicked: {

                        if (gameState.inProgress == false) {
                            gameState.initializeGame()
                            pageLoader.source = "qrc:/resources/qml/playGame.qml"
                            gameState.startGame()
                        }
                        else {
                            pageLoader.source = "qrc:/resources/qml/playGame.qml"

                        }
                    }
                }

                /*
                 * Settings button
                 */
                Button {
                    id: settingsButton
                    text: qsTr("Settings")
                    icon.color: "#dd000000"
                    font.italic: true
                    font.family: "courier new"
                    font.bold: true
                    Layout.preferredWidth: Window.width * 0.25
                    Layout.preferredHeight: Window.height * 0.1
                    font.pixelSize: Window.height * 0.05

                    /*
                     * If line has errors, ignore
                     */
                    onClicked: {
                        pageLoader.source = "qrc:/resources/qml/settings.qml"
                    }
                }

                /*
                 * Tutorial button
                 */
                Button {
                    id: tutorialButton
                    text: qsTr("Tutorial")
                    icon.color: "#dd000000"
                    font.italic: true
                    font.family: "courier new"
                    font.bold: true
                    Layout.preferredWidth: Window.width * 0.25
                    Layout.preferredHeight: Window.height * 0.1
                    font.pixelSize: Window.height * 0.05

                    onClicked: {
                        pageLoader.source = "qrc:/resources/qml/tutorial.qml"
                    }
                }

                /*
                 * Stats button
                 */
                Button {
                    id: statsButton
                    text: qsTr("Stats")
                    icon.color: "#dd000000"
                    font.italic: true
                    font.family: "courier new"
                    font.bold: true
                    Layout.preferredWidth: Window.width * 0.25
                    Layout.preferredHeight: Window.height * 0.1
                    font.pixelSize: Window.height * 0.05

                    onClicked: {
                        pageLoader.source = "qrc:/resources/qml/stats.qml"
                    }
                }

                /*
                 * Exit button
                 */
                Button {
                    id: exitButton
                    text: qsTr("Exit")
                    icon.color: "#dd000000"
                    font.italic: true
                    font.family: "courier new"
                    font.bold: true
                    Layout.preferredWidth: Window.width * 0.25
                    Layout.preferredHeight: Window.height * 0.1
                    font.pixelSize: Window.height * 0.05

                    // If line has errors, ignore
                    onClicked: {
                        gameState.clearGameData()
                        Qt.quit() // Ensure the application exits smoothly
                    }
                }
            }

            Rectangle {
                id: logoBox
                Layout.preferredWidth: Window.width * 0.35
                Layout.preferredHeight: Window.height * 0.6
                color: "#00ffffff"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                Image {
                    id: logo
                    anchors.fill: parent
                    source: "qrc:/resources/images/poker_logo.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }
}
