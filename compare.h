#ifndef COMPARE_H
#define COMPARE_H

#include "struct.h"
#include <cmath>
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

// Check Set
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

// Check Full House
bool isFullHouse(Hand* handPlayer) {
    return isSet(handPlayer) && isTwoPair(handPlayer);
}

// Check Quad
bool isQuad(Hand* handPlayer) {
    // Check Quad or Four of Kind
    return (handPlayer->cards[0].Rank == handPlayer->cards[3].Rank) || 
           (handPlayer->cards[1].Rank == handPlayer->cards[4].Rank);
}

// Check Straight Flush
bool isStraightFlush(Hand* handPlayer) {
    return isStraight(handPlayer) && isFlush(handPlayer);
}

// Evaluate hand Strength
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

// Get Best Hand
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

// Compare Hand
void CompareHand(Hand* player1, Hand* player2){
    if (player1->handPlayer < player2->handPlayer){
        std::cout << "Player 2 win";
    } 
    else if (player1->handPlayer > player2->handPlayer) {
        std::cout << "Player 1 win";
    } else {
        
    }
}


#endif