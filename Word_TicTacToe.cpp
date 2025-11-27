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
#include"C:\Users\Roaa Rady\source\repos\Gamesss\Gamesss\Games _Board.h"
#include"C:\Users\Roaa Rady\source\repos\Gamesss\Gamesss\Games_UI.h"
using namespace std;


Word_TicTacToe_UI::Word_TicTacToe_UI()
    : UI<char>("", 5) {   
}

Player<char>* Word_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Word_TicTacToe_UI::get_move(Player<char>* player) {
    //if the player was human
    if (player->get_type() == PlayerType::HUMAN) {
        int row, col;
        char letter;

        Word_TicTacToe_Board* board = static_cast<Word_TicTacToe_Board*>(player->get_board_ptr());

        while (true) {
            cout << "\n" << player->get_name() << " (" << player->get_symbol() << ") - Your turn\n";
            cout << "Enter position : ";
            cin >> row >> col;

            //check the range
            if (row < 0 || row > 2 || col < 0 || col > 2) {
                cout << "Invalid position! Must be 0-2.\n";
                continue;
            }

            //check that the cell is not alresdy taken
            if (board->get_board_matrix()[row][col] != ' ') {
                cout << "Cell already taken! Try again:\n";
                continue;
            }

            
            cout << "Enter your letter : ";
            cin >> letter;
            letter = toupper(letter);

           //check if the input is a letter or not
            if (letter < 'A' || letter > 'Z') {
                cout << "Please enter a valid letter (A-Z)!\n";
                continue;
            }

           
            return new Move<char>(row, col, letter);
        }
    }
    // if the player was computer
    else {
       
        Word_TicTacToe_Board* b = static_cast<Word_TicTacToe_Board*>(player->get_board_ptr());

        vector<pair<int, int>> empty_cells;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                
                if (b->get_board_matrix()[i][j] == ' ') {
                    empty_cells.emplace_back(i, j);
                }
            }
        }

        
        if (empty_cells.empty()) {
            return new Move<char>(0, 0, player->get_symbol());
        }

        
        size_t idx = rand() % empty_cells.size();
        int r = empty_cells[idx].first;
        int c = empty_cells[idx].second;
        char let = 'A' + (rand() % 26);

        cout << "\n" << player->get_name() << " (Computer) plays → ("
            << r << ", " << c << ") '" << let << "'" << endl;

        return new Move<char>(r, c, let);
    }
}

void Word_TicTacToe_UI::show_result(const Word_TicTacToe_Board* board, Player<char>* winner) const {
    board->display();
    if (winner) {
        cout << "Winner: " << winner->get_name() << " formed a valid word!\n\n";
    }
    else {
        cout << "Draw! No valid word was formed.\n\n";
    }
}
