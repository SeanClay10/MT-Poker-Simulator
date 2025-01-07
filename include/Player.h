#ifndef PLAYER_H
#define PLAYER_H

#include "CardDeck.h"
#include "Game.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream> // Add this line
using namespace std;

class Game;

class StatsTracker {
private:
    int totalCalls;
    int totalFolds;
    int totalRaises;
    int totalChecks;
    int totalWins;
    int totalLosses;
    int chipsWon;
    int chipsLost;
    int totalProfit; // Add this line

public:
    StatsTracker();
    void recordCall();
    void recordFold();
    void recordRaise();
    void recordCheck();
    void recordWin(int chips);
    void recordLoss(int chips);
    int getTotalProfit() const; // Add this line
    string getStatsAsString() const;
    void resetStats(); // Add this line
};

class Player {
private:
    int chips;
    Card hand[2];
    int handSize;
    bool folded;
    int lastBet;
    int handRank;
    StatsTracker stats;
    bool wonPotThisRound;
    int totalBet;

public:
    Player(int initialChips);
    virtual ~Player() {} // Add virtual destructor
    int bet(int value);
    void fold();
    void call();
    void raise();
    void check();
    void receiveCard(const Card& card);
    int getChips() const;
    Card* getHand();
    int getHandSize() const;
    bool hasFolded() const;
    void resetForNewRound(); // Update this line
    int getLastBet() const;
    void setLastBet(int bet);
    void setChips(int amount);
    StatsTracker& getStats(); // Change this line
    void determineHandRank(const vector<Card>& communityCards);
    int getHandRank() const;
    void recordWin(int chips);
    void recordLoss(int chips);
    int getInitialChips() const; // Add this line
    bool hasWonPotThisRound() const; // Add this line
    void setWonPotThisRound(bool won); // Add this line
    int getTotalBet() const; // Add this line
    void addToTotalBet(int amount); // Add this line
};

class Human : public Player {
public:
    Human(int initialChips);
    Human(int initialChips, bool charity, bool physical);
private:
    bool charity = false; 
    bool physical = false; 
};

class AI : public Player {
private:
    std::string calculatedAction; // Stores the calculated action (e.g., "fold", "call", "raise", "check")
    int raiseAmount;              // Stores the amount to raise
    float badMoveChance;          // Probability of making a suboptimal move

public:
    AI(int initialChips, float badMoveChance);

    // Getter methods
    std::string getCalculatedAction() const { return calculatedAction; }
    int getRaiseAmount() const { return raiseAmount; }

    string calculateAction(const std::vector<Card>& communityCards, int currentBet, int potSize, const Game& game);
    void doAction(Game& game);
};


#endif
