/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines the Rewards page UI
 ***********************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rewardsPage
    width: parent ? parent.width : 800
    height: parent ? parent.height : 600
    color: "#001F3F"  // Dark background for better contrast

    Image {
        id: pokerBackground
        anchors.fill: parent
        source: "qrc:/resources/images/poker_background.png"
        fillMode: Image.PreserveAspectCrop
        opacity: 0.4  // Add transparency for better readability
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // Title
        Label {
            text: qsTr("Rewards")
            font.pixelSize: height * 0.05
            font.bold: true
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        // Charity Rewards Section
        GroupBox {
            title: qsTr("Charity Rewards")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4  // Limit the height of the Charity Rewards section

            ListView {
                id: charityList
                anchors.fill: parent  // Allow the ListView to fill the GroupBox
                spacing: 10  // Ensure consistent spacing between items
                clip: true   // Prevent items from overflowing
                interactive: true

                ScrollBar.vertical: ScrollBar {  // Add a vertical scrollbar
                    policy: ScrollBar.AsNeeded
                }

                model: ListModel {
                    ListElement { siteName: "Red Cross"; siteUrl: "https://www.redcross.org"; rewardText: "Donate here to get +10 chips" }
                    ListElement { siteName: "UNICEF"; siteUrl: "https://www.unicef.org"; rewardText: "Donate here to get +10 chips" }
                    ListElement { siteName: "World Wildlife Fund"; siteUrl: "https://www.worldwildlife.org"; rewardText: "Donate here to get +10 chips" }
                    ListElement { siteName: "Doctors Without Borders"; siteUrl: "https://www.doctorswithoutborders.org"; rewardText: "Donate here to get +10 chips" }
                }

                delegate: RowLayout {
                    width: parent.width * 0.9
                    height: 50  // Fixed height for consistency
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        Layout.fillWidth: true  // Take up remaining space for charity name
                        Layout.preferredWidth: parent.width * 0.6
                        height: parent.height
                        color: "#BB4C5E"
                        radius: 8

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                Qt.openUrlExternally(model.siteUrl);
                                console.log("Charity clicked for " + model.siteName);
                                gameState.setCharityStatus(true)
                            }
                            cursorShape: Qt.PointingHandCursor
                        }

                        Label {
                            anchors.centerIn: parent
                            text: model.siteName
                            color: "#ffffff"
                            font.pixelSize: 16
                            font.bold: true
                        }
                    }

                    Rectangle {
                        Layout.preferredWidth: parent.width * 0.3  // Fixed width for reward box
                        height: parent.height
                        color: "#336699"
                        radius: 8

                        Label {
                            anchors.centerIn: parent
                            text: model.rewardText
                            color: "#000000"
                            font.pixelSize: 14
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }
        }




        // Physical Activity Rewards Section
        GroupBox {
            title: qsTr("Physical Activity Rewards")
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4

            ListView {
                id: activityList
                anchors.fill: parent
                spacing: 10
                clip: true 
                interactive: true

                ScrollBar.vertical: ScrollBar {  
                    policy: ScrollBar.AsNeeded
                }

                model: ListModel {
                    ListElement { activityName: "10,000 Steps"; reward: "+10 chips" }
                    ListElement { activityName: "Yoga Session"; reward: "+10 chips" }
                    ListElement { activityName: "30 Minute Gym Session"; reward: "+10 chips" }
                    ListElement { activityName: "5K Run"; reward: "+10 chips" }
                }

                delegate: RowLayout {
                    width: parent.width * 0.9
                    height: 50  // Fixed height for consistency
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        Layout.fillWidth: true  // Take up remaining space for charity name
                        Layout.preferredWidth: parent.width * 0.6
                        height: parent.height
                        color: "#FFA500"
                        radius: 8

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                console.log("Physical Activity clicked for " + model.activityName);
                                gameState.setPhysicalStatus(true)
                            }
                            cursorShape: Qt.PointingHandCursor
                        }

                        Label {
                            anchors.centerIn: parent
                            text: activityName
                            color: "#ffffff"
                            font.pixelSize: 16
                            font.bold: true
                        }
                    }

                    Rectangle {
                        Layout.preferredWidth: parent.width * 0.3  // Fixed width for reward box
                        height: parent.height
                        color: "#336699"
                        radius: 8

                        Label {
                            anchors.centerIn: parent
                            text: model.reward
                            color: "#000000"
                            font.pixelSize: 14
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }
        }

        // Back Button
        Button {
            text: qsTr("Back")
            font.pixelSize: height * 0.02
            Layout.alignment: Qt.AlignRight
            onClicked: {
                pageLoader.source = "qrc:/resources/qml/mainMenu.qml"
            }
        }
    }
}
