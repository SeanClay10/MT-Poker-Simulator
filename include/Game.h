#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Table.h" // Add this line
#include "Player.h"
using namespace std;

enum GamePhase {
    PRE_FLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
};

class Player;
class Table;

class Game {
private:
    GamePhase gamePhase;
    vector<Player*> players;
    Table* table;
    int currentBet;
    bool playerWentAllIn;
    int currentPlayerIndex;

public:
    // Changes
    Game(int numPlayers, int startingChips);
    Game(int numPlayers, int startingChips, bool charity, bool physical);
    ~Game(); // Add destructor
    vector<Player*> getPlayers();
    void resetData();
    void freeData();
    int getActivePlayers();


    void startNewRound();
    void determineWinner();
    bool betterHand(Player *player1, Player *player2);
    Player* tieBreaker(vector<Player *> &tiedPlayers);
    void proceedToNextPhase();
    void playerFold(Player& player);
    void playerCall(Player& player);
    void playerCheck(Player& player);
    void playerRaise(Player& player, int raiseAmount);
    Table& getTable();
    void setCurrentBet(int bet);
    int getCurrentBet() const;
    GamePhase getGamePhase() const;
    bool getPlayerWentAllIn() const;
    void setPlayerWentAllIn(bool allIn);
    int getCurrentPlayerIndex() const; // Add this line
    void setCurrentPlayerIndex(int index); // Add this line
    int getTotalChipsInAllPots() const; // Add this line
};

#endif
