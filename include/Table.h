#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "CardDeck.h"
#include "Pot.h"
using namespace std;

class Pot;
class Player;

class Table {
private:
    vector<Card> communityCards;
    Deck deck;
    Pot* mainPot;
    Pot* currentPot;

public:
    Table();
    ~Table();
    void addToPot(int amount, Player* player);
    void createSidePot(const vector<Player*>& players);
    void resetPots();
    void dealCommunityCard();
    void clearCommunityCards();
    const vector<Card>& getCommunityCards() const;
    Pot* getMainPot() const;
    Pot* getCurrentPot() const;
    void resetDeck();
    void shuffleDeck();
    void dealToPlayers(vector<Player*>& players);
    int getCardCount() const;
};

#endif