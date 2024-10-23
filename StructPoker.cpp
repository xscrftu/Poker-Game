#include <iostream>
enum class CardSuit {
    Hearts, Diamond, Spades, Clubs
};
enum class CardRank {
    Two = 2, Three = 3, Four = 4, Five = 5, Six = 6,
    Seven = 7, Eight = 8, Nine = 9, Ten = 10, Jack = 11, Queen = 12,
    King = 13, Ace = 14
};

struct Card {
public:
    CardSuit Suit;
    CardRank Rank;

    Card() = default;
    Card(CardRank rank, CardSuit suit) : Suit(suit), Rank(rank) {}
};
int main(){
    
    return 0;
}