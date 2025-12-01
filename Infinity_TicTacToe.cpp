#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
#include <deque>
#include <utility>
#include <cstdlib>
#include <ctime>
using namespace std;


// INFINITY TIC-TAC-TOE BOARD //

InfinityTicTacToe_Board::InfinityTicTacToe_Board() : Board<char>(3, 3) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = '.';
    n_moves = 0;
}



bool InfinityTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != '.')
        return false;

    board[x][y] = sym;
    move_history.push_back({ {x, y}, sym });
    n_moves++;

    if (n_moves % 3 == 0) {
        if (!move_history.empty()) {
            auto oldest = move_history.front();
            move_history.pop_front();
            board[oldest.first.first][oldest.first.second] = '.';
        }
    }

    return true;
}
bool InfinityTicTacToe_Board::check_current_win(char sym) const {
    // Rows
    for (int i = 0; i < 3; ++i)
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) return true;
    // Columns
    for (int j = 0; j < 3; ++j)
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) return true;
    // Diagonals
    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;
    return false;
}


bool InfinityTicTacToe_Board::is_win(Player<char>* player) {
    return check_current_win(player->get_symbol());
}

bool InfinityTicTacToe_Board::is_lose(Player<char>* player) {
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    return check_current_win(opp);
}

bool InfinityTicTacToe_Board::is_draw(Player<char>*) {
    return false;
}

bool InfinityTicTacToe_Board::game_is_over(Player<char>*) {
    return is_win(nullptr) || is_lose(nullptr);
}

void InfinityTicTacToe_Board::display_board() const {
    cout << "\n   0   1   2\n";
    for (int i = 0; i < 3; ++i) {
        cout << i << "  ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "  ---+---+---\n";
    }
    cout << endl;
}

// INFINITY TIC-TAC-TOE UI //

InfinityTicTacToe_UI::InfinityTicTacToe_UI()
    : UI<char>("=== Welcome to Infinity Tic-Tac-Toe ===", 3) {}

Player<char>* InfinityTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* InfinityTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter x y (0-2): ";
        cin >> x >> y;

        while (cin.fail() ||  x < 0 || x > 2 || y < 0 || y > 2) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid! Enter x y again (0-2): ";
            cin >> x >> y;
        }
    }
    else {
        // Random AI
        Board<char>* b = player->get_board_ptr();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (b->get_board_matrix()[x][y] != '.');

        cout << player->get_name() << " (Computer) played (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}
void InfinityTicTacToe_UI::display_final_result(Player<char>* p1, Player<char>* p2) {
    auto* board = static_cast<InfinityTicTacToe_Board*>(p1->get_board_ptr());
    board->display_board();

    if (board->is_win(p1))
        cout << "Player " << p1->get_name() << " (X) WINS THE GAME!\n";
    else if (board->is_win(p2))
        cout << "Player " << p2->get_name() << " (O) WINS THE GAME!\n";
    else
        cout << "Game over without winner (shouldn't happen)\n";
}

Player<char>** InfinityTicTacToe_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    string name;
    int choice;

    cout << "Player 1 name (X): ";
    cin >> name;
    cout << "Human (1) or Computer (2)? ";
    cin >> choice;
    players[0] = create_player(name, 'X', (choice == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));

    cout << "Player 2 name (O): ";
    cin >> name;
    cout << "Human (1) or Computer (2)? ";
    cin >> choice;
    players[1] = create_player(name, 'O', (choice == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));

    return players;
}
