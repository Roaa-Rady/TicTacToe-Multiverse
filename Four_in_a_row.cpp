#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//  FourInARowBoard //
FourInARowBoard::FourInARowBoard() : Board<char>(6, 7) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            board[i][j] = '.';
}

bool FourInARowBoard::isColumnFull(int col) const {
    return board[0][col] != '.';
}

int FourInARowBoard::dropToBottom(int col, char symbol) {
    for (int r = 5; r >= 0; r--) {      
        if (board[r][col] == '.') {
            board[r][col] = symbol;
            return r;
        }
    }
    return -1;
}

bool FourInARowBoard::checkFour(char symbol) const {
    // Horizontal
    for (int r = 0; r < 6; r++)
        for (int c = 0; c < 4; c++)
            if (board[r][c] == symbol && board[r][c + 1] == symbol &&
                board[r][c + 2] == symbol && board[r][c + 3] == symbol)
                return true;

    // Vertical
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 7; c++)
            if (board[r][c] == symbol && board[r + 1][c] == symbol &&
                board[r + 2][c] == symbol && board[r + 3][c] == symbol)
                return true;

    // Diagonal //
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 4; c++)
            if (board[r][c] == symbol && board[r + 1][c + 1] == symbol &&
                board[r + 2][c + 2] == symbol && board[r + 3][c + 3] == symbol)
                return true;

    // Diagonal /
    for (int r = 0; r < 3; r++)
        for (int c = 3; c < 7; c++)
            if (board[r][c] == symbol && board[r + 1][c - 1] == symbol &&
                board[r + 2][c - 2] == symbol && board[r + 3][c - 3] == symbol)
                return true;

    return false;
}

bool FourInARowBoard::update_board(Move<char>* move) {
    int col = move->get_y();
    char sym = move->get_symbol();

    if (col < 0 || col >= 7 || isColumnFull(col)) 
        return false;

    dropToBottom(col, sym);
    n_moves++;
    return true;
}

bool FourInARowBoard::is_win(Player<char>* player) {
    return checkFour(player->get_symbol());
}

bool FourInARowBoard::is_lose(Player<char>* player) {
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    return checkFour(opp);
}

bool FourInARowBoard::is_draw(Player<char>* player) {
    return game_is_over(player) && !checkFour('X') && !checkFour('O');
}

bool FourInARowBoard::game_is_over(Player<char>* player) {
    if (checkFour('X') || checkFour('O')) return true;
    for (int c = 0; c < 7; c++)
        if (!isColumnFull(c)) return false;
    return true;
}

// FourInARowUI //
FourInARowUI::FourInARowUI() : UI<char>("Welcome to Four In A Row!", 4) {
    srand(time(0));
}

Player<char>* FourInARowUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* FourInARowUI::get_move(Player<char>* player) {
    int col;
    Board<char>* b = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter column (0-6): ";
        cin >> col;
    }
    else {
        do {
            col = rand() % 7;
        } while (b->get_board_matrix()[5][col] != '.');
        cout << player->get_name() << " (Computer) played column " << col << "\n";
    }

    return new Move<char>(0, col, player->get_symbol());
}

void FourInARowUI::display_final_result(Player<char>* p1, Player<char>* p2) {
    system("cls");
    Board<char>* b = p1->get_board_ptr();


    cout << "\n   0 1 2 3 4 5 6\n";
    for (int r = 5; r >= 0; r--) {
        cout << r << " ";
        for (int c = 0; c < 7; c++) {
            cout << b->get_board_matrix()[r][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    if (((FourInARowBoard*)b)->is_win(p1))
        cout << "=== " << p1->get_name() << " (" << p1->get_symbol() << ") WINS! ===\n\n";
    else if (((FourInARowBoard*)b)->is_win(p2))
        cout << "=== " << p2->get_name() << " (" << p2->get_symbol() << ") WINS! ===\n\n";
    else
        cout << "=== IT'S A DRAW! ===\n\n";
}

Player<char>** FourInARowUI::setup_players() { 
    Player<char>** players = new Player<char>*[2];
    string name;
    int choice;

    cout << "Enter Player X name: ";
    cin >> name;
    cout << "Player X (1-Human, 2-Computer): ";
    cin >> choice;
    players[0] = create_player(name, 'X', (choice == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));

    cout << "Enter Player O name: ";
    cin >> name;
    cout << "Player O (1-Human, 2-Computer): ";
    cin >> choice;
    players[1] = create_player(name, 'O', (choice == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN));

    return players;
}
