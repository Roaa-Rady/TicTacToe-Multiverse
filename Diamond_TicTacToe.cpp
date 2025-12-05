#include"Games_Board.h"
#include"Games_UI.h"
#include <cstdlib> using namespace std;
// Diamond_Board IMPLEMENTATION

Diamond_Board::Diamond_Board() : Board<char>(5, 5) {

    // fill all with '#'
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            board[i][j] = '#';

    //// playable diamond cells
    board[2][2] = blank;

    board[1][2] = blank;
    board[2][1] = blank;
    board[2][3] = blank;
    board[3][2] = blank;

    board[0][2] = blank;
    board[1][1] = blank;
    board[1][3] = blank;
    board[2][0] = blank;
    board[2][4] = blank;
    board[3][1] = blank;
    board[3][3] = blank;
    board[4][2] = blank;

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

            // ???? ????????? ???????
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

bool Diamond_Board::inside_diamond(int x, int y) const {
    if (x < 0 || x >= 5 || y < 0 || y >= 5)
        return false;

    if (x == 0) return y == 2;
    if (x == 1) return y >= 1 && y <= 3;
    if (x == 2) return true;
    if (x == 3) return y >= 1 && y <= 3;
    if (x == 4) return y == 2;

    return false;
}

bool Diamond_Board::is_cell_empty(int x, int y) const {
    return board[x][y] == '.';
}

//



// Diamond_UI IMPLEMENTATION

Diamond_UI::Diamond_UI()
    : UI<char>("Welcome to Diamond Tic-Tac-Toe!", 3) {}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating "
        << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

//
// Diamond AI helper functions in Diamond_Board
bool Diamond_Board::has_line_of_3(char s) {
    int dx[4] = { 1, 1, 0, 1 };
    int dy[4] = { 0, 1, 1, -1 };
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            if (board[x][y] != s) continue;
            for (int d = 0; d < 4; d++) {
                int count = 1;
                int nx = x + dx[d], ny = y + dy[d];
                while (nx >= 0 && nx < rows && ny >= 0 && ny < columns && board[nx][ny] == s) {
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
    int dx[4] = { 1, 1, 0, 1 };
    int dy[4] = { 0, 1, 1, -1 };
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < columns; y++) {
            if (board[x][y] != s) continue;
            for (int d = 0; d < 4; d++) {
                int count = 1;
                int nx = x + dx[d], ny = y + dy[d];
                while (nx >= 0 && nx < rows && ny >= 0 && ny < columns && board[nx][ny] == s) {
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

// Evaluate board for AI
int evaluate(Diamond_Board* board, char AI, char YOU) {
    int score = 0;

    
    if (board->has_line_of_3(AI) && board->has_line_of_4(AI))
        score += 1000;

    
    if (board->has_line_of_3(YOU) && board->has_line_of_4(YOU))
        score -= 1000;

   
    if (board->has_line_of_3(AI)) score += 10;
    if (board->has_line_of_4(AI)) score += 20;
    if (board->has_line_of_3(YOU)) score -= 10;
    if (board->has_line_of_4(YOU)) score -= 20;

    return score;
}
// Minimax with depth limit to reduce runtime
int minimax(Diamond_Board* board, char AI, char opponent, bool is_ai_turn, int depth, int max_depth) {
    int score = evaluate(board, AI, opponent);
    if (score == 1000 || score == -1000 || depth >= max_depth) return score;

    vector<pair<int, int>> moves;
    for (int i = 0; i < board->get_rows(); i++)
        for (int j = 0; j < board->get_columns(); j++)
            if (board->is_cell_empty(i, j) && board->inside_diamond(i, j))
                moves.push_back({ i,j });

    if (moves.empty()) return 0; // draw

    if (is_ai_turn) {
        int best = -10000;
        for (auto move : moves) {
            board->set_value(move.first, move.second, AI);
            best = max(best, minimax(board, AI, opponent, false, depth + 1, max_depth));
            board->set_value(move.first, move.second, '.');
        }
        return best;
    }
    else {
        int best = 10000;
        for (auto move : moves) {
            board->set_value(move.first, move.second, opponent);
            best = min(best, minimax(board, AI, opponent, true, depth + 1, max_depth));
            board->set_value(move.first, move.second, '.');
        }
        return best;
    }
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " enter row and column (0-4): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    cout << player->get_name() << " (Computer) is choosing a move...\n";
    Diamond_Board* dboard = dynamic_cast<Diamond_Board*>(player->get_board_ptr());
    char AI = player->get_symbol();
    char YOU = (AI == 'X') ? 'O' : 'X';

    vector<pair<int, int>> moves;
    for (int i = 0; i < dboard->get_rows(); i++)
        for (int j = 0; j < dboard->get_columns(); j++)
            if (dboard->is_cell_empty(i, j) && dboard->inside_diamond(i, j))
                moves.push_back({ i,j });

    int best_score = -10000, best_x = -1, best_y = -1;

    for (auto move : moves) {
        dboard->set_value(move.first, move.second, AI);
        int score = minimax(dboard, AI, YOU, false, 0, 3); // depth limit 3
        dboard->set_value(move.first, move.second, '.');

       
        cout << "Evaluating move at (" << move.first << "," << move.second
            << ") -> score = " << score << endl;

        if (score > best_score) {
            best_score = score;
            best_x = move.first;
            best_y = move.second;
        }
    }

    cout << "Computer played (" << best_x << "," << best_y << ")\n";
    return new Move<char>(best_x, best_y, AI);
}

