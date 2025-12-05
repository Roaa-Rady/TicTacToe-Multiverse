#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include"C:\Users\Roaa Rady\source\repos\Gamesss\Gamesss\Games_Board.h"
#include"C:\Users\Roaa Rady\source\repos\Gamesss\Gamesss\Games_UI.h"
using namespace std;


Word_TicTacToe_UI::Word_TicTacToe_UI()
    : UI<char>("", 5) {   
}

Player<char>* Word_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}



//updated function for AI
Move<char>* Word_TicTacToe_UI::get_move(Player<char>* player) {
    Word_TicTacToe_Board* real_board = static_cast<Word_TicTacToe_Board*>(player->get_board_ptr());
    vector<vector<char>> board = real_board->get_board_matrix();
    char me = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        int row, col;
        char letter;

        while (true) {
            cout << "\n" << player->get_name() << " (" << me << ") - Your turn\n";
            cout << "Enter position (row col): ";
            cin >> row >> col;

            if (row < 0 || row > 2 || col < 0 || col > 2) {
                cout << "Invalid position! Must be 0-2.\n";
                continue;
            }
            if (board[row][col] != ' ') {
                cout << "Cell already taken! Try again.\n";
                continue;
            }

            cout << "Enter your letter (A-Z): ";
            cin >> letter;
            letter = toupper(letter);

            if (letter < 'A' || letter > 'Z') {
                cout << "Please enter a valid letter (A-Z)!\n";
                continue;
            }
            return new Move<char>(row, col, letter);
        }
    }

    // ====================== AI player ======================
    cout << "\n" << player->get_name() << " (Smart AI) is thinking...\n";

    // searching for immediate winning
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] != ' ') continue;

            for (char c = 'A'; c <= 'Z'; ++c) {
                // create a temporary copy of the board
                Word_TicTacToe_Board temp_board = *real_board;
                Move<char> test_move(i, j, c);

                // try the move
                if (temp_board.update_board(&test_move)) {
                    if (temp_board.is_win(nullptr)) {
                        cout << "   AI found a winning move!\n";
                        cout << player->get_name() << " plays (" << i << "," << j << ") '" << c << "'\n";
                        return new Move<char>(i, j, c);
                    }
                }
            }
        }
    }

    // no immediate win ? play randomly but smart
    vector<pair<int, int>> empty;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ')
                empty.push_back({ i, j });

    int idx = rand() % empty.size();
    int r = empty[idx].first;
    int c = empty[idx].second;
    char let = 'A' + (rand() % 26);

    cout << "   AI played a strategic move.\n";
    cout << player->get_name() << " plays (" << r << "," << c << ") '" << let << "'\n";
    return new Move<char>(r, c, let);
}
//


void Word_TicTacToe_UI::show_result(const Word_TicTacToe_Board* board, Player<char>* winner) const {
    board->display();
    if (winner) {
        cout << "Winner: " << winner->get_name() << " formed a valid word!\n\n";
    }
    else {
        cout << "Draw! No valid word was formed.\n\n";
    }
}
