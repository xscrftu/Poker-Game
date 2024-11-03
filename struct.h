// structpoker.h
#ifndef STRUCTPOKER_H
#define STRUCTPOKER_H

#include <vector>        // Để sử dụng std::vector
#include <iostream>      // Để sử dụng std::cout
#include "struct.h"      
#include <algorithm>     // Để sử dụng std::random_shuffle (hoặc std::shuffle)
#include <ctime>         // Để sử dụng std::time

enum class CardSuit {
    Hearts, Diamonds, Spades, Clubs
};

enum class CardRank {
    Two = 2, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten, Jack, Queen,
    King, Ace
};

enum class HandRank {
    HighCard = 1, Pair, TwoPair, Set, Straight, Flush, FullHouse, Quad, StraightFlush
};

/// @brief The Card struct, represent a poker card.
struct Card
{
public:
    /// @brief The suit of the card.
    CardSuit Suit = CardSuit::Clubs;
    /// @brief The rank of the card
    CardRank Rank = CardRank::Two;

    Card() = default;
    Card(CardRank rank, CardSuit suit) : Suit(suit), Rank(rank) {}
};

struct Deck
{
private:
    std::vector<Card> deck;

    static std::vector<Card> createStandardDeck()
    {
        std::vector<Card> standardDeck;
        for (CardSuit suit : {CardSuit::Hearts, CardSuit::Diamonds, CardSuit::Clubs, CardSuit::Spades})
        {
            for (CardRank rank : {CardRank::Two, CardRank::Three, CardRank::Four, CardRank::Five, CardRank::Six, CardRank::Seven, CardRank::Eight, CardRank::Nine, CardRank::Ten, CardRank::Jack, CardRank::Queen, CardRank::King, CardRank::Ace})
            {
                standardDeck.push_back(Card(rank, suit));
            }
        }
        return standardDeck;
    }
public:
    void shuffle()
    {
        std::srand(std::time(nullptr));
        std::random_shuffle(deck.begin(), deck.end());
    }

    Deck() : deck(createStandardDeck())
    {
        shuffle();
    }

    Card draw()
    {
        if (deck.empty())
        {
            std::cout << "Hết bài rồi";
        }

        Card drawnCard = deck.back();
        deck.pop_back();
        return drawnCard;
    }
};
struct Hand {
    Card cards[5];
    HandRank handPlayer;
};

#endif 