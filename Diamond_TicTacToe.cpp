#include"Games_Board.h"
#include"Games_UI.h"
#include <cstdlib> using namespace std;

//   Diamond_Board

Diamond_Board::Diamond_Board() : Board<char>(7, 7) {

    // Fill all cells with '#'
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++)
            board[i][j] = '#';

    //  NEW 7x7 DIAMOND SHAPE 

    // row 0
    board[0][3] = blank;

    // row 1
    board[1][2] = board[1][3] = board[1][4] = blank;

    // row 2
    for (int j = 1; j <= 5; j++) board[2][j] = blank;

    // row 3 (full row)
    for (int j = 0; j <= 6; j++) board[3][j] = blank;

    // row 4
    for (int j = 1; j <= 5; j++) board[4][j] = blank;

    // row 5
    board[5][2] = board[5][3] = board[5][4] = blank;

    // row 6
    board[6][3] = blank;
}



bool Diamond_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position!\n";
        return false;
    }

    if (board[x][y] == '#') {
        cout << "This cell is BLOCKED!\n";
        return false;
    }

    if (board[x][y] != blank) {
        cout << "Already taken!\n";
        return false;
    }

    board[x][y] = s;
    return true;
}



bool Diamond_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    int dx[4] = { 1, 1, 0, 1 };
    int dy[4] = { 0, 1, 1, -1 };

    bool has3[4] = { false };
    bool has4[4] = { false };

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {

            if (board[x][y] != s) continue;

            for (int d = 0; d < 4; d++) {

                int count = 1;
                int nx = x + dx[d];
                int ny = y + dy[d];

                while (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < columns &&
                    board[nx][ny] == s)
                {
                    count++;
                    nx += dx[d];
                    ny += dy[d];
                }
                if (count >= 3) has3[d] = true;
                if (count >= 4) has4[d] = true;
            }
        }
    }

    for (int d1 = 0; d1 < 4; d1++) {
        if (!has3[d1]) continue;
        for (int d2 = 0; d2 < 4; d2++) {
            if (!has4[d2]) continue;
            if (d1 != d2)
                return true;
        }
    }
    return false;
}



bool Diamond_Board::is_lose(Player<char>* player) {
    return false;
}



bool Diamond_Board::is_draw(Player<char>* player) {
    if (is_win(player)) return false;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (board[i][j] == blank)
                return false;

    return true;
}



bool Diamond_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}



bool Diamond_Board::has_line(Player<char>* player, int L) {
    char s = player->get_symbol();

    int dx[4] = { 1, 1, 0, 1 };
    int dy[4] = { 0, 1, 1, -1 };

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {

            if (board[x][y] != s) continue;

            for (int d = 0; d < 4; d++) {
                int count = 1;

                int nx = x + dx[d];
                int ny = y + dy[d];

                while (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < columns &&
                    board[nx][ny] == s)
                {
                    count++;
                    nx += dx[d];
                    ny += dy[d];
                }

                if (count >= L) return true;
            }
        }
    }
    return false;
}



// NEW inside_diamond FOR 7×7 
bool Diamond_Board::inside_diamond(int x, int y) const {
    if (x < 0 || x >= 7 || y < 0 || y >= 7)
        return false;

    if (x == 0) return y == 3;
    if (x == 1) return y >= 2 && y <= 4;
    if (x == 2) return y >= 1 && y <= 5;
    if (x == 3) return true;               // entire row playable
    if (x == 4) return y >= 1 && y <= 5;
    if (x == 5) return y >= 2 && y <= 4;
    if (x == 6) return y == 3;

    return false;
}



bool Diamond_Board::is_cell_empty(int x, int y) const {
    return board[x][y] == '.';
}

//   Diamond_UI
Diamond_UI::Diamond_UI()
    : UI<char>("Welcome to Diamond Tic-Tac-Toe!", 3) {}



Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

bool Diamond_Board::has_line_of_3(char s) {
    int dx[] = { 1, 0, 1, 1 };
    int dy[] = { 0, 1, 1, -1 };
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {

            if (board[x][y] != s) continue;
            if (!inside_diamond(x, y)) continue;

            for (int d = 0; d < 4; d++) {
                int count = 1;
                int nx = x + dx[d], ny = y + dy[d];

                while (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < columns &&
                    inside_diamond(nx, ny) &&
                    board[nx][ny] == s)
                {
                    count++;
                    nx += dx[d];
                    ny += dy[d];
                }

                if (count >= 3) return true;
            }
        }
    }
    return false;
}



bool Diamond_Board::has_line_of_4(char s) {
    int dx[] = { 1, 0, 1, 1 };
    int dy[] = { 0, 1, 1, -1 };
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {

            if (board[x][y] != s) continue;
            if (!inside_diamond(x, y)) continue;

            for (int d = 0; d < 4; d++) {
                
                int count = 1;
                int nx = x + dx[d], ny = y + dy[d];

                while (nx >= 0 && nx < rows &&
                    ny >= 0 && ny < columns &&
                    inside_diamond(nx, ny) &&
                    board[nx][ny] == s)
                {
                    count++;
                    nx += dx[d];
                    ny += dy[d];
                }

                if (count >= 4) return true;
            }
        }
    }
    return false;
}

//  AI Evaluation 
int evaluate(Diamond_Board* board, char AI, char YOU) {
    // لو الخصم ممكن يكمل خط 3+4 → منع فوري
    if (board->has_line_of_3(YOU) && board->has_line_of_4(YOU)) return -10000;
    // لو AI ممكن يكمل خط 3+4 → الفوز
    if (board->has_line_of_3(AI) && board->has_line_of_4(AI)) return 10000;

    int score = 0;
    if (board->has_line_of_4(AI)) score += 50;
    if (board->has_line_of_3(AI)) score += 20;
    if (board->has_line_of_4(YOU)) score -= 50;
    if (board->has_line_of_3(YOU)) score -= 20;

    return score;
}
//  Candidate Moves Generator
vector<pair<int, int>> get_candidate_moves(Diamond_Board* board) {
    vector<pair<int, int>> moves;
    for (int i = 0; i < board->get_rows(); i++) {
        for (int j = 0; j < board->get_columns(); j++) {
            if (!board->is_cell_empty(i, j)) continue;
            if (!board->inside_diamond(i, j)) continue;

            bool near_mark = false;
            for (int dx = -1; dx <= 1; dx++)
                for (int dy = -1; dy <= 1; dy++) {
                    int ni = i + dx, nj = j + dy;
                    if (ni >= 0 && ni < board->get_rows() && nj >= 0 && nj < board->get_columns())
                        if (board->get_value(ni, nj) != '.') near_mark = true;
                }
            if (near_mark) moves.push_back({ i,j });
        }
    }
    return moves;
}
//  Minimax Algorithm
int minimax(Diamond_Board* board, char AI, char YOU, bool is_ai_turn, int depth, int max_depth) {
    int score = evaluate(board, AI, YOU);
    if (score == 10000 || score == -10000 || depth >= max_depth) return score;

    vector<pair<int, int>> moves = get_candidate_moves(board);
    if (moves.empty()) return 0;

    if (is_ai_turn) {
        int best = -10000;
        for (auto move : moves) {
            board->set_value(move.first, move.second, AI);
            best = max(best, minimax(board, AI, YOU, false, depth + 1, max_depth));
            board->set_value(move.first, move.second, '.');
        }
        return best;
    }
    else {
        int best = 10000;
        for (auto move : moves) {
            board->set_value(move.first, move.second, YOU);
            best = min(best, minimax(board, AI, YOU, true, depth + 1, max_depth));
            board->set_value(move.first, move.second, '.');
        }
        return best;
    }
}

//  Diamond_UI get_move
Move<char>* Diamond_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << "\n" << player->get_name() << " enter row and column (0-6): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    cout << player->get_name() << " (Computer) is thinking...\n";
    Diamond_Board* dboard = dynamic_cast<Diamond_Board*>(player->get_board_ptr());
    char AI = player->get_symbol();
    char YOU = (AI == 'X') ? 'O' : 'X';

    // 1️⃣ Generate candidate moves
    vector<pair<int, int>> moves;
    for (int i = 0; i < dboard->get_rows(); i++) {
        for (int j = 0; j < dboard->get_columns(); j++) {
            if (dboard->is_cell_empty(i, j) && dboard->inside_diamond(i, j)) {
                moves.push_back({ i,j });
            }
        }
    }
    
    // 2️⃣ First: Check for blocking moves (prevent opponent win)
    for (auto move : moves) {
        dboard->set_value(move.first, move.second, YOU);
        if (dboard->has_line_of_3(YOU) && dboard->has_line_of_4(YOU)) {
            // فورًا نلعب هنا لمنع الخصم
            dboard->set_value(move.first, move.second, '.');
            cout << "Computer blocked at (" << move.first << "," << move.second << ")\n";
            return new Move<char>(move.first, move.second, AI);
        }
        dboard->set_value(move.first, move.second, '.');
    }

    // 3️⃣ If no immediate threat, use minimax to choose best move
    int best_score = -10000, best_x = -1, best_y = -1;
    for (auto move : moves) {
        dboard->set_value(move.first, move.second, AI);
        int score = minimax(dboard, AI, YOU, false, 0, 3); // depth 3
        dboard->set_value(move.first, move.second, '.');

        if (score > best_score) {
            best_score = score;
            best_x = move.first;
            best_y = move.second;
        }
    }

    cout << "Computer played (" << best_x << "," << best_y << ")\n";
    return new Move<char>(best_x, best_y, AI);
}
