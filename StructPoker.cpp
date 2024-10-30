#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <algorithm>
#include <io.h>
#include <fcntl.h>

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

std::wstring CardRankToString(CardRank rank) {
    switch (rank) {
        case CardRank::Ace:   return L"Ace";
        case CardRank::Two:   return L"2";
        case CardRank::Three: return L"3";
        case CardRank::Four:  return L"4";
        case CardRank::Five:  return L"5";
        case CardRank::Six:   return L"6";
        case CardRank::Seven: return L"7";
        case CardRank::Eight: return L"8";
        case CardRank::Nine:  return L"9";
        case CardRank::Ten:   return L"10";
        case CardRank::Jack:  return L"J";
        case CardRank::Queen: return L"Q";
        case CardRank::King:  return L"K";
        default:             return L"Unknown";
    }
}

std::wstring CardSuitToString(CardSuit suit) {
    switch (suit) {
        case CardSuit::Hearts: return L"\u2665"; // ♥
        case CardSuit::Diamonds: return L"\u2666"; // ♦
        case CardSuit::Spades: return L"\u2660"; // ♠
        case CardSuit::Clubs: return L"\u2663"; // ♣
        default: return L"Unknown";
    }
}
// Sort hand before compare
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
        std::wcout << L"Card: " << CardRankToString(card.Rank) << L" "
                   << CardSuitToString(card.Suit) << std::endl;
    }
}
// Check Pair
bool isPair(Hand* handPlayer) {
    int pairCount = 0;
    for (int i = 0; i < 4; ++i) {
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank) {
            ++pairCount;
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

// Check Two Pair
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

// Check Straight
bool isStraight(Hand* handPlayer) {
    for (int i = 0; i < 4; ++i) {
        if (static_cast<int>(handPlayer->cards[i].Rank) + 1 != static_cast<int>(handPlayer->cards[i + 1].Rank)) {
            return false;
        }
    }
    return true;
}

// Check flush
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
    // Check Quad or Four of Kind
    return (handPlayer->cards[0].Rank == handPlayer->cards[3].Rank) || 
           (handPlayer->cards[1].Rank == handPlayer->cards[4].Rank);
}

bool isStraightFlush(Hand* handPlayer) {
    return isStraight(handPlayer) && isFlush(handPlayer);
}

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

HandRank getBestHandRank(Hand* hand) {
    if (isStraightFlush(hand)) return HandRank::StraightFlush;
    if (isQuad(hand)) return HandRank::Quad;
    if (isFullHouse(hand)) return HandRank::FullHouse;
    if (isFlush(hand)) return HandRank::Flush;
    if (isStraight(hand)) return HandRank::Straight;
    if (isSet(hand)) return HandRank::Set;
    if (isTwoPair(hand)) return HandRank::TwoPair;
    if (isPair(hand)) return HandRank::Pair;

    return HandRank::HighCard; // Mặc định nếu không tìm thấy loại hand nào
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
std::wstring handRankToString(HandRank rank) {
    switch (rank) {
        case HandRank::StraightFlush: return L"Straight Flush";
        case HandRank::Quad: return L"Quad";
        case HandRank::FullHouse: return L"Full House";
        case HandRank::Flush: return L"Flush";
        case HandRank::Straight: return L"Straight";
        case HandRank::Set: return L"Set";
        case HandRank::TwoPair: return L"Two Pair";
        case HandRank::Pair: return L"One Pair";
        default: return L"High Card"; // Sử dụng L"" cho chuỗi rộng
    }
}
int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    Hand hand1;
    Hand hand2;
    Deck deck;

    for (int i = 0; i < 5; i++)
    {
        hand1.cards[i] = deck.draw();
        hand2.cards[i] = deck.draw();
    }

    std::wcout << "Player 1 "<< std::endl;
    SortHand(&hand1);
    PrintHand(hand1);
    HandRank rank1 = getBestHandRank(&hand1); // Gọi hàm và lưu trữ kết quả
    std::wcout << L"Hand strength: " << handRankToString(rank1) << std::endl;

    std::wcout << "\n\nPlayer 2:" << std::endl;
    SortHand(&hand2);
    PrintHand(hand2);
    HandRank rank2 = getBestHandRank(&hand2); // Gọi hàm và lưu trữ kết quả
    std::wcout << L"Hand strength: " << handRankToString(rank2) << std::endl << std::endl;

    double score1 = EvaluateHand(&hand1), score2 = EvaluateHand(&hand2);
    if (score1 < score2){
        std::wcout << "Player 2 win";
    }
    else if (score1 > score2){
        std::wcout << "Player 1 win";
    }
    else {
        std::wcout << "Tier";
    }
    return 0;
}