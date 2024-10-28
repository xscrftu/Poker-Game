#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

enum class CardSuit {
    Hearts, Diamonds, Spades, Clubs
};

enum class CardRank {
    Two = 2, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten, Jack, Queen,
    King, Ace
};

struct Card
{
private:
    CardSuit suit;
    CardRank rank;
public:
    Card() {}

    Card(CardRank rank, CardSuit suit)
    {
        this->suit = suit;
        this->rank = rank;
    }

    CardSuit getSuit() const
    {
        return suit;
    }
    CardRank getRank() const
    {
        return rank;
    }
};

struct Deck
{
private:
    std::vector<Card> deck;
public:
    void shuffle()
    {
        std::srand(std::time(nullptr));
        std::random_shuffle(deck.begin(), deck.end());
    }

    Deck()
    {
        for (CardSuit suit : {CardSuit::Hearts, CardSuit::Diamonds, CardSuit::Clubs, CardSuit::Spades})
        {
            for (CardRank rank : {CardRank::Two, CardRank::Three, CardRank::Four, CardRank::Five, CardRank::Six, CardRank::Seven, CardRank::Eight, CardRank::Nine, CardRank::Ten, CardRank::Jack, CardRank::Queen, CardRank::King, CardRank::Ace})
            {
                deck.push_back(Card(rank, suit));
            }
        }
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
};

// Chuyển đổi CardRank thành chuỗi
std::string CardRankToString(CardRank rank) {
    switch (rank) {
        case CardRank::Two: return "Two";
        case CardRank::Three: return "Three";
        case CardRank::Four: return "Four";
        case CardRank::Five: return "Five";
        case CardRank::Six: return "Six";
        case CardRank::Seven: return "Seven";
        case CardRank::Eight: return "Eight";
        case CardRank::Nine: return "Nine";
        case CardRank::Ten: return "Ten";
        case CardRank::Jack: return "Jack";
        case CardRank::Queen: return "Queen";
        case CardRank::King: return "King";
        case CardRank::Ace: return "Ace";
        default: return "Unknown";
    }
}

// Chuyển đổi CardSuit thành chuỗi
std::string CardSuitToString(CardSuit suit) {
    switch (suit) {
        case CardSuit::Hearts: return "Hearts";
        case CardSuit::Diamonds: return "Diamond";
        case CardSuit::Spades: return "Spades";
        case CardSuit::Clubs: return "Clubs";
        default: return "Unknown";
    }
}

void SortHand(Hand* handPlayer) { 
    for (int i = 1; i < 5; ++i) {
        Card key = handPlayer->cards[i];
        int j = i - 1;
        
        while (j >= 0 && static_cast<int>(handPlayer->cards[j].getRank()) > static_cast<int>(key.getRank())) {
            handPlayer->cards[j + 1] = handPlayer->cards[j];
            --j;
        }
        handPlayer->cards[j + 1] = key;
    }
}

void PrintHand(const Hand& hand) {
    for (const auto& card : hand.cards) {
        std::cout << "Card: Rank " << CardRankToString(card.getRank()) 
                  << ", Suit " << CardSuitToString(card.getSuit()) << std::endl;
    }
}

bool isPair(Hand* handPlayer) {
    int pairCount = 0;
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].getRank() == handPlayer->cards[i + 1].getRank()) {
            ++pairCount;
            ++i;  // Bỏ qua quân bài tiếp theo
            if (i < 3 && handPlayer->cards[i].getRank() == handPlayer->cards[i + 1].getRank()) {
                return false;  // Tứ quý hoặc bộ ba, không phải một đôi
            }
        }
    }
    return pairCount == 1;
}

bool isSet(Hand* handPlayer) {
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        if (handPlayer->cards[i].getRank() == handPlayer->cards[i + 1].getRank() &&
            handPlayer->cards[i + 1].getRank() == handPlayer->cards[i + 2].getRank()) {
            ++count;
        }
    }
    return count == 1;
}

bool isTwoPair(Hand* handPlayer) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].getRank() == handPlayer->cards[i + 1].getRank()) {
            ++count;
            ++i;  // Skip the next card in the current pair
            // Check for a third card of the same rank (indicating three or four of a kind)
            if (i < 3 && handPlayer->cards[i].getRank() == handPlayer->cards[i + 1].getRank()) {
                return false;  // More than a pair, not a two-pair hand
            }
        }
    }
    return count == 2;
}


bool isStraight(Hand* handPlayer) {
    for (int i = 0; i < 4; ++i) {
        if (static_cast<int>(handPlayer->cards[i].getRank()) + 1 != static_cast<int>(handPlayer->cards[i + 1].getRank())) {
            return false;
        }
    }
    return true;
}

bool isFlush(Hand* handPlayer) {
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].getSuit() != handPlayer->cards[i + 1].getSuit()) {
            return false;
        }
    }
    return true;
}

bool isFullHouse(Hand* handPlayer) {
    return isSet(handPlayer) && isPair(handPlayer);
}

bool isQuad(Hand* handPlayer) {
    // Kiểm tra tứ quý
    return (handPlayer->cards[0].getRank() == handPlayer->cards[3].getRank()) || 
           (handPlayer->cards[1].getRank() == handPlayer->cards[4].getRank());
}

bool isStraightFlush(Hand* handPlayer) {
    return isStraight(handPlayer) && isFlush(handPlayer);
}

int main() {
    Hand hand;
    Deck deck;

    for (int i = 0; i < 5; i++)
    {
        hand.cards[i] = deck.draw();
    }

    std::cout << "Hand before sorting:" << std::endl;
    PrintHand(hand);

    SortHand(&hand);

    std::cout << "\nHand after sorting:" << std::endl;
    PrintHand(hand);

    std::cout << "\nHand evaluation:" << std::endl;
    std::cout << "Pair: " << isPair(&hand) << std::endl;
    std::cout << "Set: " << isSet(&hand) << std::endl;
    std::cout << "Two Pair: " << isTwoPair(&hand) << std::endl;
    std::cout << "Straight: " << isStraight(&hand) << std::endl;
    std::cout << "Flush: " << isFlush(&hand) << std::endl;
    std::cout << "Full House: " << isFullHouse(&hand) << std::endl;
    std::cout << "Quad: " << isQuad(&hand) << std::endl;
    std::cout << "Straight Flush: " << isStraightFlush(&hand) << std::endl;

    return 0;
}
