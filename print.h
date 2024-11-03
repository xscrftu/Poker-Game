#ifndef PRINT_H
#define PRINT_H

#include <string>
#include "struct.h"
std::wstring CardRankToString(CardRank rank) {
    switch (rank) {
        case CardRank::Ace:   return L"Ace";
        case CardRank::Two:   return L"2";
        case CardRank::Three: return L"3";
        case CardRank::Four:  return L"4";
        case CardRank::Five:  return L"5";
        case CardRank::Six:   return L"6";
        case CardRank::Seven: return L"7";
        case CardRank::Eight: return L"8";
        case CardRank::Nine:  return L"9";
        case CardRank::Ten:   return L"10";
        case CardRank::Jack:  return L"J";
        case CardRank::Queen: return L"Q";
        case CardRank::King:  return L"K";
        default:             return L"Unknown";
    }
}

std::wstring CardSuitToString(CardSuit suit) {
    switch (suit) {
        case CardSuit::Hearts: return L"\u2665"; // ♥
        case CardSuit::Diamonds: return L"\u2666"; // ♦
        case CardSuit::Spades: return L"\u2660"; // ♠
        case CardSuit::Clubs: return L"\u2663"; // ♣
        default: return L"Unknown";
    }
}
// Sort hand before compare

// handRank to string
std::wstring handRankToString(HandRank rank) {
    switch (rank) {
        case HandRank::StraightFlush: return L"Straight Flush";
        case HandRank::Quad: return L"Quad";
        case HandRank::FullHouse: return L"Full House";
        case HandRank::Flush: return L"Flush";
        case HandRank::Straight: return L"Straight";
        case HandRank::Set: return L"Set";
        case HandRank::TwoPair: return L"Two Pair";
        case HandRank::Pair: return L"One Pair";
        default: return L"High Card"; // Sử dụng L"" cho chuỗi rộng
    }
}

void PrintHand(const Hand& hand) {
    for (const auto& card : hand.cards) {
        std::wcout << L"Card: " << CardRankToString(card.Rank) << L" "
                   << CardSuitToString(card.Suit) << std::endl;
    }
}

#endif