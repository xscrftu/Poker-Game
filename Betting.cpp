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
    cout << "Choose your currBet: "; 
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

void CheckAction1(std::vector<Player>& players, int n) {
    switch (players[n].currBet) {
        case Status::Fold:
            std::cout << "Player " << n << " has folded and will be removed.\n";
            players.erase(players.begin() + n);  // Remove the player
            break;

        case Status::Check:
            std::cout << "Player " << n << " checks.\n";
            break;

        case Status::Call:
            std::cout << "Player " << n << " calls.\n";
            break;

        case Status::Raise:
            std::cout << "Player " << n << " raises.\n";
            break;

        case Status::Allin:
            std::cout << "Player " << n << " goes all-in.\n";
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
int main() {
    Deck deck;
    int numPlayers = 5;
    TableInfo table(numPlayers);
    DealCard(&table, deck);

    // Kiểm tra số tiền của người chơi đầu tiên
    cout << "Player 1 Money: " << table.player[0].Money << endl;
    bool check = true;
    // Kiểm tra các giá trị vòng cược
    for (const auto& r : table.round) {
        cout << roundtoString(r) << " ";
        while (check){
            GetAction(table.player[3]);
        }
    }

    cout << endl;

    return 0;
}
