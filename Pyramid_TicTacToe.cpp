#include "Pyramid_TicTacToe_Board.h"
#include "Pyramid_TicTacToe_UI.h"
#include <iostream>
#include <cstdlib>  
#include <ctime>   
using namespace std;

//Board
Pyramid_TicTacToe_Board::Pyramid_TicTacToe_Board()
    : Board<char>(3, 5)
{
    board = {
    {' ', ' ', '.', ' ', ' '},   
    {' ', '.', '.', '.', ' '},   
    {'.', '.', '.', '.', '.'}    
            };
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


//UI
Pyramid_TicTacToe_UI::Pyramid_TicTacToe_UI()
    : UI<char>("Welcome to Pyramid TicTacToe!", 2) {}


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

    // Computer
    else {
        cout << player->get_name() << " (Computer) is thinking";
        vector<pair<int, int>> empty_cells;

        for (int i = 0; i < (int)matrix.size(); ++i)
            for (int j = 0; j < (int)matrix[i].size(); ++j)
                if (matrix[i][j] == '.')
                    empty_cells.emplace_back(i, j);

        if (empty_cells.empty()) return nullptr;

        int idx = rand() % empty_cells.size();
        r = empty_cells[idx].first;
        c = empty_cells[idx].second;

        cout << " -> (" << r << "," << c << ")\n";
        return new Move<char>(r, c, player->get_symbol());
    }
}


Player<char>* Pyramid_TicTacToe_UI::create_player(
    string& name, char symbol, PlayerType type)
{
    return new Player<char>(name, symbol, type);
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
    cout << "  |  " << m[2][0] << "  |  " << m[2][1] << "  |  " << m[2][2]
        << "  |  " << m[2][3] << "  |  " << m[2][4] << "  |\n";
    cout << "  -------------------------------\n\n";
}