#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>

using namespace std;

//Board
TicTacToe4x4_Board::TicTacToe4x4_Board() : Board<char>(4, 4) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = '.';
}

bool TicTacToe4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
   char symbol = move->get_symbol(); 

    if (x < 0 || x >= 4 || y < 0 || y >= 4) {
        cout << "Invalid position!\n";
        return false;
    }

    if (this->get_value(x, y) != '.') {
        cout << "This cell is already taken!\n";
        return false;
    }

    set_value(x, y, symbol);
    n_moves++;
    return true;
}
    

  //UI
bool TicTacToe4x4_Board::is_win(Player<char>* player) {
    int s = player->get_symbol();
    //check rows
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c <=1; c++) {
            if (board[r][c] == s &&
                board[r][c + 1] == s &&
                board[r][c + 2] == s)
                return true;
        }
    }
    //check columns
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r <= 1; r++) {
            if (board[r][c] == s &&
                board[r + 1][c] == s &&
                board[r + 2][c] == s)
                return true;
        }
    }
      // check diagonals from top left to bottom right
  for (int r = 0; r <= 1; ++r) {
    for (int c = 0; c <= 1; ++c) {
        if (board[r][c] == s &&
            board[r + 1][c + 1] == s &&
            board[r + 2][c + 2] == s)
            return true;
    }
}

    //check diagonals from top right to bottom left
for (int r = 0; r <= 1; ++r) {
    for (int c = 0; c <= 1; ++c) {
        if (board[r][c + 2] == s &&
            board[r + 1][c + 1] == s &&
            board[r + 2][c] == s)
            return true;
    }
}

    return false;

}
bool TicTacToe4x4_Board::is_lose(Player<char>* player)
{
    char other = (player->get_symbol() == 'X' ? 'O' : 'X');
    Player<char> temp("temp", other, PlayerType::HUMAN);
    return is_win(&temp);
}
bool TicTacToe4x4_Board::is_draw(Player<char>* player)
{
    return n_moves == 16 && !is_win(player);
}
bool TicTacToe4x4_Board::game_is_over(Player<char>* player)
{
    return is_win(player) || is_lose(player) || is_draw(player);
}

TicTacToe4x4_UI::TicTacToe4x4_UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe!", 3) {}

Player<char>* TicTacToe4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating player: " << name << endl;
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe4x4_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* board = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
    else {
        cout << player->get_name() << " (Computer) is thinking";

        while (true) {
            cout << ".";

            x = rand() % 4;
            y = rand() % 4;


            if (board->get_value(x, y) == '.') {

                cout << " -> (" << x << "," << y
                    << ") with " << player->get_symbol() << endl;

                return new Move<char>(x, y, player->get_symbol());
            }
        }
    }
}
