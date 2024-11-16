// structpoker.h
#ifndef STRUCTPOKER_H
#define STRUCTPOKER_H

#include <vector>        // Để sử dụng std::vector
#include <iostream>      // Để sử dụng std::cout
#include <algorithm>     // Để sử dụng std::random_shuffle (hoặc std::shuffle)
#include <ctime>         // Để sử dụng std::time
#include <string>

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

    Card();
    Card(CardRank rank, CardSuit suit);
};

struct Deck
{
private:
    std::vector<Card> deck;

    static std::vector<Card> createStandardDeck();

public:
    void shuffle();

    Deck();
    Card draw();
};

struct Hand {
    Card cards[5];
    HandRank handPlayer;
};

#endif // STRUCTPOKER_H