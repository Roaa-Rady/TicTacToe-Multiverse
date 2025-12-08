#include "Games_Board.h"
#include "Games_UI.h"
#include <cstdlib>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

// Board //

Misere_TicTacToe_Board::Misere_TicTacToe_Board() : Board<char>(3, 3) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool Misere_TicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position!\n";
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

bool Misere_TicTacToe_Board::is_lose(Player<char>* player) {
    char sym = player->get_symbol();

    auto line = [&](char a, char b, char c) {
        return (a == sym && b == sym && c == sym);
        };

    for (int i = 0; i < 3; i++)
        if (line(board[i][0], board[i][1], board[i][2]))
            return true;

    for (int j = 0; j < 3; j++)
        if (line(board[0][j], board[1][j], board[2][j]))
            return true;

    if (line(board[0][0], board[1][1], board[2][2])) return true;
    if (line(board[0][2], board[1][1], board[2][0])) return true;

    return false;
}

bool Misere_TicTacToe_Board::is_win(Player<char>*) { return false; }

bool Misere_TicTacToe_Board::is_draw(Player<char>* p) { return (n_moves == 9 && !is_lose(p)); }

bool Misere_TicTacToe_Board::game_is_over(Player<char>* p) { return is_lose(p) || is_draw(p); }

//// UI ////
Misere_TicTacToe_UI::Misere_TicTacToe_UI() : UI<char>("Welcome to Misère Tic Tac Toe!", 3) {}

Player<char>* Misere_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

int empty_cells(const Misere_TicTacToe_Board* b) {
    int cnt = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (b->get_value(i, j) == '.') cnt++;
    return cnt;
}

int minimax(Misere_TicTacToe_Board* board, bool is_ai_turn, char ai_sym, char human_sym) {
    Player<char> dummy("temp", is_ai_turn ? ai_sym : human_sym, PlayerType::HUMAN);
    if (board->is_lose(&dummy)) {
        return is_ai_turn ? -100000 + empty_cells(board) : 100000 - empty_cells(board);
    }

    if (empty_cells(board) == 0) return 0;

    if (is_ai_turn) {
        int best = -999999;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board->get_value(i, j) == '.') {
                    board->set_value(i, j, ai_sym);
                    int val = minimax(board, false, ai_sym, human_sym);
                    board->set_value(i, j, '.');
                    best = max(best, val);
                }
        return best;
    }
    else {
        int best = 999999;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (board->get_value(i, j) == '.') {
                    board->set_value(i, j, human_sym);
                    int val = minimax(board, true, ai_sym, human_sym);
                    board->set_value(i, j, '.');
                    best = min(best, val);
                }
        return best;
    }
}
Move<char>* Misere_TicTacToe_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << player->get_name() << " (" << player->get_symbol() << ") Enter x y (0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    Misere_TicTacToe_Board* board = dynamic_cast<Misere_TicTacToe_Board*>(player->get_board_ptr());
    char AI = player->get_symbol();
    char YOU = (AI == 'X') ? 'O' : 'X';

    vector<pair<int, int>> possibleMoves;
    vector<pair<int, int>> safeMoves;

    // اجمع كل الحركات الممكنة
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board->get_value(i, j) == '.') {
                possibleMoves.push_back({ i,j });

                // تحقق من الخسارة الفورية
                board->set_value(i, j, AI);
                Player<char> tmpAI("tempAI", AI, PlayerType::COMPUTER);
                tmpAI.set_board_ptr(board);
                bool causesLose = board->is_lose(&tmpAI);
                board->set_value(i, j, '.');

                if (!causesLose) safeMoves.push_back({ i,j });
            }
        }
    }

    // لو مافيش safeMoves → fallback = كل possibleMoves
    if (safeMoves.empty()) safeMoves = possibleMoves;

    int best_x = -1, best_y = -1;
    int best_score = -999999;

    // تقييم كل الحركات الممكنة (طباعة)
    for (auto move : possibleMoves) {
        board->set_value(move.first, move.second, AI);
        int score = minimax(board, false, AI, YOU);
        board->set_value(move.first, move.second, '.');

        cout << "Evaluating Move At (" << move.first << ", " << move.second << ") = " << score;
        if (find(safeMoves.begin(), safeMoves.end(), move) != safeMoves.end())
            cout << " [SAFE]";
        cout << "\n";

        // اختار أفضل حركة ضمن safeMoves إذا موجودة
        if (find(safeMoves.begin(), safeMoves.end(), move) != safeMoves.end()) {
            if (score > best_score || best_score == -999999) {
                best_score = score;
                best_x = move.first;
                best_y = move.second;
            }
        }
    }

    // fallback نهائي: لو كل شيء فشل (مافيش safeMoves)
    if (best_x == -1 || best_y == -1) {
        best_x = safeMoves[0].first;
        best_y = safeMoves[0].second;
    }

    cout << player->get_name() << " (Computer) played (" << best_x << ", " << best_y << ")\n";
    return new Move<char>(best_x, best_y, AI);
}
