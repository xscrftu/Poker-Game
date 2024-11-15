#include <iostream>
#include <vector>
#include "struct.h"
#include "compare.h"
#include "print.h"
using namespace std;
const int minRaise = 40;
const int smallBlind = 10, bigBlind = 20;
enum class StatusRound
{
    Pre_flop = 1,
    Flop,
    Turn,
    River,
    Final
};

enum class PlayerState
{
    INIT,
    OUT,
    ALIVE,
    ALLIN
};

enum class Action
{
    Fold,
    Check,
    Call,
    Raise,
    Allin
};

enum class Position
{
    SB,
    BB,
    UTG,
    MP,
    CO,
    BTN
};

struct Player
{
    int behindMoney;
    int frontMoney;
    Card card[2];
    Action action;
    PlayerState playerState;
    Player() = default;
    Player(int initialMoney) : behindMoney(initialMoney), frontMoney(0), playerState(PlayerState::INIT) {}
};
struct TableInfo
{
    int numPlayer;
    vector<Player> player; // Danh sách người chơi
    vector<StatusRound> round = {StatusRound::Pre_flop, StatusRound::Flop, StatusRound::Turn, StatusRound::River};
    int Pot;
    int currTableBet;
    Card communitycard[5];
    // Constructor khởi tạo với số người chơi
    TableInfo(int num) : numPlayer(num), Pot(0)
    {
        player.reserve(num); // Dự trữ bộ nhớ cho vector
        for (int i = 0; i < num; ++i)
        {
            player.emplace_back(2000); // Thêm người chơi với số tiền khởi đầu là 2000
        }
    }
};
struct playerAction
{
    int m_amount;
    Action m_act;
    Position m_pos;
    playerAction(int amount, Action act, Position pos)
        : m_amount(amount), m_act(act), m_pos(pos) {};
};
struct gamestate
{
    int numPlayer;
    vector<int> chipBehind;
    vector<int> chipFront;
    vector<PlayerState> playerstate;
    Position round0_first_player = numPlayer > 2 ? Position::UTG : Position::BB;
};

std::wstring roundtoString(const StatusRound round)
{
    switch (round)
    {
    case StatusRound::Pre_flop:
        return L"PRE_FLOP";
    case StatusRound::Flop:
        return L"FLOP";
    case StatusRound::Turn:
        return L"TURN";
    case StatusRound::River:
        return L"RIVER";
    default:
        return L"UNKNOWN";
    }
}
std::wstring playerStatetoString(const PlayerState ps)
{
    switch (ps)
    {
    case PlayerState::INIT:
        return L"INIT";
    case PlayerState::OUT:
        return L"OUT";
    case PlayerState::ALIVE:
        return L"ALIVE";
    case PlayerState::ALLIN:
        return L"ALLIN";
    default:
        return L"UNKNOWN";
    }
}

void Call(Player &player, int &tablebet)
{
    player.frontMoney = tablebet;
}
void Check(Player &player, int &tablebet)
{
    player.frontMoney = 0;
}

void Raise(Player &player, int &tablebet)
{
    int moneyRaise;
    cout << "Enter your raise money (>= min_raise): ";
    cin >> moneyRaise;
    if (player.behindMoney < tablebet)
    {
        player.frontMoney = player.behindMoney;
        player.playerState = PlayerState::ALLIN;
    }
    else
    {
        while (moneyRaise < 2 * tablebet || moneyRaise < minRaise)
        {
            cout << "Raise amount must be at least double the current table bet (" << tablebet << "). Please enter a valid amount: ";
            cin >> moneyRaise;
        }
        player.frontMoney = moneyRaise;
        tablebet = moneyRaise;
    }
}
void Allin(Player &player, int &tablebet)
{
    player.frontMoney = player.behindMoney;
    tablebet = player.behindMoney;
}
void DealCard(TableInfo *table, Deck &deck)
{
    for (int i = 0; i < 2; ++i)
    {
        for (int player = 0; player < 5; ++player)
            table->player[player].card[i] = deck.draw();
    }
}
void PrintCard(const Card &card)
{
    std::string rankStr;
    std::string suitStr;

    // Chuyển đổi Rank sang chuỗi
    switch (card.Rank)
    {
    case CardRank::Two:
        rankStr = "2";
        break;
    case CardRank::Three:
        rankStr = "3";
        break;
    case CardRank::Four:
        rankStr = "4";
        break;
    case CardRank::Five:
        rankStr = "5";
        break;
    case CardRank::Six:
        rankStr = "6";
        break;
    case CardRank::Seven:
        rankStr = "7";
        break;
    case CardRank::Eight:
        rankStr = "8";
        break;
    case CardRank::Nine:
        rankStr = "9";
        break;
    case CardRank::Ten:
        rankStr = "10";
        break;
    case CardRank::Jack:
        rankStr = "J";
        break;
    case CardRank::Queen:
        rankStr = "Q";
        break;
    case CardRank::King:
        rankStr = "K";
        break;
    case CardRank::Ace:
        rankStr = "A";
        break;
    }

    // Chuyển đổi Suit sang chuỗi
    switch (card.Suit)
    {
    case CardSuit::Hearts:
        suitStr = "Hearts";
        break;
    case CardSuit::Diamonds:
        suitStr = "Diamonds";
        break;
    case CardSuit::Clubs:
        suitStr = "Clubs";
        break;
    case CardSuit::Spades:
        suitStr = "Spades";
        break;
    }

    // In lá bài với định dạng "A ♠" hoặc "10 ♥"
    std::cout << rankStr << " " << suitStr << std::endl;
}
void GetAction(Player &player, int &tablebet)
{
    int playerAction;
    cout << "Choose your Action: 1 - Fold | 2 - Call | 3 - Raise | 4 - Allin\n";
    cout << "Your choose: ";
    while (!(std::cin >> playerAction) || playerAction < 1 || playerAction > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Enter again 1 <= n <= 4: ";
    }

    switch (playerAction)
    {
    case 1:
        player.action = Action::Fold;
        player.playerState = PlayerState::OUT;
        cout << "PLAYER FOLD. You are out of this game\n";
        break;
    case 2:
        player.action = Action::Call;
        player.playerState = PlayerState::ALIVE;
        Call(player, tablebet);
        cout << "CALL " << tablebet << "$" <<endl;
        break;
    case 3:
        player.action = Action::Raise;
        player.playerState = PlayerState::ALIVE;
        Raise(player, tablebet);
        cout << "RAISE " << tablebet << "$" << endl;
        break;
    case 4:
        player.action = Action::Allin;
        player.playerState = PlayerState::ALLIN;
        Allin(player, tablebet);
        cout << "ALL IN " << tablebet << "$" << endl;
        break;
    default:
        cout << "INVALID BET";
        break;
    }
}
void GetAction1(Player &player, int &tablebet)
{
    int playerAction;
    cout << "Choose your Action: 1 - Fold | 2 - Check | 3 - Raise | 4 - Allin\n";
    cout << "Your choose: ";
    while (!(std::cin >> playerAction) || playerAction < 1 || playerAction > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Enter again 1 <= n <= 4: ";
    }
    switch (playerAction)
    {
    case 1:
        player.action = Action::Fold;
        player.playerState = PlayerState::OUT;
        cout << "PLAYER FOLD. You are out of this game\n";
        break;
    case 2:
        player.action = Action::Check;
        player.playerState = PlayerState::ALIVE;
        Check(player, tablebet);
        cout << "PLAYER CHECK!\n";
        break;
    case 3:
        player.action = Action::Raise;
        player.playerState = PlayerState::ALIVE;
        Raise(player, tablebet);
        break;
    case 4:
        player.action = Action::Allin;
        player.playerState = PlayerState::ALLIN;
        cout << "ALL IN " << tablebet << "$" << endl;
        break;
    default:
        cout << "INVALID BET";
        break;
    }
}

int main()
{

    Deck deck;
    int numPlayers = 5;
    TableInfo table(numPlayers);
    DealCard(&table, deck);

    // Chia bai cho player
    for (int i = 0; i < 2; ++i)
    {
        for (auto &r : table.player)
        {
            r.card[i] = deck.draw();
        }
    }

    // Chia bai tren ban
    for (int i = 0; i < 5; ++i)
    {
        table.communitycard[i] = deck.draw(); // Lấy lá bài từ deck và gán cho community card
    }

    for (const auto &tableRound : table.round)
    {
        std::wcout << roundtoString(tableRound) << endl; // in ra round hiện tại
        
        // show bài lên bàn theo round
        switch (tableRound)
        {
        case StatusRound::Flop:
            PrintCard(table.communitycard[0]);
            PrintCard(table.communitycard[1]);
            PrintCard(table.communitycard[2]);
            break;
        case StatusRound::Turn:
            PrintCard(table.communitycard[3]);
            break;
        case StatusRound::River:
            PrintCard(table.communitycard[4]);
            break;
        default:
            break;
        }

        
        
        int i;
        if (tableRound == StatusRound::Pre_flop){ // Nếu round Pre_Flop thì khởi tạo smallBlind bigBlind || Người chơi UTG sẽ bắt đầu bet
            i = 2;
            table.player[0].frontMoney = smallBlind;
            table.player[1].frontMoney = bigBlind;
            table.currTableBet = 20;
        } else { // Các round còn lại 
            i = 0;
            table.currTableBet = 0;
            for (auto &player_ : table.player)
            {
                player_.frontMoney = -1;
            }
        }
        
        // Các vòng bet
        while (table.currTableBet != table.player[i].frontMoney){
            cout << "\nCurrent Table Bet : " << table.currTableBet << endl;
            if (table.player[i].playerState == PlayerState::ALIVE || table.player[i].playerState == PlayerState::INIT )
            {
                if (table.currTableBet != 0)
                {
                    cout << "PLAYER " << i + 1 << " ";
                    GetAction(table.player[i], table.currTableBet);
                }
                else
                {
                    cout << "PLAYER " << i + 1<< " ";
                    GetAction1(table.player[i], table.currTableBet);
                }
            }
            ++i;
            if (i > table.numPlayer){
                i = 0;
            }
        }
        // Xác định lượng tiền trong POT, trừ tiền mà người chơi đã đặt cược
        for (auto &player_ : table.player)
        {
            if (player_.frontMoney != 0) {
                table.Pot += player_.frontMoney;
                player_.behindMoney -= player_.frontMoney;
            }
        }

        // Đặt số tiền người chơi bằng 0 để chuyển sang round mới
        for (auto &player_ : table.player)
        {
            player_.frontMoney = 0;
        }
        cout << "POT: " << table.Pot  << "$" << endl;
    }
    return 0;
}

