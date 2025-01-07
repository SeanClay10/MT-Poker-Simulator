#include "../include/Pot.h"
#include "../include/Player.h"

// Constructor to initialize the pot
Pot::Pot() : chips(0), nextPot(nullptr), winner(nullptr) {}

// Function to add chips to the pot
void Pot::addChips(int amount, Player* player) {
    chips += amount;
}

// Getter to get the total chips in the pot
int Pot::getChips() const {
    return chips;
}

// Function to add a player to the pot
void Pot::addPlayer(Player* player) {
    players.push_back(player);
}

// Function to remove a player from the pot
void Pot::removePlayer(Player* player) {
    players.erase(remove(players.begin(), players.end(), player), players.end());
}

// Getter to get the players associated with the pot
const vector<Player*>& Pot::getPlayers() const {
    return players;
}

// Function to set the next pot
void Pot::setNextPot(Pot* next) {
    nextPot = next;
}

// Getter to get the next pot
Pot* Pot::getNextPot() const {
    return nextPot;
}

// Function to set the winner of the pot
void Pot::setWinner(Player* player) {
    winner = player;
}

// Getter to get the winner of the pot
Player* Pot::getWinner() const {
    return winner;
}

// Static function to create a new pot
Pot* Pot::newPot() {
    return new Pot();
}

// Static function to delete a pot
void Pot::deletePot(Pot*& pot) {
    if (pot) {
        delete pot;
        pot = nullptr;
    }
}