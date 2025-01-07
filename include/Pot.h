#ifndef POT_H
#define POT_H

#include <vector>
using namespace std;

class Player;

class Pot {
private:
    int chips;
    Pot* nextPot;
    vector<Player*> players;
    Player* winner;

public:
    Pot();
    void addChips(int amount, Player* player);
    int getChips() const;
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    const vector<Player*>& getPlayers() const;
    void setNextPot(Pot* next);
    Pot* getNextPot() const;
    void setWinner(Player* player);
    Player* getWinner() const;
    static Pot* newPot();
    static void deletePot(Pot*& pot);
};

#endif