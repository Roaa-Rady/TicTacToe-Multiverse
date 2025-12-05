#include"games_Board.h"
#include"games_UI.h"
//added for AI
#include <vector>
#include <algorithm>
#include <climits>
#include <windows.h>
using namespace std;


// ====================== AI player ======================
int evaluate_5x5(const vector<vector<char>>& board, char me, char opp) {
    int score = 0;
    auto line = [&](int count_me, int count_opp) {
        if (count_me == 3) return 10000;
        if (count_opp == 3) return -10000;
        if (count_me == 2 && count_opp == 0) return 500;
        if (count_opp == 2 && count_me == 0) return -500;
        if (count_me == 1 && count_opp == 0) return 50;
        if (count_opp == 1 && count_me == 0) return -50;
        return 0;
        };

    // Rows + Columns
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            // Row
            int m = 0, o = 0;
            for (int k = 0; k < 3; ++k) {
                char c = board[i][j + k];
                if (c == me) m++;
                else if (c == opp) o++;
            }
            score += line(m, o);

            // Column
            m = o = 0;
            for (int k = 0; k < 3; ++k) {
                char c = board[j + k][i];
                if (c == me) m++;
                else if (c == opp) o++;
            }
            score += line(m, o);
        }
    }
    return score;
}

// Minimax function
int minimax_5x5(vector<vector<char>> board, int depth, bool maximizing, char me, char opp, int alpha, int beta) {
    if (depth == 0) return evaluate_5x5(board, me, opp);

    int best = maximizing ? INT_MIN : INT_MAX;

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '.') {
                board[i][j] = maximizing ? me : opp;
                int val = minimax_5x5(board, depth - 1, !maximizing, me, opp, alpha, beta);
                board[i][j] = '.';

                if (maximizing) {
                    best = max(best, val);
                    alpha = max(alpha, best);
                }
                else {
                    best = min(best, val);
                    beta = min(beta, best);
                }
                if (beta <= alpha) return best;
            }
        }
    }
    return best;
}

// choosing best move function
pair<int, int> get_best_move_5x5(const vector<vector<char>>& board, char me, char opp) {
    pair<int, int> best_move = { -1, -1 };
    int best_score = -999999;

    // 1. immediate win
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '.') {
                vector<vector<char>> temp = board;
                temp[i][j] = me;
                if (evaluate_5x5(temp, me, opp) >= 10000) {
                    return { i, j };  
                }
            }
        }
    }

    // 2. block my win
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '.') {
                vector<vector<char>> temp = board;
                temp[i][j] = opp;
                if (evaluate_5x5(temp, me, opp) <= -10000) {
                    return { i, j };  
                }
            }
        }
    }

    // 3. best attacking play
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '.') {
                vector<vector<char>> temp = board;
                temp[i][j] = me;
                int score = evaluate_5x5(temp, me, opp);
                if (score > best_score) {
                    best_score = score;
                    best_move = { i, j };
                }
            }
        }
    }

    // strong move? play it
    if (best_move.first != -1) {
        return best_move;
    }

    // no strong move? play in strong position
    int centers[][2] = { {2,2}, {1,1}, {1,3}, {3,1}, {3,3}, {2,1}, {2,3}, {0,0}, {0,4}, {4,0}, {4,4} };
    for (int k = 0; k < 12; ++k) {
        int i = centers[k][0], j = centers[k][1];
        if (board[i][j] == '.') {
            return { i, j };
        }
    }

    // any empty cell (does not happen)
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (board[i][j] == '.') return { i, j };

    return { 0,0 }; // not gonna happen
}
//


// ------------------- Board Implementation -------------------
TicTacToe5x5_Board::TicTacToe5x5_Board() : Board<char>(5, 5), blank_symbol('.') {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool TicTacToe5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= 5 || y < 0 || y >= 5) {
        cout << "Invalid position! Row and column must be 0-4.\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Cell already taken!\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;
    return true;
}

int TicTacToe5x5_Board::count_3_in_row(char sym) {
    int count = 0;

    // Rows
    for (int i = 0; i < 5; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                count++;

    // Columns
    for (int j = 0; j < 5; j++)
        for (int i = 0; i <= 2; i++)
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                count++;

    // Diagonals
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                count++;
            if (board[i + 2][j] == sym && board[i + 1][j + 1] == sym && board[i][j + 2] == sym)
                count++;
        }

    return count;
}

bool TicTacToe5x5_Board::is_win(Player<char>* p) {
    if (!p) return false;
    if (!game_is_over(p)) return false; 

    int my_count = count_3_in_row(p->get_symbol());
    char other = '.'; 
    for (auto& row : board)
        for (auto& c : row)
            if (c != '.' && c != p->get_symbol())
                other = c;

    int other_count = count_3_in_row(other);

    return my_count > other_count;
}

bool TicTacToe5x5_Board::is_lose(Player<char>* p) {
    if (!p) return false;
    if (!game_is_over(p)) return false;

    int my_count = count_3_in_row(p->get_symbol());

    char other = '.';
    for (auto& row : board)
        for (auto& c : row)
            if (c != '.' && c != p->get_symbol())
                other = c;

    int other_count = count_3_in_row(other);

    return my_count < other_count;
}

bool TicTacToe5x5_Board::is_draw(Player<char>* p) {
    if (!p) return false;
    if (!game_is_over(p)) return false;

    int my_count = count_3_in_row(p->get_symbol());

    char other = '.';
    for (auto& row : board)
        for (auto& c : row)
            if (c != '.' && c != p->get_symbol())
                other = c;

    int other_count = count_3_in_row(other);

    return my_count == other_count;
}
bool TicTacToe5x5_Board::game_is_over(Player<char>*) { return n_moves >= 25; }
// ------------------- UI Implementation -------------------
TicTacToe5x5_UI::TicTacToe5x5_UI() : UI<char>("Welcome to 5x5 Tic Tac Toe!", 2) {}

Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* b = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " enter x y (0-4): ";
        cin >> x >> y;
    }
    else {
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (b->get_board_matrix()[x][y] != '.');

        cout << player->get_name() << " (Computer) played (" << x << "," << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

void TicTacToe5x5_UI::display_final_result(TicTacToe5x5_Board* board, Player<char>* p1, Player<char>* p2) {
    int p1_count = board->count_3_in_row(p1->get_symbol());
    int p2_count = board->count_3_in_row(p2->get_symbol());

    cout << "\nGame Over!\n";
    cout << p1->get_name() << " has " << p1_count << " sets of 3-in-row.\n";
    cout << p2->get_name() << " has " << p2_count << " sets of 3-in-row.\n";

    if (p1_count > p2_count) cout << p1->get_name() << " wins!\n";
    else if (p2_count > p1_count) cout << p2->get_name() << " wins!\n";
    else cout << "It's a tie!\n";
}
