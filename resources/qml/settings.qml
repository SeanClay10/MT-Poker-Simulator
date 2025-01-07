

/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines settings page UI
 ***********************************************/


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

pragma ComponentBehavior: Bound


Rectangle {
    id: settings
    width: Window.width
    height: Window.height

    Image {
        id: pokerBackground
        anchors.fill: parent
        source: "qrc:/resources/images/poker_background.png"
        fillMode: Image.PreserveAspectCrop
    }

    ColumnLayout {
        id: contentColumnLayout
        anchors.fill: parent
        spacing: 20

        Label {
            id: title
            text: qsTr("Settings")
            color: "#ddffffff"
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
            id: numberBotsRowLayout
            Layout.preferredWidth: Window.width * 0.75
            Layout.preferredHeight: Window.height * 0.15

            Label {
                id: numberBotsText
                color: "#ddffffff"
                text: qsTr("Number of Bots:")
                font.bold: true
                font.family: "courier new"
                font.pixelSize: Window.height * 0.05
                Layout.leftMargin: 100
                Layout.fillWidth: false
            }

            /*
             * Number of bots slider
             */
            Slider {
                id: botsSlider
                value: gameState.numPlayers - 1
                to: 7
                from: 2
                stepSize: 1
                onValueChanged: botsValue.text = value.toFixed(0)
            }

            /*
             * Number of bots value
             */
            Text {
                id: botsValue
                color: "#ffffff"
                text: botsSlider.value.toFixed(0)
                font.pixelSize: Window.height * 0.04
                Layout.fillWidth: false
                font.bold: true
                font.family: "courier new"
            }
        }

        RowLayout {
            id: startingChipsRowLayout
            Layout.preferredWidth: Window.width * 0.75
            Layout.preferredHeight: Window.height * 0.15

            Label {
                id: startingChipsText
                color: "#ddffffff"
                text: qsTr("Starting Chips Amount:")
                font.bold: true
                font.family: "courier new"
                font.pixelSize: Window.height * 0.05
                Layout.leftMargin: 100
                Layout.fillWidth: false
            }

            /*
             * Starting chips Slider
             */
            Slider {
                id: chipsSlider
                value: gameState.startingChips
                to: 5000
                from: 50
                stepSize: 50
                onValueChanged: {
                    chipsValue.text = value.toFixed(0)
                }
            }

            /*
             * Starting chips value
             */
            Text {
                id: chipsValue
                color: "#ffffff"
                text: chipsSlider.value.toFixed(0)
                font.pixelSize: Window.height * 0.04
                Layout.fillWidth: false
                font.bold: true
                font.family: "courier new"
            }
        }

        RowLayout {
            id: fullscreenRowLayout
            Layout.preferredWidth: Window.width * 0.75
            Layout.preferredHeight: Window.height * 0.15

            Label {
                id: fullscreenText
                color: "#ddffffff"
                text: qsTr("Fullscreen Mode:")
                font.bold: true
                font.family: "courier new"
                font.pixelSize: Window.height * 0.05
                Layout.leftMargin: 100
                Layout.fillWidth: false
            }

            /*
             * Full screen toggle
             */
            CheckBox {
                id: fullscreenCheckBox
                text: qsTr("Toggle")
                font.pixelSize: Window.height * 0.05
                font.italic: true
                font.bold: true
                font.family: "courier new"
                checked: true
            }
        }

        RowLayout {
            id: buttonsRowLayout
            spacing: 50
            Layout.margins: 100
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            /*
             * Apply button
             */
            Button {
                id: apply
                text: qsTr("Apply")
                font.family: "courier new"
                font.italic: true
                font.bold: true
                font.pixelSize: Window.height * 0.025
                onClicked: {
                    // Control fullscreen mode
                    if (fullscreenCheckBox.checked) {
                        appWindow.showFullScreen()
                    }
                    else {
                        appWindow.showNormal()
                    }
                    // Game Settings Reset
                    if (gameState.inProgress) {
                        confirmApplyLoader.active = !confirmApplyLoader.active
                    }
                    else {
                        gameState.setNumPlayers(botsSlider.value + 1)
                        gameState.setStartingChips(chipsSlider.value)
                        pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
                    }
                    gameState.resetPlayerStats()
                }
            }

            /*
             * Back button
             */
            Button {
                id: back
                text: qsTr("Back")
                font.family: "courier new"
                font.italic: true
                font.bold: true
                font.pixelSize: Window.height * 0.025

                /*
                 * Ignore if this line has ERROR/WARNING lines
                 */
                onClicked: {
                        pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
                    }
            }
        }
    }

    Rectangle {
        id: transparentOverlay
        anchors.fill: parent
        opacity: 0.5
        visible: confirmApplyLoader.active
    }

    Loader {
        id: confirmApplyLoader
        active: false
        anchors.centerIn: parent
        sourceComponent: confirmApplyComponent
    }

    Component {
        id: confirmApplyComponent

        Rectangle {
            id: confirmApplyBox
            width: 300
            height: 200
            border.width: 2
            border.color: "black"

            ColumnLayout {
                id: confirmApplyLayout
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    id: confirmGameOverride
                    text: qsTr("Applying Settings Will Wipe The Current Game!")
                    font.pixelSize: 20
                    wrapMode: Text.WordWrap
                    Layout.preferredWidth: parent.width
                }

                RowLayout {
                    id: confirmButtonsLayout
                    Layout.alignment: Qt.AlignBottom

                    Button {
                        id: confirmOverrideButton
                        text: qsTr("Confirm")
                        font.pixelSize: 12
                        onClicked: {
                            // Delete game and update starting game data
                            gameState.clearGameData() 
                            gameState.setNumPlayers(botsSlider.value + 1)
                            gameState.setStartingChips(chipsSlider.value)
                            gameState.resetPlayerStats()
                            confirmApplyLoader.active = !confirmApplyLoader.active
                            pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
                        }
                    }

                    Button {
                        id: cancelButton
                        text: qsTr("Cancel")
                        font.pixelSize: 12
                        onClicked: {
                            confirmApplyLoader.active = !confirmApplyLoader.active
                        }
                    }
                }
            }
        }
    }
}
