#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
using namespace std;

// SUS_Board Implementation //

SUS_Board::SUS_Board() : Board<char>(3, 3) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = '.';
        }
    }
}

int playerS_score = 0;
int playerU_score = 0;

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == '.') {
        board[x][y] = sym;
        n_moves++;

        int points = 0;

    
        if (board[x][0] == 'S' && board[x][1] == 'U' && board[x][2] == 'S')
            points++;

       
        if (board[0][y] == 'S' && board[1][y] == 'U' && board[2][y] == 'S')
            points++;

        
        if (x == y) {
            if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S')
                points++;
        }

       
        if (x + y == 2) {
            if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S')
                points++;
        }

      
        if (sym == 'S') {
            playerS_score += points;
        }
        else {
            playerU_score += points;
        }

        return true;
    }
    return false;
}


int SUS_Board::count_SUS_sequences(char symbol) {
    int count = 0;

   
    for (int i = 0; i < 3; i++)
        if (board[i][0] == 'S' && board[i][1] == 'U' && board[i][2] == 'S')
            count++;

    
    for (int j = 0; j < 3; j++)
        if (board[0][j] == 'S' && board[1][j] == 'U' && board[2][j] == 'S')
            count++;

    
    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S')
        count++;

    
    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S')
        count++;

    return count;
}


bool SUS_Board::is_win(Player<char>* player) {
    if (!game_is_over(player)) return false;

    char sym = player->get_symbol();

    if (sym == 'S') {
        return playerS_score > playerU_score;
    }
    else {
        return playerU_score > playerS_score;
    }
}


bool SUS_Board::is_lose(Player<char>* player) {
    if (!game_is_over(player)) return false;

    char sym = player->get_symbol();

    if (sym == 'S') {
        return playerS_score < playerU_score;
    }
    else {
        return playerU_score < playerS_score;
    }
}

bool SUS_Board::is_draw(Player<char>* player) {
    if (!game_is_over(player)) return false;
    return playerS_score == playerU_score;
}


bool SUS_Board::game_is_over(Player<char>* player) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (board[i][j] == '.')
                return false;
    return true;
}


void SUS_Board::display_scores() {
    cout << "Player S score: " << playerS_score << endl;
    cout << "Player U score: " << playerU_score << endl;
}



// SUS_UI Implementation //

SUS_UI::SUS_UI() : UI<char>("Welcome to SUS Game!", 3) {}


Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}


Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter x y (0-2): ";
        cin >> x >> y;
    }
    else {
        Board<char>* board = player->get_board_ptr();
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_board_matrix()[x][y] != '.');

        cout << player->get_name() << " (Computer) played (" << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}


Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    string name;
    int choice;
    PlayerType type;

    // Player S
    cout << "Enter Player S name: ";
    cin >> name;

    cout << "Choose Player S type (1-Human, 2-Computer): ";
    cin >> choice;
    type = (choice == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN);

    players[0] = create_player(name, 'S', type);

    // Player U
    cout << "Enter Player U name: ";
    cin >> name;

    cout << "Choose Player U type (1-Human, 2-Computer): ";
    cin >> choice;
    type = (choice == 2 ? PlayerType::COMPUTER : PlayerType::HUMAN);

    players[1] = create_player(name, 'U', type);

    return players;
}
