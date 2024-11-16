#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <string>
#include "struct.h"

struct Player
{
    std::string name;
    int wins = 0;
    int losses = 0;
    double winRate = 0.0;
    HandRank favoriteStrategy = HandRank::HighCard;
    int favoriteStrategyCount = 0;
    Hand hand;

    // Constructors
    Player();
    Player(const std::string& playerName);

    // Member functions
    void updateStats(bool won, HandRank strategy);
    void updateWinRate();
    void updateFavoriteStrategy(HandRank strategy);
    void saveStats(const std::string& filename);
    void loadStats(const std::string& filename);
};

#endif