#ifndef COMPARE_H
#define COMPARE_H

#include "struct.h"
#include <cmath>

// Function prototypes
void SortHand(Hand* handPlayer);
bool isPair(Hand* handPlayer);
bool isSet(Hand* handPlayer);
bool isTwoPair(Hand* handPlayer);
bool isStraight(Hand* handPlayer);
bool isFlush(Hand* handPlayer);
bool isFullHouse(Hand* handPlayer);
bool isQuad(Hand* handPlayer);
bool isStraightFlush(Hand* handPlayer);
double EvaluateHand(Hand* handPlayer);
HandRank getBestHandRank(Hand* hand);
void CompareHand(Hand* player1, Hand* player2);

// Helper function prototype
double calculateScore(int multiplier, const std::vector<int>& ranks);

#endif