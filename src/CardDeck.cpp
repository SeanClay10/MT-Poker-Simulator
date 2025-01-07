#include "../include/CardDeck.h"

// Default constructor
Card::Card() : suit(""), number(0), faceUp(false) {}

// Constructor to initialize a card with a suit and number
Card::Card(string suit, int value) : suit(suit), number(value), faceUp(false) {}

// Function to flip the card over
void Card::flip() {
    faceUp = !faceUp;
}

// Getter to get the card’s suit
string Card::getSuit() const {
    return suit;
}

// Getter to get the card’s number
int Card::getNumber() const {
    return number;
}

// Getter to check if the card is face up
bool Card::isFaceUp() const {
    return faceUp;
}

string Card::toString() const {
    string cardName;
    switch (number) {
        case 11:
            cardName = "jack";
            break;
        case 12:
            cardName = "queen";
            break;
        case 13:
            cardName = "king";
            break;
        case 14:
            cardName = "ace";
            break;
        default:
            cardName = to_string(number);
            break;
    }
    return cardName + "_of_" + suit;
}


// Constructor to populate the deck with cards
Deck::Deck() {
    populateDeck();
}

// Function to populate the deck with 52 cards
void Deck::populateDeck() {
    const vector<string> suits = {"hearts", "diamonds", "clubs", "spades"};
    cards.clear();
    for (const string& suit : suits) {
        for (int number = 2; number <= 14; ++number) {
            cards.emplace_back(suit, number);
        }
    }
}

// Function to shuffle the deck
void Deck::shuffleDeck() {
    // Seed the random number generator with the current time
    unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    mt19937 g(seed);
    shuffle(cards.begin(), cards.end(), g);
}

// Function to deal a card from the deck
Card Deck::dealCard() {
    if (!cards.empty()) {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
    throw out_of_range("No cards left in the deck");
}

// Function to get the number of cards left in the deck
int Deck::getCardCount() const {
    return cards.size();
}

// Function to get the current order of cards in the deck
vector<Card> Deck::getCards() const {
    return cards;
}