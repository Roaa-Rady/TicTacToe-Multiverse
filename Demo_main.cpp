

#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include"C:\Users\dell\source\repos\Asss3.opp\Asss3\Misere_TicTacToe_Board.h"
#include"C:\Users\dell\source\repos\Asss3.opp\Asss3\Misere_TicTacToe_UI.h"
#include"C:\Users\dell\source\repos\Asss3.opp\Asss3\Obstacles_TicTacToe_Board.h"
#include"C:\Users\dell\source\repos\Asss3.opp\Asss3\Obstacles_TicTacToe_UI.h"

using namespace std;


int main() {

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    int choice;
    cout << "Choose a game:\n";
    cout << "1. X-O Game\n";
    cout << "3. Misere Tic-Tac-Toe";
    cout << "4. Obstacles Tic-Tac-Toe\n";
    cout << "Enter your choice: \n";
    cin >> choice;
    cin.ignore(); // علشان يتجاهل الـnewline

    if (choice == 1) {
        // ---------- X-O Game ----------
        UI<char>* game_ui = new XO_UI();
        Board<char>* board = new X_O_Board();
        Player<char>** players = game_ui->setup_players();

        GameManager<char> game(board, players, game_ui);
        game.run();

        delete board;
        for (int i = 0; i < 2; ++i) delete players[i];
        delete[] players;
        delete game_ui;
    }
    //Misere Tic-tac-Toe//
if (choice == 3) {
    UI<char>* ui = new Misere_TicTacToe_UI();
    Board<char>* board = new Misere_TicTacToe_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    delete ui;
}
//Obstacles Tic-tac-Toe//
if (choice == 4) {
    UI<char>* ui = new Obstacles_TicTacToe_UI();
    Board<char>* board = new Obstacles_TicTacToe_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    delete ui;
}
     else {
         cout << "Invalid choice. Exiting...\n";
     }
    return 0;
}

