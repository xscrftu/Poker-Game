#include "print.h"
#include <iostream>

// Function implementations

// Static arrays for mapping
const std::string CardRankStrings[] = {
    "Unknown", // 0
    "Unknown", // 1
    "2", "3", "4", "5", "6", "7", "8", "9", "10",
    "Jack", "Queen", "King", "Ace"
};

const std::string CardSuitStrings[] = {
    "Hearts", "Diamonds", "Spades", "Clubs"
};

const std::string HandRankStrings[] = {
    "Unknown", // 0
    "High Card", "Pair", "Two Pair", "Three of a Kind", "Straight",
    "Flush", "Full House", "Four of a Kind", "Straight Flush"
};

std::string CardRankToString(CardRank rank)
{
    int rankValue = static_cast<int>(rank);
    if (rankValue >= 2 && rankValue <= 14)
    {
        return CardRankStrings[rankValue];
    }
    return "Unknown";
}

std::string CardSuitToString(CardSuit suit)
{
    int suitValue = static_cast<int>(suit);
    if (suitValue >= 0 && suitValue <= 3)
    {
        return CardSuitStrings[suitValue];
    }
    return "Unknown";
}

std::string handRankToString(HandRank rank)
{
    int rankValue = static_cast<int>(rank);
    if (rankValue >= 1 && rankValue <= 9)
    {
        return HandRankStrings[rankValue];
    }
    return "Unknown";
}

void PrintHand(const Hand& hand)
{
    for (const auto& card : hand.cards)
    {
        std::cout << "Card: " << CardRankToString(card.Rank) << " of "
            << CardSuitToString(card.Suit) << std::endl;
    }
}