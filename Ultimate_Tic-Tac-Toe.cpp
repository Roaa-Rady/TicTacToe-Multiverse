#include "Games_Board.h"
#include "Games_UI.h"
#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// ---------------- Ultimate Board ----------------
Ultimate_Board::Ultimate_Board()
    : Board<char>(9, 9)  // Main board 9x9 لعرض كل Sub-boards
{
    subBoards.resize(3, vector<Board<char>*>(3, nullptr));
    main_board_status.resize(3, vector<char>(3, '.')); // حالة كل Sub-board

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            subBoards[i][j] = new X_O_Board(); // كل Sub-board 3x3

    last_x = last_y = -1;

    // تهيئة البورد كله بالـ blank
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = '.';
}

// ---------------- Sub-Boards Access ----------------
vector<vector<Board<char>*>>& Ultimate_Board::access_subBoards() {
    return subBoards;
}


// ---------------- Update Board ----------------
bool Ultimate_Board::update_board(Move<char>* move) {
    int mx = move->get_x();
    int my = move->get_y();
    char sym = move->get_symbol();

    if (mx < 0 || mx>8 || my < 0 || my>8) {
        cout << "Invalid coordinates!\n";
        return false;
    }

    int sbx = mx / 3;
    int sby = my / 3;
    int x = mx % 3;
    int y = my % 3;

    auto& subs = access_subBoards();
    Board<char>* sub = subs[sbx][sby];

    if (main_board_status[sbx][sby] != '.') {
        cout << "This sub-board is already finished!\n";
        return false;
    }

    Move<char>* sub_move = new Move<char>(x, y, sym);

    if (!sub->update_board(sub_move)) {
        delete sub_move;
        return false;
    }
    delete sub_move;

    // Update Main board status if sub-board won
    Player<char>* tmpP = new Player<char>("tmp", sym, PlayerType::HUMAN);
    tmpP->set_board_ptr(sub);
    if (sub->is_win(tmpP)) {
        main_board_status[sbx][sby] = sym; // Main board update
        // Copy sub-board to main 9x9 board for display
        auto mat = sub->get_board_matrix();
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[sbx * 3 + i][sby * 3 + j] = mat[i][j];
    }
    delete tmpP;

    // Required next board
    last_x = x;
    last_y = y;

    // Copy current move to main board
    board[sbx * 3 + x][sby * 3 + y] = sym;

    return true;
}

// ---------------- Board Status ----------------
bool Ultimate_Board::is_win(Player<char>* p) {
    char sym = p->get_symbol();
    return main_board_win(sym);
}

bool Ultimate_Board::is_lose(Player<char>* p) { return false; }

bool Ultimate_Board::is_draw(Player<char>* p) {
    if (is_win(p)) return false;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (main_board_status[i][j] == '.') return false;
    return true;
}

bool Ultimate_Board::game_is_over(Player<char>* p) {
    return is_win(p) || is_draw(p);
}

// ---------------- Check Main Board Win ----------------
bool Ultimate_Board::main_board_win(char sym) {
    for (int i = 0; i < 3; i++)
        if (main_board_status[i][0] == sym && main_board_status[i][1] == sym && main_board_status[i][2] == sym)
            return true;
    for (int j = 0; j < 3; j++)
        if (main_board_status[0][j] == sym && main_board_status[1][j] == sym && main_board_status[2][j] == sym)
            return true;
    if (main_board_status[0][0] == sym && main_board_status[1][1] == sym && main_board_status[2][2] == sym) return true;
    if (main_board_status[0][2] == sym && main_board_status[1][1] == sym && main_board_status[2][0] == sym) return true;
    return false;
}

// ---------------- Check Sub Board Full ----------------
bool Ultimate_Board::is_sub_board_full(int sx, int sy) {
    auto mat = subBoards[sx][sy]->get_board_matrix();
    for (auto& r : mat)
        for (auto& c : r)
            if (c == '.') return false;
    return true;
}

bool Ultimate_Board::force_anywhere() const {
    if (last_x == -1) return true;
    int sx = last_x, sy = last_y;
    auto mat = subBoards[sx][sy]->get_board_matrix();
    for (auto& r : mat)
        for (auto& c : r)
            if (c == '.') return false;
    return true;
}

 //---------------- Display Board 
void Ultimate_Board::display_board() {
    cout << "\nUltimate Board (9x9 with Sub-boards 3x3):\n";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j];
            if (j % 3 == 2 && j < 8) cout << " | ";
            else cout << " ";
        }
        cout << endl;
        if (i % 3 == 2 && i < 8) cout << "----------------------------------\n";
    }
}


// ---------------- Ultimate UI ----------------
Ultimate_UI::Ultimate_UI() : UI<char>("Welcome to Ultimate Tic Tac Toe!", 2) {}

// ---------------- Create Player ----------------
Player<char>* Ultimate_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

// ---------------- Get Move ----------------
Move<char>* Ultimate_UI::get_move(Player<char>* p) {
    int x, y;
    auto* board = dynamic_cast<Ultimate_Board*>(p->get_board_ptr());
    auto& subs = board->access_subBoards();

    if (p->get_type() == PlayerType::HUMAN) {
        auto req = board->get_required_subboard();
        if (req.first != -1)
            cout << "\nYou MUST play inside sub-board("
            << req.first << "," << req.second << ") unless it's full.\n";
        cout << p->get_name() << " enter global move (0-8) x y: ";
        cin >> x >> y;
    }
    else {
        while (true) {
            x = rand() % 9;
            y = rand() % 9;
            int sbx = x / 3, sby = y / 3;
            auto req = board->get_required_subboard();
            if (!board->force_anywhere()) {
                if (sbx != req.first || sby != req.second) continue;
            }
            auto mat = subs[sbx][sby]->get_board_matrix();
            if (mat[x % 3][y % 3] == '.') break;
        }
        cout << p->get_name() << " (Computer) plays (" << x << "," << y << ")\n";
    }
    return new Move<char>(x, y, p->get_symbol());
}

