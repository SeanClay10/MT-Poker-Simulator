

/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines tutorial page UI
 ***********************************************/


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Rectangle {
    id: tutorial
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
        anchors.fill: parent

        Label {
            id: title
            text: qsTr("Tutorial")
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

        RowLayout {
            id: contentRowLayout
            spacing: 75
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: Window.width * 0.8
            Layout.preferredHeight: Window.height * 0.75

            Rectangle {
                id: instructionsBox
                Layout.margins: 20
                Layout.preferredWidth: Window.width * 0.4
                Layout.preferredHeight: Window.height * 0.75
                color: "#24741f"
                radius: 50
                border.width: 5

                Text {
                    id: _text
                    color: "#ffffff"
                    text: qsTr("Game Structure: Each player is dealt 2 cards face down and over several rounds, 5 cards are dealt (eventually) face up on the table, these are called community cards. Each round is played with 3 phases. The first phase, the Flop, shows the first 3 community cards, next, the Turn shows the 4th, and finally, the River shows the 5th.\n\nHow To Play: Before hands are dealt, 2 players post small and big blinds (bets). The 2 players on to the immediate left of the dealer are the small and big blind respectively. Usually, the small blind is half the amount of the big blind. Next, hands are dealt and the first betting round takes place. This is called the Preflop, and the first player chooses an action to either call, raise, or fold, then the next player chooses an action until all players have made a decision. Next, the flop phase is in place and players take turns choosing an action again, with the additional option to check. The same process goes for the Turn and River phases. If all phases are completed and there are at least 2 players remaining, the Showdown round occurs and all players must show their hand. The best hand wins and the player takes their winnings.\n\nActions: The call action matches the previous bet placed. The raise action places a bet higher than the current bet. The fold action removes yourself from the current game and makes you ineligible to win the current hand. The check action can only be placed if no betting action has been placed beforehand and simply passes the action to the next player.\n")
                    anchors.fill: parent
                    font.pixelSize: Math.min(parent.width, parent.height) * 0.025
                    padding: 25
                    Layout.preferredWidth: parent.width * 0.9
                    Layout.preferredHeight: parent.height * 0.9
                    wrapMode: Text.WordWrap
                    font.bold: false
                    font.family: "courier new"
                }
            }

            ColumnLayout {
                id: columnLayout
                Layout.preferredWidth: Window.width * 0.8
                Layout.preferredHeight: Window.height * 0.75

                Rectangle {
                    id: ranksBox
                    Layout.preferredWidth: Window.width * 0.45
                    Layout.preferredHeight: Window.height * 0.6
                    color: "#00ffffff"
                    border.width: 0

                    Image {
                        id: ranksImage
                        x: 0
                        y: -629
                        anchors.fill: parent
                        source: "qrc:/resources/images/poker_hand_rankings.png"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                RowLayout {
                    id: rowLayout
                    spacing: 30
                    Layout.margins: 20
                    Layout.alignment: Qt.AlignRight | Qt.AlignTop
                    layoutDirection: Qt.LeftToRight


                    /*
                     * Back button
                     */
                    Button {
                        id: back
                        text: qsTr("Back")
                        font.pixelSize: Window.height * 0.025
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
        }
    }
}
