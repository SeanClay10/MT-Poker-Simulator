#include "../include/Player.h"
#include <sstream> // Add this line

StatsTracker::StatsTracker() : totalCalls(0), totalFolds(0), totalRaises(0), totalChecks(0), totalWins(0), totalLosses(0), chipsWon(0), chipsLost(0), totalProfit(0) {}

void StatsTracker::recordCall() { totalCalls++; }
void StatsTracker::recordFold() { totalFolds++; }
void StatsTracker::recordRaise() { totalRaises++; }
void StatsTracker::recordCheck() { totalChecks++; }
void StatsTracker::recordWin(int chips) { 
    totalWins++; 
    chipsWon += chips; 
    totalProfit += chips; 
}
void StatsTracker::recordLoss(int chips) { 
    totalLosses++; 
    chipsLost += chips; 
    totalProfit -= chips; 
}


string StatsTracker::getStatsAsString() const {
    std::stringstream ss;
    ss << "Total Calls: " << totalCalls << "\n";
    ss << "Total Folds: " << totalFolds << "\n";
    ss << "Total Raises: " << totalRaises << "\n";
    ss << "Total Checks: " << totalChecks << "\n";
    ss << "Total Wins: " << totalWins << "\n";
    ss << "Total Losses: " << totalLosses << "\n";
    ss << "Chips Won: " << chipsWon << "\n";
    ss << "Chips Lost: " << chipsLost << "\n";
    ss << "Total Profit: " << totalProfit << "\n";
    return ss.str();
}

int StatsTracker::getTotalProfit() const {
    return totalProfit;
}

void StatsTracker::resetStats() {
    totalCalls = 0;
    totalFolds = 0;
    totalRaises = 0;
    totalChecks = 0;
    totalWins = 0;
    totalLosses = 0;
    chipsWon = 0;
    chipsLost = 0;
    totalProfit = 0;
}

Player::Player(int initialChips) : chips(initialChips), handSize(0), folded(false), lastBet(0) {}

int Player::bet(int value) {
    if (value <= chips) {
        chips -= value;
        addToTotalBet(value); // Update totalBet
        return value;
    }
    throw invalid_argument("Insufficient chips to bet");
}

void Player::fold() {
    folded = true;
    stats.recordFold(); // Record a fold
}

void Player::call() {
    stats.recordCall(); // Record a call
}

void Player::raise() {
    stats.recordRaise(); // Record a raise
}

void Player::check() {
    stats.recordCheck(); // Record a check
}

void Player::receiveCard(const Card& card) {
    if (handSize < 2) {
        hand[handSize++] = card;
    }
}

int Player::getChips() const {
    return chips;
}

Card* Player::getHand() {
    return hand;
}

int Player::getHandSize() const {
    return handSize;
}

bool Player::hasFolded() const {
    return folded;
}

void Player::resetForNewRound() {
    wonPotThisRound = false; // Reset wonPotThisRound at the start of the round
    totalBet = 0; // Reset totalBet at the start of the round
    handSize = 0;
    folded = false;
    lastBet = 0;
}

int Player::getTotalBet() const {
    return totalBet;
}

void Player::addToTotalBet(int amount) {
    totalBet += amount;
}

bool Player::hasWonPotThisRound() const {
    return wonPotThisRound;
}

void Player::setWonPotThisRound(bool won) {
    wonPotThisRound = won;
}

int Player::getLastBet() const {
    return lastBet;
}

void Player::setLastBet(int bet) {
    lastBet = bet;
}

void Player::setChips(int amount) {
    chips = amount;
}

StatsTracker& Player::getStats() {
    return stats;
}

void Player::determineHandRank(const vector<Card>& communityCards) {
    // Combine the player's hand with the community cards
    vector<Card> allCards = communityCards;
    allCards.push_back(hand[0]);
    allCards.push_back(hand[1]);

    // Sort cards by number
    sort(allCards.begin(), allCards.end(), [](const Card& a, const Card& b) { return a.getNumber() < b.getNumber(); });

    // Helper function to check for a flush
    auto isFlush = [](const vector<Card>& cards) {
        unordered_map<string, int> suitCount;
        for (const Card& card : cards) {
            suitCount[card.getSuit()]++;
        }
        for (const auto& pair : suitCount) {
            if (pair.second >= 5) {
                return true;
            }
        }
        return false;
    };

    // Helper function to check for a straight
    auto isStraight = [](const vector<Card>& cards) {
        int consecutive = 1;
        for (size_t i = 1; i < cards.size(); ++i) {
            if (cards[i].getNumber() == cards[i - 1].getNumber() + 1) {
                consecutive++;
                if (consecutive >= 5) {
                    return true;
                }
            } else if (cards[i].getNumber() != cards[i - 1].getNumber()) {
                consecutive = 1;
            }
        }
        return false;
    };

    // Helper function to check for a royal flush
    auto isRoyalFlush = [](const vector<Card>& cards) {
        unordered_map<string, vector<int>> suitToNumbers;
        for (const Card& card : cards) {
            suitToNumbers[card.getSuit()].push_back(card.getNumber());
        }
        for (const auto& pair : suitToNumbers) {
            const vector<int>& numbers = pair.second;
            if (find(numbers.begin(), numbers.end(), 10) != numbers.end() &&
                find(numbers.begin(), numbers.end(), 11) != numbers.end() &&
                find(numbers.begin(), numbers.end(), 12) != numbers.end() &&
                find(numbers.begin(), numbers.end(), 13) != numbers.end() &&
                find(numbers.begin(), numbers.end(), 14) != numbers.end()) {
                return true;
            }
        }
        return false;
    };

    // Helper function to count occurrences of each card number
    auto countOccurrences = [](const vector<Card>& cards) {
        unordered_map<int, int> occurrences;
        for (const Card& card : cards) {
            occurrences[card.getNumber()]++;
        }
        return occurrences;
    };

    // Check for different hand ranks
    bool flush = isFlush(allCards);
    bool straight = isStraight(allCards);
    bool royalFlush = isRoyalFlush(allCards);
    auto occurrences = countOccurrences(allCards);

    // Check for Four of a Kind, Full House, Three of a Kind, Two Pair, and One Pair
    int fourOfAKind = 0, threeOfAKind = 0, pairs = 0;
    for (const auto& pair : occurrences) {
        if (pair.second == 4) {
            fourOfAKind = pair.first;
        } else if (pair.second == 3) {
            threeOfAKind = pair.first;
        } else if (pair.second == 2) {
            pairs++;
        }
    }

    // Determine hand rank
    if (royalFlush) {
        handRank = 9; // Royal Flush
    } else if (straight && flush) {
        handRank = 8; // Straight Flush
    } else if (fourOfAKind) {
        handRank = 7; // Four of a Kind
    } else if (threeOfAKind && pairs > 0) {
        handRank = 6; // Full House
    } else if (flush) {
        handRank = 5; // Flush
    } else if (straight) {
        handRank = 4; // Straight
    } else if (threeOfAKind) {
        handRank = 3; // Three of a Kind
    } else if (pairs >= 2) {
        handRank = 2; // Two Pair
    } else if (pairs == 1) {
        handRank = 1; // One Pair
    } else {
        handRank = 0; // High Card
    }
}

int Player::getHandRank() const {
    return handRank;
}

void Player::recordWin(int chips) {
    stats.recordWin(chips); // Record a win
}

void Player::recordLoss(int chips) {
    stats.recordLoss(chips); // Record a loss
}

// Constructor
AI::AI(int initialChips, float badMoveChance)
    : Player(initialChips), calculatedAction("call"), raiseAmount(0), badMoveChance(badMoveChance) {}

string AI::calculateAction(const std::vector<Card>& communityCards, int currentBet, int potSize, const Game& game) {
    GamePhase phase = game.getGamePhase(); // Get the current game phase
    determineHandRank(communityCards);    // Evaluate the hand rank using current hand and community cards

    int handRank = getHandRank();         // AI's hand strength
    int callAmount = currentBet - getLastBet();
    float potOdds = (potSize > 0) ? static_cast<float>(callAmount) / potSize : 0.0f;

    // Pre-flop hand strength evaluation (based on hole cards)
    int highCardValue = std::max(getHand()[0].getNumber(), getHand()[1].getNumber());
    bool isPair = (getHand()[0].getNumber() == getHand()[1].getNumber());
    bool isHighCard = (highCardValue >= 11); // Jack or better

    // AI thresholds for action
    int strongHandThreshold = 6;  // Full house or better
    int mediumHandThreshold = 3;  // Three of a kind or better

    // Pre-Flop Decisions
    if (phase == PRE_FLOP) {
        if (isPair || isHighCard) { // Call or raise with strong starting hands
            calculatedAction = "call";
            if (isHighCard && highCardValue >= 13) { // Kings, Aces, or strong pairs
                calculatedAction = "raise";
                raiseAmount = std::min(potSize / 4, getChips() - (currentBet - getLastBet())); // Raise a fraction of the pot
            }
        } else if (potOdds < 0.4) { // Call with weak hands if pot odds are favorable
            calculatedAction = "call";
        } else {
            calculatedAction = "fold"; // Otherwise, fold
        }
    } 
    // Flop and Turn Decisions
    else if (phase == FLOP || phase == TURN) {
        if (handRank >= strongHandThreshold) {
            calculatedAction = "raise";
            raiseAmount = std::min(potSize / 2, getChips() - (currentBet - getLastBet()));
        } else if (handRank >= mediumHandThreshold || potOdds < 0.25) {
            calculatedAction = "call";
        } else {
            calculatedAction = "fold";
        }
    } 
    // River Decisions
    else if (phase == RIVER) {
        if (handRank >= mediumHandThreshold) {
            calculatedAction = "call";
            if (handRank >= strongHandThreshold) {
                calculatedAction = "raise";
                raiseAmount = std::min(potSize / 2, getChips() - (currentBet - getLastBet()));
            }
        } else if ((rand() % 100) < (badMoveChance * 100)) { // Random bluff
            calculatedAction = "raise";
            raiseAmount = std::min(rand() % 20 + 1, getChips());
        } else {
            calculatedAction = "fold";
        }
    } 
    // Showdown Decisions
    else if (phase == SHOWDOWN) {
        calculatedAction = "check"; // No active betting in the showdown phase
    }

    // Add some randomness to simulate imperfect decision-making
    if ((rand() % 100) < (badMoveChance * 100)) {
        if (calculatedAction != "call" && getLastBet() != currentBet) {
            calculatedAction = "call"; // Occasionally call even with weak hands if not already matched
        }
    }

    // Ensure AI cannot check if they have not matched the current bet
    if (calculatedAction == "check" && getLastBet() != currentBet) {
        calculatedAction = "call";
    }


    // Ensure AI cannot call if they have already matched the current bet
    if (calculatedAction == "call" && getLastBet() == currentBet) {
        calculatedAction = "check";
    }
    return calculatedAction;
}

// Function to execute the AI's action
void AI::doAction(Game& game) {
    AI& aiPlayer = *this; // Create a reference to the current AI object
    if (calculatedAction == "fold") {
        game.playerFold(aiPlayer); // Use reference
    } else if (calculatedAction == "call") {
        game.playerCall(aiPlayer); // Use reference
    } else if (calculatedAction == "raise") {
        game.playerRaise(aiPlayer, raiseAmount); // Use reference and raise amount
    } else if (calculatedAction == "check") {
        game.playerCheck(aiPlayer); // Use reference
    }
}


Human::Human(int initialChips) : Player(initialChips) {}
Human::Human(int initialChips, bool charity, bool physical): Player(initialChips + (charity ? 10 : 0) + (physical ? 10 : 0)), charity(charity), physical(physical) {
}
