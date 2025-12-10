#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cstdlib>
using namespace std;

// Board implementation
TicTacToe4x4_Board::TicTacToe4x4_Board() : Board<char>(4, 4) {
    board[0][0] = 'O'; board[0][1] = 'X'; board[0][2] = 'O'; board[0][3] = 'X';
    board[1][0] = '.'; board[1][1] = '.'; board[1][2] = '.'; board[1][3] = '.';
    board[2][0] = '.'; board[2][1] = '.'; board[2][2] = '.'; board[2][3] = '.';
    board[3][0] = 'X'; board[3][1] = 'O'; board[3][2] = 'X'; board[3][3] = 'O';
    n_moves = 0;
}
bool TicTacToe4x4_Board::update_board(Move<char>* move) {
    int encoded_from = move->get_x();
    int encoded_to = move->get_y();

    int from_x = encoded_from / 4;
    int from_y = encoded_from % 4;
    int to_x = encoded_to / 4;
    int to_y = encoded_to % 4;
    char sym = move->get_symbol();

    if (from_x < 0 || from_x >= 4 || from_y < 0 || from_y >= 4 ||
        to_x < 0 || to_x >= 4 || to_y < 0 || to_y >= 4) {
      
        return false;
    }
    if (this->get_value(from_x, from_y) != sym) {
        return false;
    }
    if (this->get_value(to_x, to_y) != '.') {
        return false;
    }
    int dx = abs(to_x - from_x);
    int dy = abs(to_y - from_y);

    bool orthogonal_step = (dx == 1 && dy == 0) || (dx == 0 && dy == 1);

    if (!orthogonal_step) {
        return false;
    }

    this->set_value(from_x, from_y, '.');
    this->set_value(to_x, to_y, sym);
    n_moves++;
    return true;
}
bool TicTacToe4x4_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c <= 1; c++) {
            if (board[r][c] == s && board[r][c + 1] == s && board[r][c + 2] == s) return true;
        }
    }
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r <= 1; r++) {
            if (board[r][c] == s && board[r + 1][c] == s && board[r + 2][c] == s) return true;
        }
    }
    for (int r = 0; r <= 1; r++) {
        for (int c = 0; c <= 1; c++) {
            if (board[r][c] == s && board[r + 1][c + 1] == s && board[r + 2][c + 2] == s) return true;
        }
    }
    for (int r = 0; r <= 1; r++) {
        for (int c = 2; c < 4; c++) {
            if (board[r][c] == s && board[r + 1][c - 1] == s && board[r + 2][c - 2] == s) return true;
        }
    }
    return false;
}

bool TicTacToe4x4_Board::is_lose(Player<char>* player) {return false;}
bool TicTacToe4x4_Board::is_draw(Player<char>* player) {   return false;}

bool TicTacToe4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

// AI 
vector<pair<pair<int, int>, pair<int, int>>> get_possible_moves(Board<char>* b, char sym)
{
    vector<pair<pair<int, int>, pair<int, int>>> moves;
    int dirctions[4][2] = { {1, 0}, {-1, 0}, {0, 1},  {0, -1} };
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (b->get_value(r, c) == sym) {
                for (auto& d : dirctions) {
                    int new_r = r + d[0];
                    int new_c = c + d[1];

                    if (new_r >= 0 && new_r < 4 && new_c >= 0 && new_c < 4 &&b->get_value(new_r, new_c) == '.')
                        moves.push_back({ {r, c}, {new_r, new_c} });
                }
            }
        }
    }
    return moves;
}

int evaluate_board(TicTacToe4x4_Board* b, char ai_sym, char opp_sym)
{
    Player<char> P_AI("ai", ai_sym, PlayerType::HUMAN);
    P_AI.set_board_ptr(b);
    if (b->is_win(&P_AI)) return 100;

    Player<char> P_OP("op", opp_sym, PlayerType::HUMAN);
    P_OP.set_board_ptr(b);
    if (b->is_win(&P_OP)) return -100;

    return 0;
}
int minimax(TicTacToe4x4_Board* b, int depth, bool maximizing,
    char ai_sym, char opp_sym)
{
    int score = evaluate_board(b, ai_sym, opp_sym);
    if (score == 100 || score == -100)
        return score - depth;

    if (depth == 0)
        return score;

    char current = maximizing ? ai_sym : opp_sym;
    auto moves = get_possible_moves(b, current);

    if (moves.empty()) return 0;

    if (maximizing)
    {
        int best = -10000;
        for (auto& mv : moves)
        {
            auto from = mv.first;
            auto to = mv.second;
            char saved = b->get_value(from.first, from.second);

            b->set_value(from.first, from.second, '.');
            b->set_value(to.first, to.second, saved);

            int val = minimax(b, depth - 1, false, ai_sym, opp_sym);

            b->set_value(from.first, from.second, saved);
            b->set_value(to.first, to.second, '.');

            best = max(best, val);
        }
        return best;
    }
    else
    {
        int best = 10000;
        for (auto& mv : moves)
        {
            auto f = mv.first;
            auto t = mv.second;
            char saved = b->get_value(f.first, f.second);

            b->set_value(f.first, f.second, '.');
            b->set_value(t.first, t.second, saved);

            int val = minimax(b, depth - 1, true, ai_sym, opp_sym);

            b->set_value(f.first, f.second, saved);
            b->set_value(t.first, t.second, '.');

            best = min(best, val);
        }
        return best;
    }
}
pair<pair<int, int>, pair<int, int>> find_best_move_minimax(TicTacToe4x4_Board* b, char ai_sym)
{
    char opp_sym = (ai_sym == 'X' ? 'O' : 'X');
    int best_val = -10000;
    pair<pair<int, int>, pair<int, int>> best_move = { {-1,-1},{-1,-1} };
    auto moves = get_possible_moves(b, ai_sym);

    for (auto& mv : moves)
    {
        auto f = mv.first;
        auto t = mv.second;
        char saved = b->get_value(f.first, f.second);
        int val = minimax(b, 6, false, ai_sym, opp_sym);

        b->set_value(f.first, f.second, '.');
        b->set_value(t.first, t.second, saved);
        b->set_value(f.first, f.second, saved);
        b->set_value(t.first, t.second, '.');
        if (val > best_val)
        {
            best_val = val;
            best_move = mv;
        }
    }
    return best_move;
}

// UI implementation
TicTacToe4x4_UI::TicTacToe4x4_UI()
    : UI<char>("=== 4x4 Moving Tic-Tac-Toe ===\nMove your token to an adjacent empty cell (Horizontal/Vertical ONLY)\nWin by getting 3 in a row!", 3) {
    srand(time(nullptr));
}

Player<char>* TicTacToe4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe4x4_UI::get_move(Player<char>* player) {
    Board<char>* b = player->get_board_ptr();
    char sym = player->get_symbol();
    //Human
    if (player->get_type() == PlayerType::HUMAN) {
        int from_x, from_y, to_x, to_y;
        while (true) {
            cout << "\n" << player->get_name() << " (" << sym << ") Move from (row col): ";
            cin >> from_x >> from_y;
            if (from_x < 0 || from_x >= 4 || from_y < 0 || from_y >= 4 || cin.fail()) {
                cout << "Invalid coordinates! Try again.\n";
                continue;
            }
            if (b->get_value(from_x, from_y) != sym) {
                cout << "That's not your token! You are " << sym << ".\n";
                continue;
            }
            cout << player->get_name() << " Move to (row col): ";
            cin >> to_x >> to_y;

            if (cin.fail() || to_x < 0 || to_x >= 4 || to_y < 0 || to_y >= 4) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid coordinates! Try again.\n";
                continue;
            }
            if (b->get_value(to_x, to_y) != '.') {
                cout << "Target cell is not empty!\n";
                continue;
            }
            int dx = abs(to_x - from_x);
            int dy = abs(to_y - from_y);
            if ((dx + dy) != 1) {
                cout << "Invalid move! Must be adjacent only.\n";
                continue;
            }
            int encoded_from = from_x * 4 + from_y;
            int encoded_to = to_x * 4 + to_y;
            return new Move<char>(encoded_from, encoded_to, sym);
        }
    }
    //AI
  cout << player->get_name() << " (AI) is thinking...\n";
  auto mv = find_best_move_minimax((TicTacToe4x4_Board*)b, sym);
    if (mv.first.first == -1) {
        return new Move<char>(0, 0, sym);
    }
    auto source = mv.first;
    auto target = mv.second;

    int encoded_from = source.first * 4 + source.second;
    int encoded_to = target.first * 4 + target.second;

    return new Move<char>(encoded_from, encoded_to, sym);
}
