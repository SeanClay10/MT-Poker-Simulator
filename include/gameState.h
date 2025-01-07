/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file declares the GameState class.
 * Used to record important game information.
 ***********************************************/


#ifndef GAME_STATE_H
#define GAME_STATE_H


#include <QObject>
#include <QString>
#include <QVector>
#include <QEventLoop>
#include <QTimer>
#include "Game.h"


class GameState : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString phase READ phase NOTIFY phaseChanged)
    Q_PROPERTY(int numPlayers READ numPlayers NOTIFY numPlayersChanged)
    Q_PROPERTY(int currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(int potSize READ potSize NOTIFY potSizeChanged)
    Q_PROPERTY(QVector<QString> communityCards READ communityCards NOTIFY communityCardsChanged)
    Q_PROPERTY(QVector<QString> playerCards READ playerCards NOTIFY playerCardsChanged)
    Q_PROPERTY(int startingChips READ startingChips NOTIFY startingChipsChanged)
    Q_PROPERTY(QVector<int> playerChips READ playerChips NOTIFY playerChipsChanged)
    Q_PROPERTY(bool inProgress READ inProgress NOTIFY inProgressChanged)
    Q_PROPERTY(QVector<QString> lastMoves READ lastMoves NOTIFY lastMovesChanged)
    Q_PROPERTY(int activePotsCount READ activePotsCount NOTIFY currentPotChanged)
    Q_PROPERTY(int currentBet READ currentBet WRITE setCurrentBet NOTIFY currentBetChanged)
    Q_PROPERTY(int raiseAmount READ raiseAmount NOTIFY raiseAmountChanged) // Add this line

private:
    // Game Information
    QString m_phase;
    int m_numPlayers;
    int m_potSize;          // DELETE WHEN MAIN AND SIDE POTS DONE, LINK DIRECTLY TO GAME MAIN POT FOR BETTER INTEGRATION
    int m_currentBet;
    Pot* m_mainPot;
    Pot* m_currentPot;
    int lastRaiseIndex; // Add this line
    int m_smallBlindIndex; // Add this line to track the small blind index
    int m_raiseAmount = 0; // Initialize m_raiseAmount
    bool m_charity = false;
    bool m_physical = false;

    QVector<QString> m_communityCards;      // NEED TO MANAGE DISPLAYING CORRECTLY WITH PHASES
    QVector<QString> m_playerCards;         // ONLY MANAGES DISPLAYING CARDS, CAN ADD CHEAT MODE IF WE HAVE TIME
    int m_startingChips;
    QVector<int> m_playerChips;
    bool m_inProgress;
    QVector<QString> m_lastMoves;
    string m_calculatedAction;

    Game* m_game;

public:
    // Mark as explicit to error handle
    GameState(QObject* parent = nullptr);
    ~GameState();

    // Getters
    QString phase() const;
    int numPlayers() const;
    int currentPlayer() const;
    int potSize() const;
    QVector<QString> communityCards() const;
    QVector<QString> playerCards() const;
    int startingChips() const;
    QVector<int> playerChips() const;
    Q_INVOKABLE QVector<int> position(int index) const;
    bool inProgress() const;
    Q_INVOKABLE QString getCurrentPlayerStats() const;
    QVector<QString> lastMoves() const;
    Pot* mainPot() const; // Getter for main pot. Consider changing to int? We could just manage the pot values instead of the whole pot, would also be better for UI
    Pot* currentPot() const; // Getter for current pot
    int currentBet() const;
    int raiseAmount() const; // Add this line
    void manageRound();
    Q_INVOKABLE void resetPlayerStats(); // Add Q_INVOKABLE here
    Q_INVOKABLE void updateRaiseAmount(); // Add this line

public slots:
    // Setters
    void setPhase(const QString &newPhase);
    void setNumPlayers(int numPlayers);
    void setCurrentPlayer(int newPlayer);
    void setPotSize(int potSize);
    void setCommunityCards(const QVector<QString> &communityCards);
    void setPlayerCards(const QVector<QString> &playerCards, bool revealAll = false);
    void setStartingChips(int startingChips);
    void setPlayerChips(const QVector<int> &chips);
    void setInProgress(const bool inProgress);
    void setCalculatedAction(const string &action);
    void setMainPot(Pot* mainPot); // Setter for main pot
    void setCurrentPot(Pot* currentPot); // Setter for current pot
    void setCommunityCardIndex(int index, const QString &card);
    void setPlayerCardsIndex(int index, const QString &card);
    void setPlayerIndexChips(int index, int newChips);
    void setLastMoves(const QVector<QString> &lastMoves);
    void setLastMovesIndex(int index, const QString &lastMove, int raiseAmount = 0);
    void setCurrentBet(int bet);
    void setCharityStatus(bool charity);
    void setPhysicalStatus(bool physical);

    // Action Checkers
    bool isRaise();
    bool isFold();
    bool isCheckCall();

    int activePotsCount() const;

    // Game Functionality Functions
    void initializeGame();
    void runPreFlop();
    void startGame();
    void manageGame();
    void clearGameData();

    // Need to edit these to display last moves for player
    void userCheckCall();
    void userFold();
    void userRaise(int amount);
    void askForNewGame();

    void userCalculateAction();
    void gamePhaseToString();
    QVector<int> getUpdatedChips() const;
    QVector<QString> getNewCommunityCards() const;

signals:
    // Signals For Variable Change, TRY NOT TO USE THESE, USE SETTERS INSTEAD IF POSSIBLE
    void phaseChanged();
    void numPlayersChanged();
    void currentPlayerChanged();
    void potSizeChanged();
    void communityCardsChanged();
    void playerCardsChanged();
    void startingChipsChanged();
    void playerChipsChanged();
    void inProgressChanged();
    void lastMovesChanged();
    void mainPotChanged(); // Signal for main pot change
    void currentPotChanged(); // Signal for current pot change
    void userActionCompleted(); // Signal for user action completion
    void userTurnChanged(bool userTurn); // Signal to indicate if it's the human player's turn
    void currentBetChanged();
    void playAgain();
    void raiseAmountChanged(); // Add this line
    void playAgainSelected();
    void quitSelected();
};


#endif
