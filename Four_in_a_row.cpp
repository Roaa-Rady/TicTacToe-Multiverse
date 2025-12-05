#include "Games_Board.h"
#include "Games_UI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
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

// AI
int FourInARowBoard::evaluate_window(const std::vector<char>& window, char symbol) const {
    char opp = (symbol == 'X') ? 'O' : 'X';
    int score = 0;

    int my_count = 0, opp_count = 0, empty_count = 0;
    for (char c : window) {
        if (c == symbol) my_count++;
        else if (c == opp) opp_count++;
        else empty_count++;
    }

    if (my_count == 4) return 100000;    
    if (opp_count == 4) return -100000;   

    if (my_count == 3 && empty_count == 1) score += 1000;
    if (my_count == 2 && empty_count == 2) score += 100;

    if (opp_count == 3 && empty_count == 1) score -= 1000; 

    return score;
}

int FourInARowBoard::evaluate_board(char symbol) const {
    int score = 0;
    char opp = (symbol == 'X') ? 'O' : 'X';

    // Horizontal
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns - 3; c++) {
            std::vector<char> window = { board[r][c], board[r][c + 1], board[r][c + 2], board[r][c + 3] };
            score += evaluate_window(window, symbol);
        }
    }

    // Vertical
    for (int r = 0; r < rows - 3; r++) {
        for (int c = 0; c < columns; c++) {
            std::vector<char> window = { board[r][c], board[r + 1][c], board[r + 2][c], board[r + 3][c] };
            score += evaluate_window(window, symbol);
        }
    }

    // Diagonal
    for (int r = 0; r < rows - 3; r++) {
    for (int c = 0; c < columns - 3; c++) {
        std::vector<char> window = { board[r][c], board[r + 1][c + 1], board[r + 2][c + 2], board[r + 3][c + 3] };
        score += evaluate_window(window, symbol);
    }
}

return score;
}


int FourInARowBoard::minimax(int depth, bool isMaximizing, char aiSymbol, char humanSymbol, int alpha, int beta) {
    if (depth == 0 || game_is_over(nullptr)) {
        if (checkFour(aiSymbol)) return 1000000;
        if (checkFour(humanSymbol)) return -1000000;
        if (game_is_over(nullptr)) return 0;
        return evaluate_board(aiSymbol);
    }

    if (isMaximizing) {
        int maxEval = -10000000;
        for (int col = 0; col < 7; col++) {
            if (isColumnFull(col)) continue;

            int row = dropToBottom(col, aiSymbol);  
            int eval = minimax(depth - 1, false, aiSymbol, humanSymbol, alpha, beta);
            board[row][col] = '.'; 
            n_moves--;

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) break; 
        }
        return maxEval;
    }
    else {
        int minEval = 10000000;
        for (int col = 0; col < 7; col++) {
            if (isColumnFull(col)) continue;

            int row = dropToBottom(col, humanSymbol);
            int eval = minimax(depth - 1, true, aiSymbol, humanSymbol, alpha, beta);
            board[row][col] = '.';
            n_moves--;

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}


int FourInARowBoard::get_best_move(char aiSymbol, int maxDepth) {
    char humanSymbol = (aiSymbol == 'X') ? 'O' : 'X';
    int bestScore = -10000000;
    int bestCol = -1;

    for (int col = 0; col < 7; col++) {
        if (isColumnFull(col)) continue;

        int row = dropToBottom(col, aiSymbol);

        
        if (checkFour(aiSymbol)) {
            board[row][col] = '.';
            n_moves--;
            return col;
        }
        int score = minimax(maxDepth - 1, false, aiSymbol, humanSymbol, -10000000, 10000000);

        board[row][col] = '.'; // undo
        n_moves--;

        if (score > bestScore) {
            bestScore = score;
            bestCol = col;
        }
    }

    return bestCol >= 0 ? bestCol : 3; 
}




// FourInARowUI //
FourInARowUI::FourInARowUI() : UI<char>("Welcome to Four In A Row!", 4) {
    srand(time(0));
}

Player<char>* FourInARowUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);

Move<char>* FourInARowUI::get_move(Player<char>* player) {
    int col;
    FourInARowBoard* b = dynamic_cast<FourInARowBoard*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter column (0-6): ";
        while (!(cin >> col)  col < 0  col > 6 || b->isColumnFull(col)) {
            cout << "Invalid or full column! Try again: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    else {
        cout << player->get_name() << " (AI) is thinking";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        cout << "\n";

        int depth = (player->get_symbol() == 'X') ? 8 : 7; 
        col = b->get_best_move(player->get_symbol(), depth);

        cout << player->get_name() << " (AI) played column " << col << "\n";
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
