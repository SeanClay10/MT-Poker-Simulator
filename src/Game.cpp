#include "../include/Game.h"
#include "../include/Table.h"
#include "../include/Pot.h" // Add this line


// Initialize game vars
Game::Game(int numPlayers, int startingChips) {
    this->table = new Table(); // Initialize the table pointer

    // Add human player
    Human* humanPlayer = new Human(startingChips);
    this->players.push_back(humanPlayer);

    // Add AI players
    for (int i = 0; i < numPlayers - 1; ++i) {
        float badMoveChance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        AI* aiPlayer = new AI(startingChips, badMoveChance);
        this->players.push_back(aiPlayer);
    }

    this->currentBet = 0;
    this->playerWentAllIn = false;
    this->currentPlayerIndex = -1; // Initialize currentPlayerIndex
}

Game::Game(int numPlayers, int startingChips, bool charity, bool physical)
{
    this->table = new Table(); // Initialize the table pointer

    // Add human player
    Human *humanPlayer = new Human(startingChips, charity, physical);
    this->players.push_back(humanPlayer);

    // Add AI players
    for (int i = 0; i < numPlayers - 1; ++i) {
        float badMoveChance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        AI* aiPlayer = new AI(startingChips, badMoveChance);
        this->players.push_back(aiPlayer);
    }

    this->currentBet = 0;
    this->playerWentAllIn = false;
    this->currentPlayerIndex = -1; // Initialize currentPlayerIndex
}

Game::~Game() {
    this->freeData();
}

vector<Player*> Game::getPlayers() {return this->players;}

void Game::resetData() {
    gamePhase = PRE_FLOP;
    table->resetPots();
    table->clearCommunityCards();
    table->resetDeck();
    currentBet = 0;
    playerWentAllIn = false;
    for (Player* player : players) {
        player->resetForNewRound(); // Use pointer to reset player
    }
}


void Game::freeData() {
    this->resetData();
    // Free players
    for (Player* player : this->players) {
        if (player != nullptr) {
            delete player;
            player = nullptr; // Set pointer to nullptr after deletion
        }
    }
    this->players.clear(); // Clear the vector after deleting players

    if (this->table != nullptr) {
        delete this->table; // Clean up the table pointer
        this->table = nullptr; // Set pointer to nullptr after deletion
    }
}


int Game::getActivePlayers() {
    int activePlayers = 0;

    for (const Player* player : players) {
        if (!player->hasFolded() && player->getChips() > 0) {
            activePlayers++;
        }
    }
    return activePlayers;
}


// Function to start a new round
void Game::startNewRound() {
    this->resetData();

    table->dealToPlayers(players); // Pass vector<Player*>
}

// Function to determine the winner
void Game::determineWinner() {
    const vector<Card>& communityCards = table->getCommunityCards();

    // Iterate through each player and if a player has folded, record a loss
    for (Player* player : players) {
        if (player->hasFolded()) {
            int lossAmount = player->getTotalBet(); // Use totalBet to calculate the number of chips bet this round
            player->recordLoss(lossAmount); // Record a loss
        }
    }
    // Start with the main pot
    Pot* pot = table->getMainPot();

    // Iterate through each pot in the linked list
    while (pot) {
        // Skip the pot if it has 0 chips
        if (pot->getChips() == 0) {
            pot = pot->getNextPot();
            continue;
        }

        // Determine the best hand among players in the current pot
        Player* bestPlayer = nullptr;
        int bestRank = -1;
        vector<Player *> tiedPlayers;

        // Iterate through the players in the pot
        for (Player *player : pot->getPlayers())
        {
            if (!player->hasFolded())
            {
                // Determine the player's hand rank
                player->determineHandRank(communityCards);
                int playerRank = player->getHandRank();
                // Check if the player has the best hand
                if (playerRank > bestRank)
                {
                    bestRank = playerRank;
                    bestPlayer = player;
                    tiedPlayers.clear();           // Reset tied players
                    tiedPlayers.push_back(player); // Add the current best player
                }
                else if (playerRank == bestRank)
                {
                    tiedPlayers.push_back(player); // Add to tie list if same rank
                }
            }
        }

        // Determine winner's index
        // If there's a tie, call the tieBreaker function
        if (tiedPlayers.size() > 1) {
            bestPlayer = tieBreaker(tiedPlayers); // This will update the winner in case of a tie
        }

        if (bestPlayer)
        {
            int bestPlayerIndex = -1;
            for (size_t i = 0; i < players.size(); ++i)
            {
                if (players[i] == bestPlayer)
                { // Compare pointers
                    bestPlayerIndex = i;
                    break;
                }
            }
            bestPlayer->setWonPotThisRound(true);                           // Set wonPotThisRound to true
            bestPlayer->setChips(bestPlayer->getChips() + pot->getChips()); // Award chips to player
            pot->setWinner(bestPlayer);                                     // Set the winner of the pot
        }

        // Move to the next pot
        pot = pot->getNextPot();
    }

    // Record wins and losses for each player
    for (Player *player : players)
    {
        if (player->hasWonPotThisRound())
        {
            int totalChipsWon = 0;
            Pot *pot = table->getMainPot();
            while (pot)
            {
                if (pot->getChips() > 0 && pot->getWinner() == player)
                {
                    totalChipsWon += pot->getChips();
                }
                pot = pot->getNextPot();
            }

            int chipsBet = player->getTotalBet();        // Use totalBet to calculate the number of chips bet this round
            player->recordWin(totalChipsWon - chipsBet); // Record a win with net chips won
        }
        else if (!player->hasFolded())
        {
            int chipsBet = player->getTotalBet();
            player->recordLoss(chipsBet); // Record a loss
        }
    }
}

bool Game::betterHand(Player *player1, Player *player2)
{
    // First compare the hand ranks
    int hand1Rank = player1->getHandRank();
    int hand2Rank = player2->getHandRank();

    if (hand1Rank != hand2Rank)
    {
        return hand1Rank > hand2Rank; // Compare hand ranks
    }

    // If the hand ranks are the same, compare the cards in hand (kickers)
    Card *hand1Cards = player1->getHand(); // Get hand as a pointer to Card array
    Card *hand2Cards = player2->getHand(); // Get hand as a pointer to Card array

    size_t hand1Size = player1->getHandSize(); // Get the number of cards in hand1
    size_t hand2Size = player2->getHandSize(); // Get the number of cards in hand2

    // Ensure both hands have the same number of cards for comparison
    if (hand1Size != hand2Size)
    {
        return hand1Size > hand2Size;
    }

    // Compare cards from highest to lowest rank
    for (size_t i = 0; i < hand1Size; ++i)
    {
        if (hand1Cards[i].getNumber() != hand2Cards[i].getNumber())
        {                                                                 // Compare rank using getNumber()
            return hand1Cards[i].getNumber() > hand2Cards[i].getNumber(); // Compare ranks using getNumber()
        }
    }

    // If all cards are the same, return false (tie)
    return false;
}

Player* Game::tieBreaker(vector<Player *> &tiedPlayers)
{
    if (tiedPlayers.size() <= 1)
    {
        return tiedPlayers.empty() ? nullptr : tiedPlayers[0]; // Return the single player or nullptr if empty
    }

    const vector<Card> &communityCards = table->getCommunityCards(); // Assuming community cards are stored correctly

    int bestHandRank = -1;
    vector<Player *> winners;

    for (Player *player : tiedPlayers)
    {
        player->determineHandRank(communityCards); // Calculate hand rank
        int playerHandRank = player->getHandRank();

        if (playerHandRank > bestHandRank)
        {
            bestHandRank = playerHandRank;
            winners.clear();
            winners.push_back(player);
        }
        else if (playerHandRank == bestHandRank)
        {
            winners.push_back(player);
        }
    }

    // Apply tiebreakers if there's more than one winner
    if (winners.size() > 1)
    {
        Player *finalBestPlayer = nullptr;
        for (Player *player : winners)
        {
            // Compare cards for tie-breaking starting from the highest-ranked
            if (!finalBestPlayer || betterHand(finalBestPlayer, player))
            {
                finalBestPlayer = player;
            }
        }

        // If a final winner is found, update the winners list
        if (finalBestPlayer)
        {
            winners.clear();
            winners.push_back(finalBestPlayer);
        }
    }

    // Return the final winner or the first player in case of a tie
    if (winners.size() == 1)
    {
        winners[0]->setWonPotThisRound(true);
        return winners[0];
    }
    else
    {
        winners[0]->setWonPotThisRound(true);
        return winners[0];
    }
}

// Function to proceed to the next phase of the game
void Game::proceedToNextPhase() {
    switch (gamePhase) {
        case PRE_FLOP:
            gamePhase = FLOP;
            table->dealCommunityCard();
            table->dealCommunityCard();
            table->dealCommunityCard();
            break;
        case FLOP:
            gamePhase = TURN;
            table->dealCommunityCard();
            break;
        case TURN:
            gamePhase = RIVER;
            table->dealCommunityCard();
            break;
        case RIVER:
            gamePhase = SHOWDOWN;
            break;
        case SHOWDOWN:
            determineWinner();
            break;
    }
}

// Function to handle a player folding
void Game::playerFold(Player& player) {
    player.fold();
    Pot* pot = table->getMainPot();
    while (pot) {
        pot->removePlayer(&player);
        pot = pot->getNextPot();
    }
}


// Function to handle a player calling the current bet
void Game::playerCall(Player& player) {
    int callAmount = currentBet - player.getLastBet();
    int playerChips = player.getChips();
    player.setLastBet(player.getLastBet() + callAmount);

    if (playerChips <= callAmount) {
        table->addToPot(playerChips, &player);
    } else {
        table->addToPot(callAmount, &player);
    }
    player.call();

}

// Function to handle a player raising the current bet
void Game::playerRaise(Player& player, int raiseAmount) {
    int totalRaise = (currentBet + raiseAmount) - player.getLastBet();
    currentBet += raiseAmount;
    player.setLastBet(player.getLastBet() + totalRaise);
    table->addToPot(totalRaise, &player);
    player.raise();
}

void Game::playerCheck(Player& player) {
    player.check();
}



// Getter to get the table
Table& Game::getTable() {
    return *table;
}

// Setter to set the current bet
void Game::setCurrentBet(int bet) {
    currentBet = bet;
}

// Getter to get the current bet
int Game::getCurrentBet() const {
    return currentBet;
}

// Getter to get game phase
GamePhase Game::getGamePhase() const {
    return gamePhase;
}

// Getter to get the current player index
int Game::getCurrentPlayerIndex() const {
    return currentPlayerIndex;
}

// Setter to set the current player index
void Game::setCurrentPlayerIndex(int index) {
    currentPlayerIndex = index;
}



bool Game::getPlayerWentAllIn() const {
    return playerWentAllIn;
}

void Game::setPlayerWentAllIn(bool allIn) {
    playerWentAllIn = allIn;
}

int Game::getTotalChipsInAllPots() const {
    int totalChips = 0;
    Pot* pot = table->getMainPot();
    while (pot) {
        totalChips += pot->getChips();
        pot = pot->getNextPot();
    }
    return totalChips;
}
