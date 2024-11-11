#ifndef PRINT_H
#define PRINT_H

#include <string>
#include "struct.h"

// Function prototypes
std::string CardRankToString(CardRank rank);
std::string CardSuitToString(CardSuit suit);
std::string handRankToString(HandRank rank);
void PrintHand(const Hand& hand);

#endif