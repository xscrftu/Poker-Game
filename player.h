#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <string>
#include "struct.h"

struct Player
{
    std::wstring name;
    int wins = 0;
    int losses = 0;
    double winRate = 0.0;
    HandRank favoriteStrategy = HandRank::HighCard;
    int favoriteStrategyCount = 0;
    Hand hand;

    /// @brief Default constructor with initialization
    Player() : name(L"") {}
    Player(const std::wstring& playerName) : name(playerName) {}

    void updateStats(bool won, HandRank strategy)
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

    void updateWinRate()
    {
        int totalGames = wins + losses;
        if (totalGames > 0)
        {
            winRate = static_cast<double>(wins) / totalGames;
        }
    }

    void updateFavoriteStrategy(HandRank strategy)
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

    void saveStats(const std::wstring& filename)
    {
        std::wofstream file(filename.c_str());
        if (file.is_open()) {
            file << name << L"\n" << wins << L"\n" << losses << L"\n" << winRate << L"\n" << static_cast<int>(favoriteStrategy) << L"\n";
            file.close();
        }
        else {
            std::wcerr << L"Error opening file for saving stats!" << std::endl;
        }
    }

    void loadStats(const std::wstring& filename)
    {
        std::wifstream file(filename.c_str());
        if (file.is_open())
        {
            file >> name >> wins >> losses >> winRate;
            int strategy;
            file >> strategy;
            favoriteStrategy = static_cast<HandRank>(strategy);
            file.close();
        }
        else
        {
            std::wcerr << L"Error opening file for loading stats!" << std::endl;
        }
    }
};

#endif // PLAYER_H