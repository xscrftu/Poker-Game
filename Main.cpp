#include <iostream>
#include <sstream>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include "struct.h"
#include "compare.h"
#include "print.h"
#include "player.h"

int main() {
    /// @brief Set console mode to support wide characters
    _setmode(_fileno(stdout), _O_U16TEXT);

    unsigned int numPlayer;
    std::wstring userInput;

    /// @brief Input and validate the number of players
    do
    {
        std::wcout << L"Enter number of players: ";
        std::getline(std::wcin, userInput);
        numPlayer = 0;
    } while (userInput.empty() || !(std::wstringstream(userInput) >> numPlayer) || !(std::to_wstring(numPlayer) == userInput) || numPlayer <= 1);

    std::vector <Player> players;
    players.resize(numPlayer); /// @brief Resize vector to hold the players

    /// @brief Input players' name and initialize players
    for (unsigned int i = 0; i < numPlayer; ++i)
    {
        std::wstring playerName;
        std::wcout << L"Enter name for Player " << i + 1 << ": ";
        std::wcin >> playerName;
        Player player{playerName};
        players.push_back(player);
    }

    wchar_t conPlaying;
    /// @brief Main game loop
    do
    {
        /// @brief Load players stats;
        for (auto& player : players)
        {
            player.loadStats(player.name + L"_stats.txt");
        }

        Deck deck;

        /// @brief Deal 5 cards to each player's hand
        for (int i = 0; i < 5; ++i)
        {
            for (auto& player : players)
            {
                player.hand.cards[i] = deck.draw();
            }
        }

        /// @brief Process each player's hand
        for (auto& player : players)
        {
            SortHand(&player.hand);
            PrintHand(player.hand);
            HandRank rank = getBestHandRank(&player.hand);
            std::wcout << L"Hand strength: " << handRankToString(rank) << std::endl;
        }

        /// @brief Evaluate each player's hand and determine the maximum score
        std::vector<double> scores;
        double maxScore = -1;
        for (auto& player : players)
        {
            double score = EvaluateHand(&player.hand);
            if (score > maxScore)
            {
                maxScore = score;
            }
            scores.push_back(score);
        }

        /// @brief Determine winner(s) and update stats
        std::vector<Player> winners;
        for (unsigned int i = 0; i < numPlayer; ++i)
        {
            if (scores[i] == maxScore)
            {
                winners.push_back(players[i]);
                players[i].updateStats(true, getBestHandRank(&players[i].hand));
            }
            else
            {
                players[i].updateStats(false, getBestHandRank(&players[i].hand));
            }
        }

        /// @brief Print out winners
        if (winners.size() == 1)
        {
            std::wcout << winners[0].name << L" wins!" << std::endl;
        }
        else
        {
            std::wcout << L"It's a tie between " << winners.size() << L" players: ";
            for (unsigned int i = 0; i < winners.size(); ++i)
            {
                std::wcout << winners[i].name << std::endl;
            }
        }

        /// @brief Output player stats
        for (const auto& player : players)
        {
            std::wcout << player.name << L" - Wins: " << player.wins;
            std::wcout << L" - Losses: " << player.losses;
            std::wcout << L" - Win Rate: " << player.winRate * 100 << L"%" << std::endl;
        }

        /// @brief Save players' stats
        for (auto& player : players)
        {
            player.saveStats(player.name + L"_stats.txt");
        }

        /// @brief Prompt to continue playing
        std::wcout << L"Would you like to continue playing? (Y/N): ";
        std::wcin >> conPlaying;
        conPlaying = std::towupper(conPlaying);
    } while (conPlaying == 'Y');

    return 0;
}