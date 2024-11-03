#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "struct.h"
#include "compare.h"
#include "print.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    Hand hand1;
    Hand hand2;
    Deck deck;

    for (int i = 0; i < 5; i++)
    {
        hand1.cards[i] = deck.draw();
        hand2.cards[i] = deck.draw();
    }

    std::wcout << "Player 1 "<< std::endl;
    SortHand(&hand1);
    PrintHand(hand1);
    HandRank rank1 = getBestHandRank(&hand1); // Gọi hàm và lưu trữ kết quả
    std::wcout << L"Hand strength: " << handRankToString(rank1) << std::endl;

    std::wcout << "\n\nPlayer 2:" << std::endl;
    SortHand(&hand2);
    PrintHand(hand2);
    HandRank rank2 = getBestHandRank(&hand2); // Gọi hàm và lưu trữ kết quả
    std::wcout << L"Hand strength: " << handRankToString(rank2) << std::endl << std::endl;

    double score1 = EvaluateHand(&hand1), score2 = EvaluateHand(&hand2);
    if (score1 < score2){
        std::wcout << "Player 2 win";
    }
    else if (score1 > score2){
        std::wcout << "Player 1 win";
    }
    else {
        std::wcout << "Tier";
    }
    return 0;
}