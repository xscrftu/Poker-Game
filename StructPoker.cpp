#include <iostream>
<<<<<<< HEAD
#include <cmath>
=======
#include <vector>
#include <ctime>
#include <algorithm>

>>>>>>> cd8e28aaacb770b754179962290bbadc5823e400
enum class CardSuit {
    Hearts, Diamonds, Spades, Clubs
};

enum class CardRank {
    Two = 2, Three, Four, Five, Six,
    Seven, Eight, Nine, Ten, Jack, Queen,
    King, Ace
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

<<<<<<< HEAD
enum class HandRank {
    StraightFlush = 9, Quad = 8, FullHouse = 7, Flush = 6, 
    Straight = 5, Set = 4, TwoPair = 3, Pair = 2, HighCard = 1
=======
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
>>>>>>> cd8e28aaacb770b754179962290bbadc5823e400
};

struct Hand {
    Card cards[5];
    HandRank handPlayer;
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
            // ++i;  // Bỏ qua quân bài tiếp theo
            // if (i < 3 && handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
            //     return false;  // Tứ quý hoặc bộ ba, không phải một đôi
            // }
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
    int count = 0;  // Đếm số cặp
    for (int i = 0; i < 4; ++i) {
        // Kiểm tra nếu quân bài hiện tại bằng quân bài tiếp theo
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
            ++count;  // Tăng số cặp
            ++i;      // Bỏ qua quân bài tiếp theo
        }
    }
    return count == 2;  // Trả về true nếu có 2 cặp
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
    return isSet(handPlayer) && isTwoPair(handPlayer);
}

bool isQuad(Hand* handPlayer) {
    // Kiểm tra tứ quý
    return (handPlayer->cards[0].Rank == handPlayer->cards[3].Rank) || 
           (handPlayer->cards[1].Rank == handPlayer->cards[4].Rank);
}

bool isStraightFlush(Hand* handPlayer) {
    return isStraight(handPlayer) && isFlush(handPlayer);
}

// double EvaluateHand(Hand* handPlayer) {
//     if (isStraightFlush(handPlayer)) {
//         return 9 * 14 +static_cast<int>(handPlayer->cards[4].Rank);
//     } else if (isQuad(handPlayer)) {
//         return 8 * 14 + static_cast<int>(handPlayer->cards[3].Rank);  // cards[3], cards[2] will be a quad
//     } else if (isFullHouse(handPlayer)) {
//         return 7 * 14 + static_cast<int>(handPlayer->cards[3].Rank);
//     } else if (isFlush(handPlayer)) {
//         return 6 * 14 + static_cast<int>(handPlayer->cards[4].Rank);  // Danh gia them
//     } else if (isStraight(handPlayer)) {
//         return 5 * 14 +static_cast<int>(handPlayer->cards[4].Rank);
//     } else if (isSet(handPlayer)) {
//         return 4 * 14 + static_cast<int>(handPlayer->cards[3].Rank);
//     } else if (isTwoPair(handPlayer)) {
//         return HandRank::TwoPair;
//     } else if (isPair(handPlayer)) {
//         return HandRank::Pair;
//     } else {
//         return HandRank::HighCard; // Nếu không thuộc loại nào khác, sẽ là "High Card"
//     }
// }

double EvaluateHand(Hand* handPlayer) {
    if (isStraightFlush(handPlayer)) {
        return 9 * pow(14, 5) + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 4) +
               static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 3) +
               static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 2) +
               static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 1) +
               static_cast<int>(handPlayer->cards[0].Rank);
    } else if (isQuad(handPlayer)) {
        return 8 * pow(14, 5) + static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 4) +
               static_cast<int>(handPlayer->cards[4].Rank); // Lá bài thứ 5 có thể là kicker
    } else if (isFullHouse(handPlayer)) {
        return 7 * pow(14, 5) + static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 4) +
       -        static_cast<int>(handPlayer->cards[4].Rank); // Bộ ba và đôi
    } else if (isFlush(handPlayer)) {
        return 6 * pow(14, 5) + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 4) +
               static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 3) +
               static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 2) +
               static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 1) +
               static_cast<int>(handPlayer->cards[0].Rank);
    } else if (isStraight(handPlayer)) {
        return 5 * pow(14, 5) + static_cast<int>(handPlayer->cards[4].Rank);
    } else if (isSet(handPlayer)) {
        return 4 * pow(14, 5) + static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 4) +
               static_cast<int>(handPlayer->cards[4].Rank); // Bộ ba và kicker cao
    } 
    else if (isTwoPair(handPlayer)) {
        if (handPlayer->cards[0].Rank != handPlayer->cards[1].Rank) {
            return 3 * pow(14, 5) + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 4) 
            + static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 3) 
            + static_cast<int>(handPlayer->cards[1].Rank);
        } 
        else if (handPlayer->cards[1].Rank != handPlayer->cards[2].Rank){
            return 3 * pow(14, 5) + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 4) 
            + static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 3) 
            + static_cast<int>(handPlayer->cards[2].Rank);
        } else {
            return 3 * pow(14, 5) + static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 4) 
            + static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 3) 
            + static_cast<int>(handPlayer->cards[4].Rank);
        }
    // Pair
    } else if (isPair(handPlayer)) { 
        if (handPlayer->cards[0].Rank == handPlayer->cards[1].Rank){
            return 2 * pow(14, 5) + static_cast<int>(handPlayer->cards[0].Rank) * pow(14, 4)
            + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 3)
            + static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 2)
            + static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 1);
        }
        else if (handPlayer->cards[1].Rank == handPlayer->cards[2].Rank){
            return 2 * pow(14, 5) + static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 4)
            + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 3)
            + static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 2)
            + static_cast<int>(handPlayer->cards[0].Rank) * pow(14, 1);
        }
        else if (handPlayer->cards[2].Rank == handPlayer->cards[3].Rank){
            return 2 * pow(14, 5) + static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 4)
            + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 3)
            + static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 2)
            + static_cast<int>(handPlayer->cards[0].Rank) * pow(14, 1);
        }
        else {
            return 2 * pow(14, 5) + static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 4)
            + static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 3)
            + static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 2)
            + static_cast<int>(handPlayer->cards[0].Rank) * pow(14, 1);
        }
    } else {
        // High Card
        return 1 * pow(14, 5) + static_cast<int>(handPlayer->cards[4].Rank) * pow(14, 4) +
               static_cast<int>(handPlayer->cards[3].Rank) * pow(14, 3) +
               static_cast<int>(handPlayer->cards[2].Rank) * pow(14, 2) +
               static_cast<int>(handPlayer->cards[1].Rank) * pow(14, 1) +
               static_cast<int>(handPlayer->cards[0].Rank);
    }
}


void CompareHand(Hand* player1, Hand* player2){
    if (player1->handPlayer < player2->handPlayer){
        std::cout << "Player 2 win";
    } 
    else if (player1->handPlayer > player2->handPlayer) {
        std::cout << "Player 1 win";
    } else {
        
    }
}
int main() {
<<<<<<< HEAD
    Hand hand = {
        Card(CardRank::Ace, CardSuit::Hearts),
        Card(CardRank::King, CardSuit::Diamond),
        Card(CardRank::Queen, CardSuit::Spades),  
        Card(CardRank::Jack, CardSuit::Clubs),
        Card(CardRank::Ten, CardSuit::Hearts)
    };
    Hand hand1 = {
        Card(CardRank::King, CardSuit::Hearts),
        Card(CardRank::King, CardSuit::Diamond),
        Card(CardRank::King, CardSuit::Spades),  
        Card(CardRank::Ten, CardSuit::Clubs),
        Card(CardRank::Ten, CardSuit::Hearts)
    };
=======
    Hand hand;
    Deck deck;

    for (int i = 0; i < 5; i++)
    {
        hand.cards[i] = deck.draw();
    }

    std::cout << "Hand before sorting:" << std::endl;
    PrintHand(hand);

>>>>>>> cd8e28aaacb770b754179962290bbadc5823e400
    SortHand(&hand);
    SortHand(&hand1);

    std::cout << "Player 1 "<< std::endl;
    PrintHand(hand);
    std::cout << "Hand evaluation:" << std::endl;
    std::cout << "Pair: " << isPair(&hand) << std::endl;
    std::cout << "Set: " << isSet(&hand) << std::endl;
    std::cout << "Two Pair: " << isTwoPair(&hand) << std::endl;
    std::cout << "Straight: " << isStraight(&hand) << std::endl;
    std::cout << "Flush: " << isFlush(&hand) << std::endl;
    std::cout << "Full House: " << isFullHouse(&hand) << std::endl;
    std::cout << "Quad: " << isQuad(&hand) << std::endl;
    std::cout << "Straight Flush: " << isStraightFlush(&hand) << std::endl;

    std::cout << "\n\nPlayer 2:" << std::endl;
    PrintHand(hand1);
    std::cout << "Hand evaluation:" << std::endl;
    std::cout << "Pair: " << isPair(&hand1) << std::endl;
    std::cout << "Set: " << isSet(&hand1) << std::endl;
    std::cout << "Two Pair: " << isTwoPair(&hand1) << std::endl;
    std::cout << "Straight: " << isStraight(&hand1) << std::endl;
    std::cout << "Flush: " << isFlush(&hand1) << std::endl;
    std::cout << "Full House: " << isFullHouse(&hand1) << std::endl;
    std::cout << "Quad: " << isQuad(&hand1) << std::endl;
    std::cout << "Straight Flush: " << isStraightFlush(&hand1) << std::endl;

    double score1 = EvaluateHand(&hand), score2 = EvaluateHand(&hand1);
    if (score1 < score2){
        std::cout << "Player 2 win";
    }
    else if (score1 > score2){
        std::cout << "Player 1 win";
    }
    else {
        std::cout << "Tier";
    }
    return 0;
}