#include "compare.h"
#include <iostream>
#include <cmath>

// Function implementations
void SortHand(Hand* handPlayer)
{
    for (int i = 1; i < 5; ++i)
    {
        Card key = handPlayer->cards[i];
        int j = i - 1;

        while (j >= 0 && static_cast<int>(handPlayer->cards[j].Rank) > static_cast<int>(key.Rank))
        {
            handPlayer->cards[j + 1] = handPlayer->cards[j];
            --j;
        }
        handPlayer->cards[j + 1] = key;
    }
}

bool isPair(Hand* handPlayer)
{
    int pairCount = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank)
        {
            ++pairCount;
        }
    }
    return pairCount == 1;
}

bool isSet(Hand* handPlayer)
{
    int count = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank &&
            handPlayer->cards[i + 1].Rank == handPlayer->cards[i + 2].Rank)
        {
            ++count;
        }
    }
    return count == 1;
}

bool isTwoPair(Hand* handPlayer)
{
    int count = 0;  // Đếm số cặp
    for (int i = 0; i < 4; ++i)
    {
        // Kiểm tra nếu quân bài hiện tại bằng quân bài tiếp theo
        if (handPlayer->cards[i].Rank == handPlayer->cards[i + 1].Rank)
        {
            ++count;  // Tăng số cặp
            ++i;      // Bỏ qua quân bài tiếp theo
        }
    }
    return count == 2;  // Trả về true nếu có 2 cặp
}

bool isStraight(Hand* handPlayer)
{
    for (int i = 0; i < 4; ++i)
    {
        if (static_cast<int>(handPlayer->cards[i].Rank) + 1 != static_cast<int>(handPlayer->cards[i + 1].Rank))
        {
            return false;
        }
    }
    return true;
}

bool isFlush(Hand* handPlayer)
{
    for (int i = 0; i < 4; ++i)
    {
        if (handPlayer->cards[i].Suit != handPlayer->cards[i + 1].Suit)
        {
            return false;
        }
    }
    return true;
}

bool isFullHouse(Hand* handPlayer)
{
    return isSet(handPlayer) && isTwoPair(handPlayer);
}

bool isQuad(Hand* handPlayer)
{
    // Check Quad or Four of Kind
    return (handPlayer->cards[0].Rank == handPlayer->cards[3].Rank) ||
        (handPlayer->cards[1].Rank == handPlayer->cards[4].Rank);
}

bool isStraightFlush(Hand* handPlayer)
{
    return isStraight(handPlayer) && isFlush(handPlayer);
}

// Enhanced helper function to calculate score
double calculateScore(int multiplier, const std::vector<int>& ranks)
{
    double score = multiplier * pow(14, 5);
    int power = 4;
    for (std::vector<int>::const_iterator it = ranks.begin(); it != ranks.end(); ++it)
    {
        score += (*it) * pow(14, power);
        --power;
    }
    return score;
}

double EvaluateHand(Hand* handPlayer)
{
    if (isStraightFlush(handPlayer))
    {
        std::vector<int> ranks = {
            static_cast<int>(handPlayer->cards[4].Rank),
            static_cast<int>(handPlayer->cards[3].Rank),
            static_cast<int>(handPlayer->cards[2].Rank),
            static_cast<int>(handPlayer->cards[1].Rank),
            static_cast<int>(handPlayer->cards[0].Rank)
        };
        return calculateScore(9, ranks);
    }
    else if (isQuad(handPlayer))
    {
        std::vector<int> ranks = {
            static_cast<int>(handPlayer->cards[3].Rank),
            static_cast<int>(handPlayer->cards[4].Rank)
        };
        return calculateScore(8, ranks);
    }
    else if (isFullHouse(handPlayer))
    {
        std::vector<int> ranks = {
            static_cast<int>(handPlayer->cards[2].Rank),
            static_cast<int>(handPlayer->cards[4].Rank)
        };
        return calculateScore(7, ranks);
    }
    else if (isFlush(handPlayer))
    {
        std::vector<int> ranks = {
            static_cast<int>(handPlayer->cards[4].Rank),
            static_cast<int>(handPlayer->cards[3].Rank),
            static_cast<int>(handPlayer->cards[2].Rank),
            static_cast<int>(handPlayer->cards[1].Rank),
            static_cast<int>(handPlayer->cards[0].Rank)
        };
        return calculateScore(6, ranks);
    }
    else if (isStraight(handPlayer))
    {
        std::vector<int> ranks = { static_cast<int>(handPlayer->cards[4].Rank) };
        return calculateScore(5, ranks);
    }
    else if (isSet(handPlayer))
    {
        std::vector<int> ranks = {
            static_cast<int>(handPlayer->cards[2].Rank),
            static_cast<int>(handPlayer->cards[4].Rank)
        };
        return calculateScore(4, ranks);
    }
    else if (isTwoPair(handPlayer))
    {
        std::vector<int> ranks;
        if (handPlayer->cards[0].Rank != handPlayer->cards[1].Rank)
        {
            ranks = {
                static_cast<int>(handPlayer->cards[4].Rank),
                static_cast<int>(handPlayer->cards[2].Rank),
                static_cast<int>(handPlayer->cards[1].Rank)
            };
        }
        else if (handPlayer->cards[1].Rank != handPlayer->cards[2].Rank)
        {
            ranks = {
                static_cast<int>(handPlayer->cards[4].Rank),
                static_cast<int>(handPlayer->cards[1].Rank),
                static_cast<int>(handPlayer->cards[2].Rank)
            };
        }
        else
        {
            ranks = {
                static_cast<int>(handPlayer->cards[3].Rank),
                static_cast<int>(handPlayer->cards[1].Rank),
                static_cast<int>(handPlayer->cards[4].Rank)
            };
        }
        return calculateScore(3, ranks);
    }
    else if (isPair(handPlayer))
    {
        std::vector<int> ranks;
        if (handPlayer->cards[0].Rank == handPlayer->cards[1].Rank)
        {
            ranks = {
                static_cast<int>(handPlayer->cards[0].Rank),
                static_cast<int>(handPlayer->cards[4].Rank),
                static_cast<int>(handPlayer->cards[3].Rank),
                static_cast<int>(handPlayer->cards[2].Rank)
            };
        }
        else if (handPlayer->cards[1].Rank == handPlayer->cards[2].Rank)
        {
            ranks = {
                static_cast<int>(handPlayer->cards[1].Rank),
                static_cast<int>(handPlayer->cards[4].Rank),
                static_cast<int>(handPlayer->cards[3].Rank),
                static_cast<int>(handPlayer->cards[0].Rank)
            };
        }
        else if (handPlayer->cards[2].Rank == handPlayer->cards[3].Rank)
        {
            ranks = {
                static_cast<int>(handPlayer->cards[3].Rank),
                static_cast<int>(handPlayer->cards[4].Rank),
                static_cast<int>(handPlayer->cards[1].Rank),
                static_cast<int>(handPlayer->cards[0].Rank)
            };
        }
        else
        {
            ranks = {
                static_cast<int>(handPlayer->cards[3].Rank),
                static_cast<int>(handPlayer->cards[2].Rank),
                static_cast<int>(handPlayer->cards[1].Rank),
                static_cast<int>(handPlayer->cards[0].Rank)
            };
        }
        return calculateScore(2, ranks);
    }
    else
    {
        // High Card
        std::vector<int> ranks = {
            static_cast<int>(handPlayer->cards[4].Rank),
            static_cast<int>(handPlayer->cards[3].Rank),
            static_cast<int>(handPlayer->cards[2].Rank),
            static_cast<int>(handPlayer->cards[1].Rank),
            static_cast<int>(handPlayer->cards[0].Rank)
        };
        return calculateScore(1, ranks);
    }
}

HandRank getBestHandRank(Hand* hand)
{
    if (isStraightFlush(hand))
    {
        return HandRank::StraightFlush;
    }
    else if (isQuad(hand))
    {
        return HandRank::Quad;
    }
    else if (isFullHouse(hand))
    {
        return HandRank::FullHouse;
    }
    else if (isFlush(hand))
    {
        return HandRank::Flush;
    }
    else if (isStraight(hand))
    {
        return HandRank::Straight;
    }
    else if (isSet(hand))
    {
        return HandRank::Set;
    }
    else if (isTwoPair(hand))
    {
        return HandRank::TwoPair;
    }
    else if (isPair(hand))
    {
        return HandRank::Pair;
    }
    else
    {
        return HandRank::HighCard; // Mặc định nếu không tìm thấy loại hand nào
    }
}

void CompareHand(Hand* player1, Hand* player2)
{
    if (player1->handPlayer < player2->handPlayer)
    {
        std::cout << "Player 2 win";
    }
    else if (player1->handPlayer > player2->handPlayer)
    {
        std::cout << "Player 1 win";
    }
    else
    {
        // Handle tie case
    }
}