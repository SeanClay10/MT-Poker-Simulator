#include "../include/Table.h"
#include "../include/CardDeck.h"
#include "../include/Pot.h"
#include "../include/Player.h"

// Constructor to initialize the table
Table::Table() {
    mainPot = Pot::newPot();
    currentPot = mainPot;
    deck.populateDeck();
    deck.shuffleDeck();
}

Table::~Table() {
    resetPots();
}

// Function to add chips to the current pot
void Table::addToPot(int amount, Player* player) {
    currentPot->addChips(amount, player);
    currentPot->addPlayer(player);
    player->bet(amount); // This already updates totalBet
}

// Function to create a new side pot
void Table::createSidePot(const vector<Player*>& players) {
    Pot* newPot = new Pot();
    for (Player* player : players) {
        if (!player->hasFolded() && player->getChips() > 0) {
            newPot->addPlayer(player);
        }
    }
    currentPot->setNextPot(newPot);
    currentPot = newPot;
}

// Function to reset the pots
void Table::resetPots() {
    Pot* pot = mainPot;
    while (pot) {
        Pot* next = pot->getNextPot();
        Pot::deletePot(pot);
        pot = next;
    }
    mainPot = Pot::newPot();
    currentPot = mainPot;
}

// Function to place a card on the table
void Table::dealCommunityCard() {
    if (communityCards.size() < 5) {
        Card card = deck.dealCard(); // Deal a card from the deck
        communityCards.push_back(card); // Add the card to the communityCards vector
    }
}

// Function to clear the community cards
void Table::clearCommunityCards() {
    communityCards.clear();
}

// Getter to get the community cards
const vector<Card>& Table::getCommunityCards() const {
    return communityCards;
}

// Getter to get the main pot
Pot* Table::getMainPot() const {
    return mainPot;
}

// Getter to get the current pot
Pot* Table::getCurrentPot() const {
    return currentPot;
}

// Function to reset the deck
void Table::resetDeck() {
    deck.populateDeck();
    deck.shuffleDeck();
}

// Function to shuffle the deck
void Table::shuffleDeck() {
    deck.shuffleDeck();
}

// Function to deal cards to players
void Table::dealToPlayers(vector<Player*>& players) {
    for (Player* player : players) {
        player->receiveCard(deck.dealCard());
        player->receiveCard(deck.dealCard());
    }
}

// Getter to get the number of cards left in the deck
int Table::getCardCount() const {
    return deck.getCardCount();
}