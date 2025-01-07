/***********************************************
 * Project: Poker Sim
 * Authors: The NULL Pointers
 * File Description:
 * This file defines GameState Class functions
 * Note, this imvolves Qt Quick code, some keywords
 * may not be recognizable by IDE
 ***********************************************/


#include "../include/gameState.h"


/*
 * Constructor/Destructor Function Definitions
 */
GameState::GameState(QObject *parent) : QObject(parent),
    // Initialize game state variables
    m_phase("Pre-Flop"),
    m_numPlayers(5),
    m_potSize(0),
    m_currentBet(0),
    m_mainPot(nullptr), // Track the main pot
    m_currentPot(nullptr), // Track the current pot
    m_startingChips(1000),
    m_communityCards({}),
    m_playerCards({}),
    m_playerChips({}),
    m_game(nullptr),
    m_inProgress(false),
    m_lastMoves({}),
    m_calculatedAction(""),
    lastRaiseIndex(-1) // Initialize lastRaiseIndex
{}


GameState::~GameState() {}


/*
 * Getter Function Definitions
 */
QString GameState::phase() const {return this->m_phase;}


int GameState::numPlayers() const {return this->m_numPlayers;}


int GameState::currentPlayer() const {return this->m_game->getCurrentPlayerIndex();}


int GameState::potSize() const {return this->m_potSize;}


Pot* GameState::mainPot() const {return this->m_mainPot;}


Pot* GameState::currentPot() const {return this->m_currentPot;}


QVector<QString> GameState::communityCards() const {return this->m_communityCards;}


QVector<QString> GameState::playerCards() const {return this->m_playerCards;}


int GameState::startingChips() const {return this->m_startingChips;}


QVector<int> GameState::playerChips() const {return this->m_playerChips;}


bool GameState::inProgress() const {return this->m_inProgress;}


QVector<QString> GameState::lastMoves() const {return this->m_lastMoves;}


QString GameState::getCurrentPlayerStats() const {
    // Get player stats and update UI
    if (m_game && !m_game->getPlayers().empty() && m_game->getPlayers()[0]) {
        return QString::fromStdString(m_game->getPlayers()[0]->getStats().getStatsAsString());
    }
    return "No Player Stats";
}

int GameState::currentBet() const {
    return m_currentBet;
}

int GameState::raiseAmount() const {
    return m_raiseAmount;
}

/*
 * Setter function definitions
 */
void GameState::setPhase(const QString &newPhase) {
    // Might change this according to Game object game phase instead for better integration
    if (m_phase != newPhase) {
        m_phase = newPhase;
        emit phaseChanged();
    }
}


void GameState::setNumPlayers(int numPlayers) {
    if (m_numPlayers != numPlayers) {
        m_numPlayers = numPlayers;      // Account for human player
        emit numPlayersChanged();
    }
}


void GameState::setCurrentPlayer(int newPlayer) {
    if (this->m_game->getCurrentPlayerIndex() != newPlayer) {
        this->m_game->setCurrentPlayerIndex(newPlayer);
        emit currentPlayerChanged();
        emit userTurnChanged(newPlayer == 0); // Emit signal to indicate if it's the human player's turn
    }
}


void GameState::setPotSize(int potSize) {
    if (m_potSize != potSize) {
        m_potSize = potSize;
        emit potSizeChanged();
    }
}


void GameState::setMainPot(Pot* mainPot) {
    if (m_mainPot != mainPot) {
        m_mainPot = mainPot;
        emit mainPotChanged();
    }
}

void GameState::setCurrentPot(Pot* currentPot) {
    if (m_currentPot != currentPot) {
        m_currentPot = currentPot;
        emit currentPotChanged();
    }
}

void GameState::setCommunityCards(const QVector<QString> &communityCards) {
    if (m_communityCards != communityCards) {
        m_communityCards = communityCards;
        int remainingCards = 5 - m_communityCards.size();
        for (int i = 0; i < remainingCards; ++i) {
            m_communityCards.append("blank_card");
        }
        emit communityCardsChanged();
    }
}


void GameState::setPlayerCards(const QVector<QString> &playerCards, bool revealAll) {
    QVector<QString> newCards;
    if (revealAll) {
        for (int i = 0; i < m_numPlayers; ++i) {
            newCards.append(QString::fromStdString(m_game->getPlayers()[i]->getHand()[0].toString()));
            newCards.append(QString::fromStdString(m_game->getPlayers()[i]->getHand()[1].toString()));
        }
    } else {
        newCards.append(playerCards);
        for (int i = playerCards.size() / 2; i < m_numPlayers; ++i) {
            newCards.append("back_card");
            newCards.append("back_card");
        }
    }
    if (m_playerCards != newCards) {
        m_playerCards = newCards;
        emit playerCardsChanged();
    }
}


void GameState::setStartingChips(int startingChips) {
    if (m_startingChips != startingChips) {
        m_startingChips = startingChips;
        emit startingChipsChanged();
    }
}


void GameState::setPlayerChips(const QVector<int> &chips) {
    if (m_playerChips != chips) {
        m_playerChips = chips;
        emit playerChipsChanged();
    }
}


void GameState::setInProgress(const bool inProgress) {
    if (m_inProgress != inProgress) {
        m_inProgress = inProgress;
        emit inProgressChanged();
    }
}


void GameState::setCommunityCardIndex(int index, const QString &card) {
    if (index >= 0 && index < 5) {
        m_communityCards[index] = card;
        emit communityCardsChanged();
    }
}


void GameState::setPlayerCardsIndex(int index, const QString &card) {
    if (index >= 0 && index < m_numPlayers * 2) {
        m_playerCards[index] = card;
        emit playerCardsChanged();
    }
}


void GameState::setPlayerIndexChips(int index, int newChips) {
    if (index >= 0 && index < m_playerChips.size()) {
        m_playerChips[index] = newChips;
        emit playerChipsChanged();
    }
}


void GameState::setLastMoves(const QVector<QString> &lastMoves) {
    if (m_lastMoves != lastMoves) {
        m_lastMoves = lastMoves;
        emit lastMovesChanged();
    }
}


void GameState::setLastMovesIndex(int index, const QString &lastMove, int raiseAmount) {
    if (index >= 0 && index < m_lastMoves.size()) {
        if (lastMove == "fold") {
            m_lastMoves[index] = "Fold";
        } else if (lastMove == "check") {
            m_lastMoves[index] = "Check";
        } else if (lastMove == "call") {
            m_lastMoves[index] = "Call";
        } else if (lastMove == "raise") {
            m_lastMoves[index] = "Raise $" + QString::number(raiseAmount);
        } else {
            m_lastMoves[index] = lastMove;
        }
        emit lastMovesChanged();
    }
}

void GameState::setCalculatedAction(const string &action) {
    if (m_calculatedAction != action) {
        m_calculatedAction = action;
    }
}

void GameState::setCurrentBet(int bet) {
    if (m_currentBet != bet) {
        m_currentBet = bet;
        emit currentBetChanged();
    }
}

int GameState::activePotsCount() const {
    int count = 0;
    Pot* pot = m_mainPot;
    while (pot) {
        count++;
        pot = pot->getNextPot();
    }
    return count;
}

void GameState::setCharityStatus(bool charity) {
    this->m_charity = charity;
}

void GameState::setPhysicalStatus(bool physical) {
    this->m_physical = physical;
}

/*
 * Action Check Functions
 */
bool GameState::isRaise() {return m_calculatedAction == "raise";}


bool GameState::isCheckCall() {return m_calculatedAction == "check" || m_calculatedAction == "call";}


bool GameState::isFold() {return m_calculatedAction == "fold";}


/*
 * Game Functionality Function Definitions
 */
void GameState::initializeGame() {
    // Create new game
    this->m_game = new Game(this->m_numPlayers, this->m_startingChips, this->m_charity, this->m_physical);

    // Initialize data
    this->m_communityCards.fill("blank_card", 5);
    emit communityCardsChanged();

    this->m_playerCards.fill("back_card", 2 * m_numPlayers);
    emit playerCardsChanged();

    this->m_lastMoves.fill("N/A", m_numPlayers);
    emit lastMovesChanged();

    setPlayerChips(getUpdatedChips());

    // Set main and current pots
    setMainPot(m_game->getTable().getMainPot());
    setCurrentPot(m_game->getTable().getCurrentPot());

    this->m_smallBlindIndex = rand() % this->m_numPlayers; // Set small blind index to a random player
}


void GameState::startGame() {
    bool playAgain = false;


    do {
        setInProgress(true);

        // Reset Round Data and deal 
        m_game->startNewRound();

        // Shows only the first player's cards
        QVector<QString> firstPlayerCards({
            QString::fromStdString(m_game->getPlayers()[0]->getHand()[0].toString()),
            QString::fromStdString(m_game->getPlayers()[0]->getHand()[1].toString())
        });
        setPlayerCards(firstPlayerCards, false);

        // Manages reset of the round until a winner is determined
        manageGame();

        QEventLoop loop;

        // Connect options for user
        QObject::connect(this, &GameState::playAgainSelected, &loop, [&]() {
            playAgain = true;
            loop.quit();
        });
        QObject::connect(this, &GameState::quitSelected, &loop, [&]() {
            playAgain = false;
            loop.quit();
        });
        // Keep user in loop until one option is selected
        loop.exec();

        clearGameData();
    } while (playAgain);
}

void GameState::askForNewGame(){
    m_game->resetData();
    emit playAgain();
}

void GameState::manageGame() {
    setCurrentPlayer(m_smallBlindIndex); // Set current player to the small blind index
    runPreFlop();

    // Run game until SHOWDOWN phase
    while (m_game->getGamePhase() != SHOWDOWN) {
        manageRound();
    }

    emit playAgain();

    // Reveal player cards
    m_game->proceedToNextPhase();
    setCommunityCards(getNewCommunityCards());
    gamePhaseToString();
    setPlayerCards({}, true);

    // Update all players' chips with every player's current chips
    setPlayerChips(getUpdatedChips());
    m_smallBlindIndex = (m_smallBlindIndex + 1) % m_numPlayers; // Increment small blind index by 1
}


void GameState::runPreFlop() {
    // Delay
    QEventLoop loop;
    QTimer::singleShot(2000, &loop, &QEventLoop::quit);
    loop.exec();

    // Run Pre-Flop
    int bigBlindIndex = (m_smallBlindIndex + 1) % numPlayers();
    int littleBlindAmount = 5;
    int bigBlindAmount = 2 * littleBlindAmount;

    // Little blind bet
    setCurrentPlayer(m_smallBlindIndex);

    // Delay
    QTimer::singleShot(750, &loop, &QEventLoop::quit);
    loop.exec();

    m_game->getTable().addToPot(littleBlindAmount, m_game->getPlayers()[m_smallBlindIndex]);
    m_game->getPlayers()[m_smallBlindIndex]->setLastBet(littleBlindAmount);

    // Update UI
    setPotSize(m_game->getTotalChipsInAllPots());
    setPlayerIndexChips(m_smallBlindIndex, m_game->getPlayers()[m_smallBlindIndex]->getChips());
    setLastMovesIndex(m_smallBlindIndex, "Small: $5", 0);
    setCurrentBet(littleBlindAmount); // Update current bet

    // Big blind bet
    setCurrentPlayer(bigBlindIndex);

    // Delay
    QTimer::singleShot(750, &loop, &QEventLoop::quit);
    loop.exec();
    m_game->getTable().addToPot(bigBlindAmount, m_game->getPlayers()[bigBlindIndex]);
    m_game->getPlayers()[bigBlindIndex]->setLastBet(bigBlindAmount);

    // Update UI
    setPotSize(m_game->getTotalChipsInAllPots());
    setPlayerIndexChips(bigBlindIndex, m_game->getPlayers()[bigBlindIndex]->getChips());
    setLastMovesIndex(bigBlindIndex, "Big: $10", 0);
    setCurrentBet(bigBlindAmount); // Update current bet

    // Move to next player
    setCurrentPlayer((bigBlindIndex + 1) % m_numPlayers);

    // Set current bet
    m_game->setCurrentBet(bigBlindAmount);
}


void GameState::manageRound() {
    // Get starting player index
    lastRaiseIndex = -1;
    int startingPlayerIndex = currentPlayer();
    bool roundEnded = false;

    // Run round until current player gets back around to last raise index
    while (!roundEnded) {
        // Check if all players have folded except one
        int activePlayers = 0;
        for (Player* player : m_game->getPlayers()) {
            if (!player->hasFolded() && player->getChips() > 0) {
                activePlayers++;
            }
        }
        if (activePlayers == 1) {
            while (m_game->getGamePhase() != SHOWDOWN) {
                m_game->proceedToNextPhase();
            }
            break;
        }

        Player& currentPlayer = *(m_game->getPlayers()[this->currentPlayer()]);

        // Handle player actions if they have not folded and have chips
        if (!currentPlayer.hasFolded() && currentPlayer.getChips() > 0) {
            if (AI* aiPlayer = dynamic_cast<AI*>(&currentPlayer)) {
                // Add a 1-second delay before each AI player action
                QEventLoop loop;
                QTimer::singleShot(1000, &loop, &QEventLoop::quit);
                loop.exec();

                // AI player's turn
                aiPlayer->calculateAction(m_game->getTable().getCommunityCards(), m_game->getCurrentBet(), m_game->getTable().getMainPot()->getChips(), *m_game);
                aiPlayer->doAction(*m_game);

                // Update UI
                setPotSize(m_game->getTotalChipsInAllPots());
                setPlayerIndexChips(m_game->getCurrentPlayerIndex(), currentPlayer.getChips());
                setLastMovesIndex(m_game->getCurrentPlayerIndex(), QString::fromStdString(aiPlayer->getCalculatedAction()), aiPlayer->getRaiseAmount());
                setCurrentBet(m_game->getCurrentBet()); // Update current bet

                // If the AI raised, update the last raise index
                if (aiPlayer->getCalculatedAction() == "raise") {
                    lastRaiseIndex = m_game->getCurrentPlayerIndex();
                }
            } else {
                // Human player's turn
                QEventLoop loop;
                connect(this, &GameState::userActionCompleted, &loop, &QEventLoop::quit);
                loop.exec();

                // Update UI after human player's action
                setPotSize(m_game->getTotalChipsInAllPots());
                setPlayerIndexChips(m_game->getCurrentPlayerIndex(), currentPlayer.getChips());
            }
        }
        // Move to the next player
        setCurrentPlayer((m_game->getCurrentPlayerIndex() + 1) % numPlayers());

        // If the round has come back to the starting player and no raises have been made, end the round
        if (m_game->getCurrentPlayerIndex() == startingPlayerIndex && lastRaiseIndex == -1) {
            roundEnded = true;
        }

        // If the last raise index is reached, end the round
        if (lastRaiseIndex != -1 && m_game->getCurrentPlayerIndex() == lastRaiseIndex) {
            roundEnded = true;
        }

        // If a player has gone all in, give other players a chance to call or fold
        if (m_game->getGamePhase() != SHOWDOWN && !roundEnded && m_game->getPlayerWentAllIn()) {
            for (Player* player : m_game->getPlayers()) {
                if (!player->hasFolded() && player->getChips() > 0 && player->getLastBet() != m_game->getCurrentBet()) {
                    if (AI* aiPlayer = dynamic_cast<AI*>(player)) {
                        // Add a 1-second delay before each AI player action
                        QEventLoop loop2;
                        QTimer::singleShot(1000, &loop2, &QEventLoop::quit);
                        loop2.exec();
                        aiPlayer->calculateAction(m_game->getTable().getCommunityCards(), m_game->getCurrentBet(), m_game->getTable().getMainPot()->getChips(), *m_game);
                        aiPlayer->doAction(*m_game);

                        // Update UI
                        setPotSize(m_game->getTotalChipsInAllPots());
                        setPlayerIndexChips(m_game->getCurrentPlayerIndex(), player->getChips());
                        setLastMovesIndex(m_game->getCurrentPlayerIndex(), QString::fromStdString(aiPlayer->getCalculatedAction()), aiPlayer->getRaiseAmount());
                        setCurrentBet(m_game->getCurrentBet()); // Update current bet
                    } else {
                        // Human player's turn
                        QEventLoop loop2;
                        connect(this, &GameState::userActionCompleted, &loop2, &QEventLoop::quit);
                        loop2.exec();

                        // Update UI after human player's action
                        setPotSize(m_game->getTotalChipsInAllPots());
                        setPlayerIndexChips(m_game->getCurrentPlayerIndex(), player->getChips());
                    }
                }
            }
        }

        // Create a side pot if a player went all-in
        if (m_game->getPlayerWentAllIn()) {
            m_game->getTable().createSidePot(m_game->getPlayers());
            m_game->setPlayerWentAllIn(false);
        }

        // Proceed to the next phase if the game is not in SHOWDOWN and the round has ended
        if (roundEnded && m_game->getGamePhase() != SHOWDOWN) {
            m_game->proceedToNextPhase();
            // Update game phase
            gamePhaseToString();
            // Update community cards
            setCommunityCards(getNewCommunityCards());
        }
    }
}


void GameState::clearGameData() {
    if (this->m_game == nullptr || inProgress() == false) return;

    // Reset Game State Data
    setPhase("Pre-Flop");
    setPotSize(0);
    setStartingChips(1000);
    setInProgress(false);
    setCalculatedAction("");
    setCurrentBet(0);

    // Iterate through every player and set their chips to 50 if their chips are 0
    for (int i = 0; i < m_game->getPlayers().size(); ++i) {
        Player* player = m_game->getPlayers()[i];
        if (player->getChips() < 50) {
            player->setChips(50);
        }
    }
    setPlayerChips(getUpdatedChips());

    // Initialize data
    this->m_communityCards.fill("blank_card", 5);
    emit communityCardsChanged();

    this->m_playerCards.fill("back_card", 2 * m_numPlayers);
    emit playerCardsChanged();

    this->m_lastMoves.fill("N/A", m_numPlayers);
    emit lastMovesChanged();

    m_game->resetData();

    // Set main and current pots
    setMainPot(m_game->getTable().getMainPot());
    setCurrentPot(m_game->getTable().getCurrentPot());
}


/*
 * Signal Function Definitions for Game Functionality
 */
void GameState::userRaise(int amount) {
    if (m_game) {
        Player* player = m_game->getPlayers()[0]; // Retrieve the current player
        
        m_game->playerRaise(*player, amount);

        setPotSize(m_game->getTotalChipsInAllPots());
        setPlayerIndexChips(0, player->getChips());
        setLastMovesIndex(0, "raise", amount);
        setCurrentBet(m_game->getCurrentBet()); // Update current bet

        // Update last raise index
        lastRaiseIndex = 0;

        emit userActionCompleted();
    }
}


void GameState::userCheckCall() {
    if (m_game) {
        Player* player = m_game->getPlayers()[0]; // Retrieve the current player
        int lastBet = player->getLastBet();
        int currentBet = m_game->getCurrentBet();

        if (lastBet != currentBet) {
            m_game->playerCall(*player);
            setLastMovesIndex(0, "Call");
        } else {
            m_game->playerCheck(*player);
            setLastMovesIndex(0, "Check");
        }

        setPotSize(m_game->getTotalChipsInAllPots());
        setPlayerIndexChips(0, player->getChips());

        emit userActionCompleted();
    }
}


void GameState::userFold() {
    if (m_game) {
        Player* player = m_game->getPlayers()[0]; // Retrieve the current player
        m_game->playerFold(*player);
        setLastMovesIndex(0, "Fold");

        emit userActionCompleted();
    }
}


void GameState::userCalculateAction() {
    if (m_game) {
        Player* player = m_game->getPlayers()[0]; // Retrieve the current player
        // Temporarily turn the player into an AI to get the calculated action
        AI tempAI(player->getChips(), 0.0f); // Base answer on stats alone
        tempAI.setLastBet(player->getLastBet()); // Set the last bet for tempAI

        m_calculatedAction = tempAI.calculateAction(m_game->getTable().getCommunityCards(),
                                                    m_game->getCurrentBet(),
                                                    m_game->getTable().getMainPot()->getChips(),
                                                    *m_game);
        return;
    }
}


QVector<int> GameState::position(int index) const {
    const double startingAngle = M_PI / 2.0;
    const double angle = startingAngle + (2.0 * M_PI / m_numPlayers) * index;
    const int xradius = 550;
    const int yradius = 270;

    int x = static_cast<int>(xradius * cos(angle));
    int y = static_cast<int>(yradius * sin(angle));

    return QVector<int>{x, y};
}


void GameState::gamePhaseToString() {
    switch (m_game->getGamePhase()) {
        case PRE_FLOP:
            setPhase("Pre-Flop");
            break;

        case FLOP:
            setPhase("Flop");
            break;

        case TURN:
            setPhase("Turn");
            break;

        case RIVER:
            setPhase("River");
            break;

        case SHOWDOWN:
            setPhase("Showdown");
            break;

        default:
            setPhase("Unknown");
            break;

    }
}

// Helper function for getting updated chips
QVector<int> GameState::getUpdatedChips() const {
    QVector<int> updatedChips;
    for (Player* player : m_game->getPlayers()) {
        updatedChips.append(player->getChips());
    }
    return updatedChips;
}

//Helper function to get new community cards
QVector<QString> GameState::getNewCommunityCards() const {
    QVector<QString> newCommunityCards;
    for (const Card& card : m_game->getTable().getCommunityCards()) {
        newCommunityCards.append(QString::fromStdString(card.toString()));
    }
    return newCommunityCards;
}

void GameState::resetPlayerStats() {
    if (m_game && !m_game->getPlayers().empty()) {
        m_game->getPlayers()[0]->getStats().resetStats();
    }
}

void GameState::updateRaiseAmount() {
    if (m_game && !m_game->getPlayers().empty()) {
        int playerChips = m_game->getPlayers()[0]->getChips();
        int currentBet = m_game->getCurrentBet();
        int lastBet = m_game->getPlayers()[0]->getLastBet();
        m_raiseAmount = playerChips - (currentBet - lastBet);
        if (m_raiseAmount < 0) {
            m_raiseAmount = 0; // Ensure m_raiseAmount is not negative
        }
        emit raiseAmountChanged(); // Emit the signal
    }
}
