#include <cstdlib>
#include <ctime>
#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "XO_Classes.h"
#include"Games_Board.h"
#include "BoardGame_Classes.h"
#include "Games_UI.h"


using namespace std;


int main() {

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    int choice;
    cout << "Choose a game:\n";
    cout << "1. X-O Game\n";
    cout << "2. Numerical Tic-Tac-Toe\n";
    cout << "3. Misere Tic-Tac-Toe\n";
    cout << "4. Obstacles Tic-Tac-Toe\n";
    cout << "5. 5x5 Tic-Tac-Toe\n"; 
    cout << "6. 4x4 Tic_Tac-Toe\n";
    cout << "7. SUS Game\n";
    cout << "8. Four in a row Game\n";
    cout << "9. Infinity Tic-Tac-Toe\n";
    cout << "10. Word Tic-Tac-Toe\n"; 
    cout << "11. Pyramid Tic-Tac-Toe\n";
    cout << "12. Diamond Tic-Tac-Toe\n";
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
        //Numerical TicTacToe
    else if (choice == 2) {
    cout << "\n--- Starting Numerical Tic-Tac-Toe ---\n\n";
    UI<int>* ui = new Numerical_TicTacToe_UI();
    Board<int>* board = new Numerical_TicTacToe_Board();
    Player<int>** players = ui->setup_players();

    GameManager<int> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; ++i) delete players[i];
    delete[] players;
    delete ui;
    }
    //Misere Tic-tac-Toe//
  else if (choice == 3) {
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
else if (choice == 4) {
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
    //5x5 Tic-Tac-Toe
else if (choice == 5) {
    TicTacToe5x5_UI* ui = new TicTacToe5x5_UI();
    TicTacToe5x5_Board* board = new TicTacToe5x5_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

                  //3-in-row
    ui->display_final_result(board, players[0], players[1]);

    delete board;
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    delete ui;
}
    

    //4x4 TicTacToe 
    else if (choice == 6) {
        cout << "\n--- Starting 4x4 Tic-Tac-Toe ---\n\n";

        TicTacToe4x4_UI ui;
        Board<char>* board = new TicTacToe4x4_Board();
        Player<char>** players = ui.setup_players();

        GameManager<char> game(board, players, &ui);
        game.run();
        }


     //------------ SUS Game -------------//
 else if (choice == 7) {
      UI<char>* ui = new SUS_UI();
      Board<char>* board = new SUS_Board();
      Player<char>** players = ui->setup_players();

      GameManager<char> game(board, players, ui);
      game.run();

      delete board;
      for (int i = 0; i < 2; i++) delete players[i];
      delete[] players;
      delete ui;
    }

     //------------ FourInARow Game -------------//
else if (choice == 8) {
    UI<char>* ui = new FourInARowUI ();
    Board<char>* board = new FourInARowBoard();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    delete ui;
}

      //------------ InfinityTicTacToe -------------//
  else if (choice == 9) {
      UI<char>* ui = new InfinityTicTacToe_UI();
      Board<char>* board = new InfinityTicTacToe_Board ();
      Player<char>** players = ui->setup_players();

      GameManager<char> game(board, players, ui);
      game.run();

      delete board;
      for (int i = 0; i < 2; i++) delete players[i];
      delete[] players;
      delete ui;
  }

    // Word Tic-Tac-Toe
  else if (choice == 10) {
    Word_TicTacToe_UI* ui = new Word_TicTacToe_UI();
    Word_TicTacToe_Board* board = new Word_TicTacToe_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);

    
    board->display();
    game.run();

          //who is the winner?
    Player<char>* winner = nullptr;
    if (board->is_win(nullptr)) {
        winner = (board->get_moves_count() % 2 == 1) ? players[0] : players[1];
    }

    ui->show_result(board, winner);

         //cleaning
    delete board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
}
  else if (choice == 11) {
      cout << "\n--- Starting Pyramid Tic-Tac-Toe ---\n\n";

      Pyramid_TicTacToe_UI* ui = new Pyramid_TicTacToe_UI();
      Board<char>* board = new Pyramid_TicTacToe_Board();
      Player<char>** players = ui->setup_players();

      GameManager<char> game(board, players, ui);
      game.run();

      delete board;
      for (int i = 0; i < 2; ++i) delete players[i];
      delete[] players;
      delete ui;
      }
       else if (choice == 12) {
    UI<char>* ui = new Diamond_UI();
    Board<char>* board = new Diamond_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++) delete players[i];
    delete[] players;
    delete ui;
}


    
    else {
            cout << "Invalid choice! Exiting...\n";
            }

            cout << "\nThank you for playing!\n";
            return 0;
}

