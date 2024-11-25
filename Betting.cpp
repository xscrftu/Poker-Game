#include <iostream>
#include <vector>
#include "struct.h"
#include "compare.h"
#include "print.h"
#include <io.h>
#include <fcntl.h>
using namespace std;
const int minRaise = 40;
const int smallBlind = 10, bigBlind = 20;
enum class StatusRound
{
    Pre_flop = 1,
    Flop,
    Turn,
    River
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
    vector<Card> fullHand;
    int score;
    Position pos;
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
    if (player.behindMoney <= tablebet){
        player.frontMoney = player.behindMoney;
        player.playerState = PlayerState::ALLIN;
    }
    player.frontMoney = tablebet;
}
void Check(Player &player, int &tablebet)
{
    player.frontMoney = 0;
}

void Raise(Player &player, int &tablebet)
{
    int moneyRaise;
    
    if (player.behindMoney <= tablebet)
    {
        std::wcout << L"You have not enough money to RAISE. Just can ALL_IN !!\n";
        std::wcout << L"Please decide your option: y - ALL_IN || n - Re_action\n";
        char ch;
        std::wcout << L"Your option: ";
        std::cin >> ch;
        if (ch == 'y'){
            std::wcout << L"You have just ALL IN ";
            player.frontMoney = player.behindMoney;
            player.playerState = PlayerState::ALLIN;
        }
        // } else {
        //     GetAction(player,tablebet); // Nếu người chơi chọn n (nghĩa là NO) thì cho người chơi option lại
        // }
    }
    else
    {
        std::wcout << L"Enter your raise money (>= min_raise): ";
        std::cin >> moneyRaise;
        while (moneyRaise < 2 * tablebet || moneyRaise < minRaise || moneyRaise > player.behindMoney)
        {
            std::wcout << L"Raise amount must be at least double the current table bet (" << tablebet << L"$) and (<=" << player.behindMoney << L"$). Please enter a valid amount: ";
            std::cin >> moneyRaise;
        }
        if (moneyRaise == player.behindMoney) {
            std::wcout << L"ALL IN !!!";
            player.playerState = PlayerState::ALLIN;
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
    std::wstring rankStr;
    std::wstring suitStr;

    // Chuyển đổi Rank sang chuỗi
    switch (card.Rank)
    {
    case CardRank::Two:
        rankStr = L"2";
        break;
    case CardRank::Three:
        rankStr = L"3";
        break;
    case CardRank::Four:
        rankStr = L"4";
        break;
    case CardRank::Five:
        rankStr = L"5";
        break;
    case CardRank::Six:
        rankStr = L"6";
        break;
    case CardRank::Seven:
        rankStr = L"7";
        break;
    case CardRank::Eight:
        rankStr = L"8";
        break;
    case CardRank::Nine:
        rankStr = L"9";
        break;
    case CardRank::Ten:
        rankStr = L"10";
        break;
    case CardRank::Jack:
        rankStr = L"J";
        break;
    case CardRank::Queen:
        rankStr = L"Q";
        break;
    case CardRank::King:
        rankStr = L"K";
        break;
    case CardRank::Ace:
        rankStr = L"A";
        break;
    }

    // Chuyển đổi Suit sang chuỗi
    switch (card.Suit)
    {
    case CardSuit::Hearts:
        suitStr = L"\u2665";
        break;
    case CardSuit::Diamonds:
        suitStr = L"\u2666";
        break;
    case CardSuit::Clubs:
        suitStr = L"\u2663";
        break;
    case CardSuit::Spades:
        suitStr = L"\u2660";
        break;
    }

    // In lá bài với định dạng "A ♠" hoặc "10 ♥"
    std::wcout << rankStr << " " << suitStr << std::endl;
}
void GetAction(Player &player, int &tablebet)
{
    int playerAction;
    std::wcout << L"Your stack: " << player.behindMoney << L"$\n" ;
    std::wcout << L"Choose your Action: 1 - Fold | 2 - Call | 3 - Raise | 4 - Allin\n";
    std::wcout << L"Your choose: ";
    while (!(std::cin >> playerAction) || playerAction < 1 || playerAction > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::wcout << L"Enter again 1 <= n <= 4: ";
    }

    switch (playerAction)
    {
    case 1:
        player.action = Action::Fold;
        player.playerState = PlayerState::OUT;
        std::wcout << L"PLAYER FOLD. You are out of this game\n";
        break;
    case 2:
        player.action = Action::Call;
        player.playerState = PlayerState::ALIVE;
        Call(player, tablebet);
        std::wcout << L"CALL " << tablebet << L"$" <<endl;
        break;
    case 3:
        player.action = Action::Raise;
        player.playerState = PlayerState::ALIVE;
        Raise(player, tablebet);
        std::wcout << L"RAISE " << tablebet << L"$" << endl;
        break;
    case 4:
        player.action = Action::Allin;
        player.playerState = PlayerState::ALLIN;
        Allin(player, tablebet);
        std::wcout << L"ALL IN " << tablebet << L"$" << endl;
        break;
    default:
        std::wcout << L"INVALID BET";
        break;
    }
}
void GetAction1(Player &player, int &tablebet)
{
    int playerAction;
    std::wcout << L"Your stack: " << player.behindMoney << L"$\n" ;
    std::wcout << L"Choose your Action: 1 - Fold | 2 - Check | 3 - Raise | 4 - Allin\n";
    std::wcout << L"Your choose: ";
    while (!(std::cin >> playerAction) || playerAction < 1 || playerAction > 4){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::wcout << L"Enter again 1 <= n <= 4: ";
    }
    switch (playerAction)
    {
    case 1:
        player.action = Action::Fold;
        player.playerState = PlayerState::OUT;
        std::wcout << L"PLAYER FOLD. You are out of this game\n";
        break;
    case 2:
        player.action = Action::Check;
        player.playerState = PlayerState::ALIVE;
        Check(player, tablebet);
        std::wcout << L"PLAYER CHECK!\n";
        break;
    case 3:
        player.action = Action::Raise;
        player.playerState = PlayerState::ALIVE;
        Raise(player, tablebet);
        break;
    case 4:
        player.action = Action::Allin;
        player.playerState = PlayerState::ALLIN;
        Allin(player, tablebet);
        std::wcout << L"ALL IN " << tablebet << L"$" << endl;
        break;
    default:
        std::wcout << L"INVALID BET";
        break;
    }
}
bool CheckFold(TableInfo *table, PlayerState ps, int j) // Hàm check liệu người chơi có bỏ bài hết không
{
    for (int i = 0; i < (*table).player.size(); ++i){
        Player t = (*table).player[i];
        if (t.playerState == PlayerState::OUT || i == j) // Kiểm tra tất cả trạng thái người chơi TRỪ người chơi thứ j(nghĩa là người chơi hiện tại)
        {
            continue;
        } else if ( t.playerState != ps){
            return false;
        }
    }
    return true;
}
bool CheckAllin(TableInfo *table, PlayerState ps) // Hàm check liệu người chơi có all in hết không
{
    for (int i = 0; i < (*table).player.size(); ++i){
        Player t = (*table).player[i];
        if (t.playerState == PlayerState::OUT) // Kiểm tra tất cả trạng thái người chơi
        {
            continue;
        } else if ( t.playerState != ps){
            return false;
        }
    }
    return true;
}

void findBestHand(const std::vector<Card>& cards, int k, int start, std::vector<Card>& current, 
                  double& maxScore, std::vector<Card>& bestHand) {
    if (current.size() == k) {
        Hand hand;
        for (size_t i = 0; i < current.size(); ++i) { 
            hand.cards[i] = current[i]; 
        }
        SortHand(&hand);
        for (size_t i = 0; i < current.size(); ++i) { 
            current[i] = hand.cards[i]; 
        }
        double score = EvaluateHand(&hand); 
        if (score > maxScore) {
            maxScore = score;
            bestHand = current; 
        }
        return;
    }

    for (int i = start; i < cards.size(); ++i) {
        current.push_back(cards[i]);
        findBestHand(cards, k, i + 1, current, maxScore, bestHand);
        current.pop_back();
    }
}
void printCombination(const std::vector<Card>& combination) {
    for (const Card& card : combination) {
        std::wcout << CardRankToString(card.Rank) << " " << CardSuitToString(card.Suit); 
        std::wcout << "  ";
    }
    std::wcout << std::endl;
}
int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
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
        std::wcout << L"~~~ " << roundtoString(tableRound) << L" ~~~" << endl; // in ra round hiện tại
        
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
        
        int i; // Biến index người chơi 
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
            if (CheckFold(&table, PlayerState::OUT, i) || CheckAllin(&table, PlayerState::ALLIN)) { // Nếu tất cả người chơi (trừ người chơi i) đã Fold hoặc All-In hủy vòng lặp
                break;
            }

            // Nếu người chơi còn sống hoặc mới khởi tạo thì cho người chơi hành động
            if (table.player[i].playerState == PlayerState::ALIVE || table.player[i].playerState == PlayerState::INIT ) 
            {
                wcout << "\nCurrent Table Bet : " << table.currTableBet << "$" << endl;
                wcout << "PLAYER " << i + 1 << " ";
                if (table.currTableBet != 0)
                {
                    GetAction(table.player[i], table.currTableBet);
                }
                else
                {
                    GetAction1(table.player[i], table.currTableBet);
                }
            }
            ++i;
            if (i > table.numPlayer) i = 0; // Khởi tạo lại i khi i vượt quá số người chơi
        }
        
        // Xác định lượng tiền trong POT, trừ tiền mà người chơi đã đặt cược
        for (auto &player_ : table.player)
        {
            if (player_.frontMoney != 0 && player_.playerState != PlayerState::OUT && player_.frontMoney != -1) { // Kiểm tra nếu tiền cược # 0 và trạng thái người chơi # OUT thì trừ tiền trong POT
                table.Pot += player_.frontMoney;
                player_.behindMoney -= player_.frontMoney;
            }
        }

        if (tableRound == StatusRound::River){
            for (auto &player : table.player)
            {
                if (player.playerState == PlayerState::ALIVE || player.playerState == PlayerState::ALLIN){
                    // Thêm 2 lá bài riêng biệt của người chơi vào fullHand
                    player.fullHand = vector<Card>(begin(player.card), end(player.card));

                    // Thêm các lá bài cộng đồng vào fullHand
                    for (auto &card : table.communitycard)
                    {
                        player.fullHand.push_back(card);  // Thêm bài cộng đồng
                    }
                }
            }
            float maxScore = -1;  // Khởi tạo giá trị score tối đa
            vector<Card> bestHand;
        
            // Tìm và in ra tổ hợp tốt nhất của mỗi người chơi
            for (auto &player : table.player) {
                if (player.playerState == PlayerState::ALIVE || player.playerState == PlayerState::ALLIN){
                    vector<Card> current;
                    double playerMaxScore = -1;  // Khởi tạo giá trị max cho từng người chơi
                    findBestHand(player.fullHand, 5, 0, current, playerMaxScore, bestHand);
                    printCombination(bestHand);
                    wcout << L"Score: " << playerMaxScore << endl;
                    player.score = playerMaxScore;
                }
            }
            // Tìm người chơi có điểm số cao nhất
            Player winner;
            float maxxxx = -1;
            for (auto &player : table.player) {
                if (player.playerState == PlayerState::ALIVE || player.playerState == PlayerState::ALLIN){
                    if (player.score > maxxxx) {
                        maxxxx = player.score;
                    }
                }
            }

            int io = 0;
            while (io < 6){
                if (table.player[i].playerState == PlayerState::ALIVE || table.player[i].playerState == PlayerState::ALLIN){
                    if (table.player[io].score == maxxxx) {
                        table.player[io].behindMoney += table.Pot;
                        wcout << "Player " << io + 1 << "win";
                    }
                }
                ++io;
            }
        }
            
        

        // Đặt số tiền người chơi bằng 0 để chuyển sang round mới
        for (auto &player_ : table.player)
        {
            player_.frontMoney = 0;
        }
        cout << "\nPOT: " << table.Pot  << "$" << endl;
    }
    return 0;
}

