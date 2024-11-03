#include <iostream>
#include <vector>
#include "struct.h"
#include "compare.h"
#include "print.h"
using namespace std;

enum class StatusRound {
    Pre_flop = 1, Flop, Turn, River
};

enum class Status {
    Invalid, Fold, Check, Call, Bet, Raise, Allin
};

// enum class Button {
//     deal = 1, smallBlind, bigBlind
// };
struct Player {
    int Money;
    int BetMoney;  
    Card card[2];  
    Status currBet;  
    // Constructor để khởi tạo người chơi với số tiền
    Player(int money, int currBet_money = 0)
        : Money(money), currBet(Status::Invalid), BetMoney(currBet_money) {}
};
struct TableInfo {
    int numPlayer;
    vector<Player> player; // Danh sách người chơi
    vector<StatusRound> round = {StatusRound::Pre_flop, StatusRound::Flop, StatusRound::Turn, StatusRound::River};
    int Pot;
    int currTableBet;
    Card communitycard[5];
    // Constructor khởi tạo với số người chơi
    TableInfo(int num) : numPlayer(num), Pot(0) {
        player.reserve(num); // Dự trữ bộ nhớ cho vector
        for (int i = 0; i < num; ++i) {
            player.emplace_back(2000); // Thêm người chơi với số tiền khởi đầu là 2000
        }
    }
};

string roundtoString(StatusRound round){
    switch (round)
    {
    case StatusRound::Pre_flop: return "Pre_flop";  
    case StatusRound::Flop: return "Flop";
    case StatusRound::Turn: return "Turn";
    case StatusRound::River: return "River";
    default:
        break;
    }
}
void GetAction(Player& player){
    int playerAction; 
    cout << "Choose your currBet: 1 - Fold | 2 - Check | 3 - Call | 4 - Bet | 5 - Raise"; 
    cin >> playerAction;
    switch (playerAction)
    {
    case 1:
        player.currBet = Status::Fold;
        break;
    case 2:
        player.currBet = Status::Check;
        break;
    case 3:
        player.currBet = Status::Call;
        break;
    case 4: 
        player.currBet = Status::Bet;
        break;
    case 5: 
        player.currBet = Status::Raise;
        break;
    default:
        cout << "INVALID BET";
        break;
    }
}
bool IsBetting(TableInfo& table) {
    int curr_money = -1;
    for (Player& player : table.player) {
        if (player.currBet == Status::Fold || player.currBet == Status::Allin)
            continue;
        if (curr_money < 0)
            curr_money = player.BetMoney;
        else if (curr_money != player.BetMoney)
            return false;
    }

    return true;
}
void Call(Player &player, int &tablebet){
    player.BetMoney = tablebet;
    player.Money -= tablebet;
}
void Bet(Player &player, int &tablebet){
    int moneyBet; 
    cout << "Enter your bet money: ";
    cin >> moneyBet;
    tablebet = moneyBet;
    player.BetMoney = tablebet;
    player.Money -= tablebet; // suy xet them
}
void Raise(Player &player, int &tablebet) {
    int moneyRaise;
    cout << "Enter your raise money (>= mỉn rasise): ";
    cin >> moneyRaise;
    while (moneyRaise < 2 * tablebet) {
        cout << "Raise amount must be at least double the current table bet (" << tablebet << "). Please enter a valid amount: ";
        cin >> moneyRaise;
    }
    tablebet = moneyRaise;
    player.BetMoney = tablebet;
    player.Money -= tablebet;
}
void Allin(Player& player, int &tablebet){
    player.BetMoney = player.Money;
    tablebet = player.BetMoney;
    player.Money = 0;
}
void Action(Player& player, int &tablebet) {
    switch (player.currBet) {
        case Status::Fold:
            break;
        case Status::Check:
            std::cout << "Player Check.\n";
            break;
        case Status::Call:
            std::cout << "Player calls.\n";
            Call(player, tablebet);
            break;
        case Status::Bet:
            std::cout << "Player Bet.\n";
            Bet(player, tablebet);
            break;
        case Status::Raise:
            std::cout << "Player raises.\n";
            Raise(player, tablebet);
            break;
        case Status::Allin:
            std::cout << "Player goes all-in.\n";
            Allin(player, tablebet);
            break;

        default:
            std::cout << "Unknown action.\n";
            break;
    }
}
// Chia Bài
void DealCard(TableInfo* table, Deck& deck){
    for (int i = 0; i < 2; ++i){
        for (int player = 0; player < 5; ++player)
            table->player[player].card[i] = deck.draw();
    }
}
void PrintCard(const Card& card) {
    std::string rankStr;
    std::string suitStr;

    // Chuyển đổi Rank sang chuỗi
    switch (card.Rank) {
        case CardRank::Two:   rankStr = "2"; break;
        case CardRank::Three: rankStr = "3"; break;
        case CardRank::Four:  rankStr = "4"; break;
        case CardRank::Five:  rankStr = "5"; break;
        case CardRank::Six:   rankStr = "6"; break;
        case CardRank::Seven: rankStr = "7"; break;
        case CardRank::Eight: rankStr = "8"; break;
        case CardRank::Nine:  rankStr = "9"; break;
        case CardRank::Ten:   rankStr = "10"; break;
        case CardRank::Jack:  rankStr = "J"; break;
        case CardRank::Queen: rankStr = "Q"; break;
        case CardRank::King:  rankStr = "K"; break;
        case CardRank::Ace:   rankStr = "A"; break;
    }

    // Chuyển đổi Suit sang chuỗi
    switch (card.Suit) {
        case CardSuit::Hearts:   suitStr = "Hearts"; break;
        case CardSuit::Diamonds: suitStr = "Diamonds"; break;
        case CardSuit::Clubs:    suitStr = "clubs"; break;
        case CardSuit::Spades:   suitStr = "Spades"; break;
    }

    // In lá bài với định dạng "A ♠" hoặc "10 ♥"
    std::cout << rankStr << " " << suitStr << std::endl;
}
int main() {
    Deck deck;
    int numPlayers = 5;
    TableInfo table(numPlayers);
    DealCard(&table, deck);

    // Chia bai cho player
    for (int i = 0; i < 2; ++i){
        for (auto & r: table.player){
            r.card[i] = deck.draw();
        }
    }
    // Chia bai tren ban
    for (int i = 0; i < 5; ++i) {
        table.communitycard[i] = deck.draw();  // Lấy lá bài từ deck và gán cho community card
    }

    for (const auto& r : table.round) {
        cout << roundtoString(r) << " ";
        switch (r)
        {
        case StatusRound::Flop:
            for (int i = 0; i<2; ++i){
                std::cout << PrintCard(table.communitycard[i]);
            }
            break;
        case StatusRound::Turn:
            for (int i = 3; i<4; ++i){
                std::cout << PrintCard(table.communitycard[i]);
            }
            break;
        case StatusRound::River:
            for (int i = 4; i<5; ++i){
                std::cout << PrintCard(table.communitycard[i]);
            }
            break;
        default:
            break;
        }
        if (r == StatusRound::Pre_flop){
            table.currTableBet = 20; //big blind
        } else {
            table.currTableBet = 0;
        }
        for (auto& it : table.player){
            GetAction(it);
            Action(it,table.currTableBet);
        }
    }
    cout << endl;
    return 0;
}
