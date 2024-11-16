#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include "struct.h"
#include "compare.h"
#include "print.h"
#include "player.h"

int main()
{
    unsigned int numPlayer;
    std::string userInput;

    do
    {
        std::cout << "Enter number of players: ";
        std::getline(std::cin, userInput);
        numPlayer = 0;
    } while (userInput.empty() || !(std::stringstream(userInput) >> numPlayer) ||
        !(std::to_string(numPlayer) == userInput) || numPlayer <= 1);

    std::vector<Player> players;

    for (unsigned int i = 0; i < numPlayer; ++i)
    {
        std::string playerName;
        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::getline(std::cin, playerName);
        Player player(playerName);
        players.push_back(player);
    }

    char conPlaying;
    do
    {
        for (size_t i = 0; i < players.size(); ++i)
        {
            players[i].loadStats(players[i].name); // Removed ".txt" as it's handled in loadStats
        }

        Deck deck;

        for (int i = 0; i < 5; ++i)
        {
            for (size_t j = 0; j < players.size(); ++j)
            {
                players[j].hand.cards[i] = deck.draw();
            }
        }

        for (size_t i = 0; i < players.size(); ++i)
        {
            std::cout << players[i].name << "'s hand: " << std::endl;
            SortHand(&players[i].hand);
            PrintHand(players[i].hand);
            HandRank rank = getBestHandRank(&players[i].hand);
            std::cout << "Hand strength: " << handRankToString(rank) << std::endl;
        }

        std::vector<double> scores;
        double maxScore = -1.0;
        for (size_t i = 0; i < players.size(); ++i)
        {
            double score = EvaluateHand(&players[i].hand);
            if (score > maxScore)
            {
                maxScore = score;
            }
            scores.push_back(score);
        }

        std::vector<Player> winners;
        for (size_t i = 0; i < players.size(); ++i)
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

        if (winners.size() == 1)
        {
            std::cout << winners[0].name << " wins!" << std::endl;
        }
        else
        {
            std::cout << "It's a tie between " << winners.size() << " players: " << std::endl;
            for (size_t i = 0; i < winners.size(); ++i)
            {
                std::cout << winners[i].name << std::endl;
            }
        }

        for (size_t i = 0; i < players.size(); ++i)
        {
            std::cout << players[i].name << " - Wins: " << players[i].wins;
            std::cout << " - Losses: " << players[i].losses;
            std::cout << " - Win Rate: " << players[i].winRate * 100 << "%" << std::endl;
        }

        for (size_t i = 0; i < players.size(); ++i)
        {
            players[i].saveStats(players[i].name); // Removed ".txt" as it's handled in saveStats
        }

        std::cout << "Would you like to continue playing? (Y/N): ";
        std::cin >> conPlaying;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
        conPlaying = std::toupper(conPlaying);
    } while (conPlaying == 'Y');

    return 0;
}