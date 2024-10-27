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
    CardSuit Suit;
    CardRank Rank;

    Card() = default;
    Card(CardRank rank, CardSuit suit) : Suit(suit), Rank(rank) {}
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
        case CardSuit::Diamond: return "Diamond";
        case CardSuit::Spades: return "Spades";
        case CardSuit::Clubs: return "Clubs";
        default: return "Unknown";
    }
}

void SortHand(Hand* handPlayer) { 
    for (int i = 1; i < 5; ++i) {
        Card key = handPlayer->cards[i];
        int j = i - 1;
        
        while (j >= 0 && static_cast<int>(handPlayer->cards[j].Rank) > static_cast<int>(key.Rank)) {
            handPlayer->cards[j + 1] = handPlayer->cards[j];
            --j;
        }
        handPlayer->cards[j + 1] = key;
    }
}

void PrintHand(const Hand& hand) {
    for (const auto& card : hand.cards) {
        std::cout << "Card: Rank " << CardRankToString(card.Rank) 
                  << ", Suit " << CardSuitToString(card.Suit) << std::endl;
    }
}

bool isPair(Hand* handPlayer) {
    int pairCount = 0;
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
            ++pairCount;
            ++i;  // Bỏ qua quân bài tiếp theo
            if (i < 3 && handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
                return false;  // Tứ quý hoặc bộ ba, không phải một đôi
            }
        }
    }
    return pairCount == 1;
}

bool isSet(Hand* handPlayer) {
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank &&
            handPlayer->cards[i + 1].Rank == handPlayer->cards[i + 2].Rank) {
            ++count;
        }
    }
    return count == 1;
}

bool isTwoPair(Hand* handPlayer) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
            ++count;
            ++i;  // Skip the next card in the current pair
            // Check for a third card of the same rank (indicating three or four of a kind)
            if (i < 3 && handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
                return false;  // More than a pair, not a two-pair hand
            }
        }
    }
    return count == 2;
}


bool isStraight(Hand* handPlayer) {
    for (int i = 0; i < 4; ++i) {
        if (static_cast<int>(handPlayer->cards[i].Rank) + 1 != static_cast<int>(handPlayer->cards[i + 1].Rank)) {
            return false;
        }
    }
    return true;
}

bool isFlush(Hand* handPlayer) {
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].Suit != handPlayer->cards[i + 1].Suit) {
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
    return (handPlayer->cards[0].Rank == handPlayer->cards[3].Rank) || 
           (handPlayer->cards[1].Rank == handPlayer->cards[4].Rank);
}

bool isStraightFlush(Hand* handPlayer) {
    return isStraight(handPlayer) && isFlush(handPlayer);
}

int main() {
    Hand hand = {
        Card(CardRank::Ace, CardSuit::Hearts),
        Card(CardRank::Ace, CardSuit::Diamond),
        Card(CardRank::Six, CardSuit::Spades),  
        Card(CardRank::Six, CardSuit::Clubs),
        Card(CardRank::Six, CardSuit::Hearts)
    };

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
