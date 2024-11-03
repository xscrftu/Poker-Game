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
    _setmode(_fileno(stdout), _O_U16TEXT);

    unsigned int numPlayer;
    std::wstring userInput;

    do
    {
        std::wcout << L"Enter number of players: ";
        std::getline(std::wcin, userInput);
        numPlayer = 0;
    } while (userInput.empty() || !(std::wstringstream(userInput) >> numPlayer) || !(std::to_wstring(numPlayer) == userInput) || numPlayer <= 1);

    std::vector <Player> players;

    for (unsigned int i = 0; i < numPlayer; ++i)
    {
        std::wstring playerName;
        std::wcout << L"Enter name for Player " << i + 1 << ": ";
        std::wcin >> playerName;
        Player player{playerName};
        players.push_back(player);
    }

    // Load players stats;
    for (auto& player : players)
    {
        player.loadStats(player.name + L"_stats.txt");
    }

    Deck deck;

    // Deal 5 card to players hand
    for (int i = 0; i < 5; ++i)
    {
        for (auto& player : players)
        {
            player.hand.cards[i] = deck.draw();
        }
    }

    // Process players
    for (auto& player : players)
    {
        SortHand(&player.hand);
        PrintHand(player.hand);
        HandRank rank = getBestHandRank(&player.hand);
        std::wcout << L"Hand strength: " << handRankToString(rank) << std::endl;
    }

    // Evaluate each player's hand
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

    // Determine winner and update stats
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

    // Print out winners
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

    // Output player stats
    for (const auto& player : players)
    {
        std::wcout << player.name << L" - Wins: " << player.wins;
        std::wcout << L" - Losses: " << player.losses;
        std::wcout << L" - Win Rate: " << player.winRate * 100 << L"%" << std::endl;   
    }

    // Save players stats
    for (auto& player : players)
    {
        player.saveStats(player.name + L"_stats.txt");
    }

    return 0;
}