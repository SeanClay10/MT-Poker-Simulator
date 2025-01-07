#ifndef CARDDECK_H
#define CARDDECK_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <chrono>
using namespace std;

class Card {
private:
    string suit;
    int number;
    bool faceUp;

public:
    Card();
    Card(string suit, int value);
    void flip();
    string getSuit() const;
    int getNumber() const;
    bool isFaceUp() const;
    string toString() const;
};

class Deck {
private:
    vector<Card> cards;

public:
    Deck();
    void populateDeck();
    void shuffleDeck();
    Card dealCard();
    int getCardCount() const;
    vector<Card> getCards() const;
};

#endif