#include "struct.h"
#include <cstdlib>

Card::Card() : Suit(CardSuit::Clubs), Rank(CardRank::Two) {}

Card::Card(CardRank rank, CardSuit suit) : Suit(suit), Rank(rank) {}

// Deck function implementations
std::vector<Card> Deck::createStandardDeck()
{
    std::vector<Card> standardDeck;
    for (CardSuit suit : {CardSuit::Hearts, CardSuit::Diamonds, CardSuit::Clubs, CardSuit::Spades})
    {
        for (CardRank rank : {CardRank::Two, CardRank::Three, CardRank::Four, CardRank::Five, CardRank::Six, CardRank::Seven, CardRank::Eight, CardRank::Nine, CardRank::Ten, CardRank::Jack, CardRank::Queen, CardRank::King, CardRank::Ace})
        {
            standardDeck.emplace_back(rank, suit);
        }
    }
    return standardDeck;
}

void Deck::shuffle()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::random_shuffle(deck.begin(), deck.end());
}

Deck::Deck()
{
    deck = createStandardDeck();
    shuffle();
}

Card Deck::draw()
{
    if (deck.empty())
    {
        std::cout << "No more cards in deck!";  // Changed from wide string
    }

    Card drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}