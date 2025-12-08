#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>

using namespace std;

//Board implementation
Pyramid_TicTacToe_Board::Pyramid_TicTacToe_Board()
    : Board<char>(3, 5)
{
    board = {
    {' ', ' ', '.', ' ', ' '},   
    {' ', '.', '.', '.', ' '},   
    {'.', '.', '.', '.', '.'}  };
}
bool Pyramid_TicTacToe_Board::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (r < 0 || r >= rows || c < 0 || c >= columns)
        return false;

    if (board[r][c] == ' ')   // invalid
        return false;

    if (board[r][c] != '.')   // not empty
        return false;

    board[r][c] = s;
    n_moves++;
    return true;
}
bool Pyramid_TicTacToe_Board::is_win(Player<char>* player) {
    char s = player->get_symbol();

    vector<vector<pair<int, int>>> lines = {
        // Vertical middle line
        {{0,2}, {1,2}, {2,2}},

        // Horizontal lines
        {{1,1}, {1,2}, {1,3}},
        {{2,0}, {2,1}, {2,2}},
        {{2,1}, {2,2}, {2,3}},
        {{2,2}, {2,3}, {2,4}},

        // Diagonal lines
        {{0,2}, {1,1}, {2,0}}, // left diagonal
        {{0,2}, {1,3}, {2,4}}  // right diagonal
    };

    for (auto& L : lines) {
        if (board[L[0].first][L[0].second] == s &&
            board[L[1].first][L[1].second] == s &&
            board[L[2].first][L[2].second] == s)
            return true;
    }
    return false;
}
bool Pyramid_TicTacToe_Board::is_lose(Player<char>* p) {
    char s = p->get_symbol();
    char opp = (s == 'X' ? 'O' : 'X');
    Player<char> o("opp", opp, PlayerType::HUMAN);
    return is_win(&o);
}
bool Pyramid_TicTacToe_Board::is_draw(Player<char>* p) {
    if (is_win(p) || is_lose(p))
        return false;

    for (auto& row : board)
        for (char c : row)
            if (c == ' ')
                return false;

    return true;
}

bool Pyramid_TicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

//AI  algorithm
int evaluate(Pyramid_TicTacToe_Board* board, char aiSymbol) {
    Player<char> ai("AI", aiSymbol, PlayerType::COMPUTER);
    ai.set_board_ptr(board);

    if (board->is_win(&ai)) return 1000;

    char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';
    Player<char> human("Human", humanSymbol, PlayerType::HUMAN);
    human.set_board_ptr(board);

    if (board->is_win(&human)) return -1000;

    return 0; 
}

int minimax(Pyramid_TicTacToe_Board* board, char aiSymbol, bool isMax) {
    int score = evaluate(board, aiSymbol);
    if (score == 1000 || score == -1000) return score;

    vector<pair<int, int>> empty;
    auto matrix = board->get_board_matrix();
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix[i].size(); j++)
            if (matrix[i][j] == '.') empty.push_back({ i,j });

    if (empty.empty()) return 0; 

    if (isMax) {
        int best = -10000;
        for (auto [r, c] : empty) {
            board->set_value(r, c, aiSymbol);
            best = max(best, minimax(board, aiSymbol, false));
            board->set_value(r, c, '.'); 
        }
        return best;
    }
    else {
        int best = 10000;
        char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';
        for (auto [r, c] : empty) {
            board->set_value(r, c, humanSymbol);
            best = min(best, minimax(board, aiSymbol, true));
            board->set_value(r, c, '.'); 
        }
        return best;
    }
}

pair<int, int> findBestMove(Pyramid_TicTacToe_Board* board, char aiSymbol) {
    int bestVal = -10000;
    pair<int, int> bestMove = { -1,-1 };

    auto matrix = board->get_board_matrix();
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == '.') {
                board->set_value(i, j, aiSymbol);
                int moveVal = minimax(board, aiSymbol, false);
                board->set_value(i, j, '.');
                if (moveVal > bestVal) {
                    bestMove = { i,j };
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}


//UI implementation
Pyramid_TicTacToe_UI::Pyramid_TicTacToe_UI()
    : UI<char>("Welcome to Pyramid TicTacToe!", 2) {}


Player<char>* Pyramid_TicTacToe_UI::create_player(
    string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
}



Move<char>* Pyramid_TicTacToe_UI::get_move(Player<char>* player) {
    
    Board<char>* board = player->get_board_ptr();
    int r, c;
    auto matrix = board->get_board_matrix();
    // Human
    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            cout << player->get_name() << " (" << player->get_symbol()<< ") enter row and column: ";
            cin >> r >> c;

            if (r < 0 || r >= board->get_rows() || c < 0 || c >= board->get_columns()) {
                cout << "Out of bounds. Choose a valid cell.\n";
                continue;
            }
            if (board->get_value(r, c) != '.') {
                cout << "Cell not available. Choose an empty cell.\n";
                continue;
            }
            return new Move<char>(r, c, player->get_symbol());
        }
    }
    // AI
    else {
        cout << player->get_name() << " AI is thinking";
       auto [r, c] = findBestMove(dynamic_cast<Pyramid_TicTacToe_Board*>(board), player->get_symbol());
cout << " -> (" << r << "," << c << ")\n";
return new Move<char>(r, c, player->get_symbol());
    }
}

void Pyramid_TicTacToe_UI::display_board_matrix(
    const vector<vector<char>>& m) const
{
    cout << "\n";
  //Row1
    cout << "         -------------\n";
    cout << "         |     " << m[0][2] << "     |\n";
    cout << "         -------------\n";
  // Row2
    cout << "      -------------------\n";
    cout << "      |  " << m[1][1] << "  |  " << m[1][2] << "  |  " << m[1][3] << "  |\n";
    cout << "      -------------------\n";
  // Row3
    cout << "  -------------------------------\n";
    cout << "  |  " << m[2][0] << "  |  " << m[2][1] << "  |  " << m[2][2] << "  |  " << m[2][3] << "  |  " << m[2][4] << "  |\n";
    cout << "  -------------------------------\n\n";
}
