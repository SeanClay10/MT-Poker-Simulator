/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines play game
 ***********************************************/


import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick 2.15
import QtQuick.Controls 2.15


pragma ComponentBehavior: Bound


Rectangle {
    id: playGame
    width: Window.width
    height: Window.height
    Image {
        id: background_image
        anchors.fill: parent
        source: "qrc:/resources/images/poker_background.png"
        fillMode: Image.PreserveAspectCrop
    }

    Rectangle {
        id: buttonBox
        width: 602
        height: 89
        color: "#14541b"
        radius: 25
        border.width: 3
        anchors.left: table_box.right
        anchors.top: table_box.bottom
        anchors.leftMargin: -542
        anchors.topMargin: 207

        RowLayout {
            id: buttonRowLayout
            anchors.fill: parent

            /*
             * Raise button
             */
            RoundButton {
                id: raiseButton
                text: qsTr("Raise")
                font.pixelSize: 18
                font.bold: true
                font.family: "Courier new"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 125
                Layout.preferredHeight: 40
                background: Rectangle {
                    radius: raiseButton.radius
                    color: "white"
                }
                onClicked: {
                    if (gameState.currentPlayer == 0) {
                        gameState.updateRaiseAmount(); // Call the function to update raise amount
                        raiseChipsAmountLoader.active = !raiseChipsAmountLoader.active
                    }
                }
            }


            /*
             * Check or call button
             */
            RoundButton {
                id: checkCallButton
                text: qsTr("Check/Call")
                font.pixelSize: 18
                font.bold: true
                font.family: "Courier new"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 125
                Layout.preferredHeight: 40
                background: Rectangle {
                    radius: checkCallButton.radius
                    color: "white"
                }
                onClicked: {
                    if (gameState.currentPlayer == 0) {
                        gameState.userCheckCall()
                    }
                }
            }


            /*
             * Fold Button
             */
            RoundButton {
                id: foldButton
                text: qsTr("Fold")
                font.pixelSize: 18
                font.bold: true
                font.family: "Courier new"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 125
                Layout.preferredHeight: 40
                background: Rectangle {
                    radius: foldButton.radius
                    color: "white"
                }
                onClicked: {
                    if (gameState.currentPlayer == 0) {
                        gameState.userFold()
                    }
                }
            }

            /*
             * Calculate best choice button
             */
            RoundButton {
                id: calculateButton
                text: qsTr("Calculate")
                font.pixelSize: 18
                font.bold: true
                font.family: "Courier new"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 125
                Layout.preferredHeight: 40
                background: Rectangle {
                    radius: calculateButton.radius
                    color: "white"
                }
                onClicked: {
                    if (gameState.currentPlayer == 0) {
                        gameState.userCalculateAction()
                    }
                    gameState.isRaise() ? raiseButton.background.color = "yellow" : raiseButton.background.color = "white";
                    gameState.isCheckCall() ? checkCallButton.background.color = "yellow" : checkCallButton.background.color = "white";
                    gameState.isFold() ? foldButton.background.color = "yellow" : foldButton.background.color = "white";
                }
            }

        }
    }

    Rectangle {
        id: table_box
        width: 482
        height: 285
        color: "#14541b"
        radius: 100
        border.width: 8
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenterOffset: -64
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: potSizeBox
            color: "#00ffffff"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 90
            anchors.rightMargin: 89
            anchors.topMargin: 13
            anchors.bottomMargin: 202

            /*
             * Pot size amount
             */
            Text {
                id: potSizeText
                color: "#ffffff"
                text: qsTr("Pot: $"+ gameState.potSize)
                anchors.fill: parent
                font.pixelSize: parent.height * 0.5
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.bold: true
                font.family: "courier new"
            }
        }

        Rectangle {
            id: communityCardsBox
            x: 26
            y: 79
            width: 429
            height: 92
            color: "#00ffffff"

            RowLayout {
                id: communityCardLayout
                anchors.fill: parent
                
                /*
                 * Community card 1
                 */
                Rectangle {
                    id: card1Box
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height * 0.9
                    color: "#00ffffff"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                    Image {
                        id: card1
                        anchors.fill: parent
                        source: "qrc:/resources/images/cards/" + gameState.communityCards[0] + ".png"
                        fillMode: Image.PreserveAspectFit
                        Layout.preferredWidth: parent.width * 0.45
                        Layout.preferredHeight: parent.height
                    }
                }

                /*
                 * Community card 2
                 */
                Rectangle {
                    id: card2Box
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height * 0.9
                    color: "#00ffffff"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Image {
                        id: card2
                        anchors.fill: parent
                        source: "qrc:/resources/images/cards/" + gameState.communityCards[1] + ".png"
                        fillMode: Image.PreserveAspectFit
                        Layout.preferredWidth: parent.width * 0.45
                        Layout.preferredHeight: parent.height
                    }
                }

                /*
                 * Community card 3
                 */
                Rectangle {
                    id: card3Box
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height * 0.9
                    color: "#00ffffff"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Image {
                        id: card3
                        anchors.fill: parent
                        source: "qrc:/resources/images/cards/" + gameState.communityCards[2] + ".png"
                        fillMode: Image.PreserveAspectFit
                        Layout.preferredWidth: parent.width * 0.45
                        Layout.preferredHeight: parent.height
                    }
                }

                /*
                 * Community card 4
                 */
                Rectangle {
                    id: card4Box
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height * 0.9
                    color: "#00ffffff"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Image {
                        id: card4
                        anchors.fill: parent
                        source: "qrc:/resources/images/cards/" + gameState.communityCards[3] + ".png"
                        fillMode: Image.PreserveAspectFit
                        Layout.preferredWidth: parent.width * 0.45
                        Layout.preferredHeight: parent.height
                    }
                }

                /*
                 * Community card 5
                 */
                Rectangle {
                    id: card5Box
                    Layout.preferredWidth: parent.width * 0.15
                    Layout.preferredHeight: parent.height * 0.9
                    color: "#00ffffff"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Image {
                        id: card5
                        anchors.fill: parent
                        source: "qrc:/resources/images/cards/" + gameState.communityCards[4] + ".png"
                        fillMode: Image.PreserveAspectFit
                        Layout.preferredWidth: parent.width * 0.45
                        Layout.preferredHeight: parent.height
                    }
                }
            }
        }

        Rectangle {
            id: phaseBox
            color: "#00ffffff"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 19
            anchors.rightMargin: 18
            anchors.topMargin: 175
            anchors.bottomMargin: 55

            /*
             * Phase text
             */
            Text {
                id: phaseText
                color: "#ffffff"
                text: qsTr("Phase: ") + gameState.phase
                anchors.fill: parent
                anchors.leftMargin: 0
                anchors.rightMargin: 0
                anchors.topMargin: 16
                anchors.bottomMargin: -16
                font.pixelSize: parent.height * 0.65
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.family: "courier new"
            }
        }
    }

    Rectangle {
        id: currentBetBox
        color: "#00ffffff"
        width: 180 // Adjusted width
        height: 50
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 65 // Adjusted left margin
        anchors.bottomMargin: 17

        Text {
            id: currentBetText
            color: "#ffffff"
            text: qsTr("Current Bet: $") + gameState.currentBet
            anchors.fill: parent
            font.pixelSize: parent.height * 0.52
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.family: "courier new"
        }
    }

    /*
     * Seats Data
     */
    Repeater{
        model:gameState.numPlayers
        Rectangle {
            id: seat2
            required property int index
            property var position: gameState.position(index)

            width: 356
            height: 125
            color: "#14541b"
            radius: 20
            border.width: 5
            border.color: gameState.currentPlayer == index ? "#09ff00" : (index == 0 ? "#f4d109" : "#000000")
            anchors.verticalCenter: table_box.verticalCenter
            anchors.horizontalCenterOffset: position[0]
            anchors.verticalCenterOffset: position[1]
            anchors.horizontalCenter: table_box.horizontalCenter

            RowLayout {
                id: playerDataRowLayout1
                anchors.fill: parent
                RowLayout {
                    id: handRowLayout1

                    Rectangle {
                        id: handCard1Box1
                        color: "#00ffffff"
                        Image {
                            id: image2
                            anchors.fill: parent
                            source: "qrc:/resources/images/cards/" + gameState.playerCards[index*2] + ".png"
                            fillMode: Image.PreserveAspectFit
                        }
                        Layout.preferredWidth: 60
                        Layout.preferredHeight: 90
                        Layout.fillWidth: false
                        Layout.fillHeight: false
                    }

                    Rectangle {
                        id: handCard2Box1
                        color: "#00ffffff"
                        Image {
                            id: image3
                            anchors.fill: parent
                            source: "qrc:/resources/images/cards/" + gameState.playerCards[index*2+1] + ".png"
                            fillMode: Image.PreserveAspectFit
                        }
                        Layout.preferredWidth: 60
                        Layout.preferredHeight: 90
                        Layout.fillWidth: false
                        Layout.fillHeight: false
                    }
                    Layout.margins: 15
                }

                ColumnLayout {
                    id: textColumnLayout1

                    Text {
                        id: playerChips1
                        color: "#ffffff"
                        text: qsTr("$"+gameState.playerChips[index])

                        font.pixelSize: 30
                        font.family: "Courier new"
                        font.bold: true
                    }

                    Text {
                        id: lastMove1
                        color: "#ffffff"
                        text: gameState.lastMoves[index]
                        font.pixelSize: 30
                        font.family: "Courier new"
                        font.bold: true
                    }
                }
            }
        }
    }

    Rectangle {
        id: settingsButtonBox
        x: 1086
        width: 179
        height: 72
        color: "#14541b"
        radius: 50
        border.width: 2
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: 15
        anchors.topMargin: 24

        RoundButton {
            id: settingsButton
            text: "Settings"
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            anchors.bottomMargin: 10
            font.pixelSize: 18
            font.bold: true
            font.family: "Courier new"
            display: AbstractButton.TextOnly
            onClicked: {
                transparentOverlay.visible = !transparentOverlay.visible
                settingsMenuLoader.active = !settingsMenuLoader.active
            }
        }
    }

    Loader {
        id: raiseChipsAmountLoader
        active: false
        sourceComponent: raiseChipsSlider
        anchors.centerIn: parent
    }

    Component {
        id: raiseChipsSlider

        Rectangle {
            id: chipsSliderBox
            width: 300
            height: 200
            color: "lightgrey"
            border.color: "black"
            border.width: 2

            ColumnLayout {
                id: raiseChipsSliderLayout
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    id: raiseAmountInstructionText
                    text: qsTr("Select Amount")
                    font.pixelSize: 20
                }

                Slider {
                    id: raiseAmount
                    value: 10
                    from: 1
                    to: gameState.raiseAmount // Use the new property
                    onValueChanged: raiseAmountText.text = value.toFixed(0)
                }

                Text {
                    id: raiseAmountText
                    text: raiseAmount.value.toFixed(0)
                    font.pixelSize: 20
                }

                RowLayout {
                    id: raiseAmountButtons
                    Layout.alignment: Qt.AlignBottom

                    Button {
                        id: raiseConfirm
                        text: qsTr("Raise")
                        font.pixelSize: 12
                        onClicked: {
                            // Update raise amount for backend
                            raiseChipsAmountLoader.active = !raiseChipsAmountLoader.active
                            gameState.userRaise(raiseAmount.value)
                            gameState.updateRaiseAmount()
                        }
                    }

                    Button {
                        id: raiseCancel
                        text: qsTr("Cancel")
                        font.pixelSize: 12
                        onClicked: {
                            raiseChipsAmountLoader.active = !raiseChipsAmountLoader.active
                        }
                    }

                }
            }
        }
    }

    Rectangle {
            id: transparentOverlay
            anchors.fill: parent
            opacity: 0.5
            visible: false
    }

    Loader {
        id: settingsMenuLoader
        active: false
        sourceComponent: settingsMenuComponent
        anchors.centerIn: parent
    }

    Loader {
        id: tutorialTextMenuLoader
        active: false
        sourceComponent: tutorialTextMenuComponent
        anchors.centerIn: parent
    }

    Loader {
        id: cardRankMenuLoader
        active: false
        sourceComponent: cardRankMenuComponent
        anchors.centerIn: parent
    }

    Loader {
        id: playAgainLoader
        active: false
        sourceComponent: playAgainComponent; // Unload
        anchors.centerIn: parent
    }

    Component {
        id: tutorialTextMenuComponent

        ColumnLayout {
            id: tutorialTextMenuLayout
            anchors.centerIn: parent

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
                    font.pixelSize: Math.min(parent.width, parent.height) * 0.025
                    anchors.fill: parent
                    padding: 25
                    Layout.preferredWidth: parent.width * 0.9
                    Layout.preferredHeight: parent.height * 0.9
                    wrapMode: Text.WordWrap
                    font.bold: false
                    font.family: "courier new"
                }
            }

            Button {
                id: tutorialTextMenuRemoveButton
                text: qsTr("Back to Game")
                font.pixelSize: 20
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    transparentOverlay.visible = false
                    tutorialTextMenuLoader.active = !tutorialTextMenuLoader.active
                }
            }
        }
    }

    Component {
        id: cardRankMenuComponent

        ColumnLayout {
            id: cardRankMenuLayout
            anchors.centerIn: parent

            Rectangle {
                id: cardRankMenuBox
                Layout.preferredWidth: Window.width * 0.4
                Layout.preferredHeight: Window.height * 0.45
                color: "#24741f"
                radius: 50
                border.width: 5
                
                Image {
                    id: ranksImage
                    x: 0
                    y: -629
                    anchors.fill: parent
                    anchors.margins: 10
                    source: "qrc:/resources/images/poker_hand_rankings.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Button {
                id: cardRankMenuRemoveButton
                text: qsTr("Back to Game")
                font.pixelSize: 20
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    transparentOverlay.visible = false
                    cardRankMenuLoader.active = !cardRankMenuLoader.active
                }
            }
        }
    }

    Component {
        id: settingsMenuComponent

        Rectangle {
            id: settingsMenuBox
            width: 300
            height: 200
            color: "lightgrey"
            border.color: "black"
            border.width: 2

            ColumnLayout {
                id: settingsMenuButtonLayout
                anchors.fill: parent
                anchors.leftMargin: 10

                Button {
                    id: showTutorialButton
                    text: qsTr("Show Tutorial")
                    font.pixelSize: 20
                    onClicked: {
                        settingsMenuLoader.active = !settingsMenuLoader.active
                        tutorialTextMenuLoader.active = !tutorialTextMenuLoader.active
                    }
                }

                Button {
                    id: showRanksButton
                    text: qsTr("Show Hand Ranks")
                    font.pixelSize: 20
                    onClicked: {
                        settingsMenuLoader.active = !settingsMenuLoader.active
                        cardRankMenuLoader.active = !cardRankMenuLoader.active
                    }
                }

                Button {
                    id: backToGameButton
                    text: qsTr("Return to Game")
                    font.pixelSize: 20
                    onClicked: {
                        transparentOverlay.visible = !transparentOverlay.visible
                        settingsMenuLoader.active = !settingsMenuLoader.active
                    }
                }

                Button {
                    id: backButton
                    text: qsTr("Main Menu")
                    font.pixelSize: 20
                    onClicked: {
                        pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
                    }
                }
            }
        }
    }

    Component {
        id: playAgainComponent
        Rectangle {
            id: playAgainMenuBox
            Layout.preferredWidth: Window.width * 0.4
            Layout.preferredHeight: Window.height * 0.45
            color: "#24741f"
            radius: 50
            border.width: 5

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            RowLayout {
                id: buttonRow
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -130
                spacing: 20

                Button {
                    id: playAgainButton
                    text: qsTr("Play Again")
                    font.pixelSize: 20
                    onClicked: {
                        gameState.playAgainSelected()
                        playAgainLoader.active = !playAgainLoader.active; // Unload
                    }
                }
                Button {
                    id: backToMenuButton
                    text: qsTr("Quit")
                    font.pixelSize: 20
                    onClicked: {
                        gameState.quitSelected()
                        playAgainLoader.active = !playAgainLoader.active; // Unload
                        pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
                    }
                }
            }
        }
    }

    Connections {
        target: gameState
        function onPlayAgain() {
            playAgainLoader.active = !playAgainLoader.active; // Reload if needed
        }
        function onUserActionCompleted() {
            raiseButton.background.color = "white";
            checkCallButton.background.color = "white";
            foldButton.background.color = "white";
        }
    }
}
