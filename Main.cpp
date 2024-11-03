#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "struct.h"
#include "compare.h"
#include "print.h"
#include "player.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wstring player1Name, player2Name;
    std::wcout << L"Enter name for Player 1: ";
    std::wcin >> player1Name;
    std::wcout << L"Enter name for Player 2: ";
    std::wcin >> player2Name;
    Player player1{player1Name};
    Player player2{player2Name};

    player1.loadStats(player1Name + L"_stats.txt");
    player2.loadStats(player2Name + L"_stats.txt");

    Deck deck;

    // Deal 5 cards to each player
    for (int i = 0; i < 5; i++) {
        player1.hand.cards[i] = deck.draw(); // Access the hand's cards
        player2.hand.cards[i] = deck.draw(); // Access the hand's cards
    }

    // Process Player 1
    std::wcout << L"Player: " << player1.name << std::endl;
    SortHand(&player1.hand);
    PrintHand(player1.hand);
    HandRank rank1 = getBestHandRank(&player1.hand);
    std::wcout << L"Hand strength: " << handRankToString(rank1) << std::endl;

    // Process Player 2
    std::wcout << L"\n\nPlayer: " << player2.name << std::endl;
    SortHand(&player2.hand);
    PrintHand(player2.hand);
    HandRank rank2 = getBestHandRank(&player2.hand);
    std::wcout << L"Hand strength: " << handRankToString(rank2) << std::endl;

    // Evaluate and compare hand scores
    double score1 = EvaluateHand(&player1.hand);
    double score2 = EvaluateHand(&player2.hand);
    
    if (score1 < score2) {
        std::wcout << player2.name << L" wins!" << std::endl;
        player2.updateStats(true, rank2);
        player1.updateStats(false, rank1);
    } else if (score1 > score2) {
        std::wcout << player1.name << L" wins!" << std::endl;
        player1.updateStats(true, rank1);
        player2.updateStats(false, rank2);
    } else {
        std::wcout << L"It's a tie!" << std::endl;
    }

    // Output player stats
    std::wcout << player1.name << L" - Wins: " << player1.wins 
            << L", Losses: " << player1.losses 
            << L", Win Rate: " << player1.winRate * 100 << L"%" << std::endl;

    std::wcout << player2.name << L" - Wins: " << player2.wins 
            << L", Losses: " << player2.losses 
            << L", Win Rate: " << player2.winRate * 100 << L"%" << std::endl;

    // Save player stats
    player1.saveStats(player1Name + L"_stats.txt");
    player2.saveStats(player2Name + L"_stats.txt");

    return 0;
}