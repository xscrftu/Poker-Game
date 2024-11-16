#include "player.h"
#include <iostream>

// Constructors
Player::Player()
{
    name = "";
    wins = 0;
    losses = 0;
    winRate = 0.0;
    favoriteStrategy = HandRank::HighCard;
    favoriteStrategyCount = 0;
}

Player::Player(const std::string& playerName)
{
    name = playerName;
    wins = 0;
    losses = 0;
    winRate = 0.0;
    favoriteStrategy = HandRank::HighCard;
    favoriteStrategyCount = 0;
}

// Member function implementations
void Player::updateStats(bool won, HandRank strategy)
{
    if (won)
    {
        wins++;
    }
    else
    {
        losses++;
    }
    updateWinRate();
    updateFavoriteStrategy(strategy);
}

void Player::updateWinRate()
{
    int totalGames = wins + losses;
    if (totalGames > 0)
    {
        winRate = static_cast<double>(wins) / totalGames;
    }
}

void Player::updateFavoriteStrategy(HandRank strategy)
{
    if (strategy == favoriteStrategy)
    {
        favoriteStrategyCount++;
    }
    else
    {
        favoriteStrategy = strategy;
        favoriteStrategyCount = 1;
    }
}

void Player::saveStats(const std::string& filename)
{
    std::string fullFilename = filename + ".txt";
    std::ofstream file(fullFilename);
    if (file.is_open()) {
        file << name << "\n" << wins << "\n" << losses << "\n" << winRate << "\n" << static_cast<int>(favoriteStrategy) << "\n";
        file.close();
    }
    else {
        std::cerr << "Error opening file for saving stats!" << std::endl;
    }
}

void Player::loadStats(const std::string& filename)
{
    std::string fullFilename = filename + ".txt";
    std::ifstream file(fullFilename);
    if (file.is_open())
    {
        std::getline(file, name);
        file >> wins >> losses >> winRate;
        int strategy;
        file >> strategy;
        favoriteStrategy = static_cast<HandRank>(strategy);
        file.close();
    }
    else
    {
        std::cerr << "Error opening file for loading stats!" << std::endl;
    }
}