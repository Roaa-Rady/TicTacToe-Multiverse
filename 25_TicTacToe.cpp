#include"games_Board.h"
#include"games_UI.h"

// ------------------- Board Implementation -------------------
TicTacToe5x5_Board::TicTacToe5x5_Board() : Board<char>(5, 5), blank_symbol('.') {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool TicTacToe5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= 5 || y < 0 || y >= 5) {
        cout << "Invalid position! Row and column must be 0-4.\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Cell already taken!\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;
    return true;
}

int TicTacToe5x5_Board::count_3_in_row(char sym) {
    int count = 0;

    // Rows
    for (int i = 0; i < 5; i++)
        for (int j = 0; j <= 2; j++)
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                count++;

    // Columns
    for (int j = 0; j < 5; j++)
        for (int i = 0; i <= 2; i++)
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                count++;

    // Diagonals
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                count++;
            if (board[i + 2][j] == sym && board[i + 1][j + 1] == sym && board[i][j + 2] == sym)
                count++;
        }

    return count;
}

bool TicTacToe5x5_Board::is_win(Player<char>*) { return false; }
bool TicTacToe5x5_Board::is_lose(Player<char>*) { return false; }
bool TicTacToe5x5_Board::is_draw(Player<char>*) { return n_moves >= 25; }
bool TicTacToe5x5_Board::game_is_over(Player<char>*) { return n_moves >= 25; }

// ------------------- UI Implementation -------------------
TicTacToe5x5_UI::TicTacToe5x5_UI() : UI<char>("Welcome to 5x5 Tic Tac Toe!", 2) {}

Player<char>* TicTacToe5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe5x5_UI::get_move(Player<char>* player) {
    int x, y;
    Board<char>* b = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " enter x y (0-4): ";
        cin >> x >> y;
    }
    else {
        do {
            x = rand() % 5;
            y = rand() % 5;
        } while (b->get_board_matrix()[x][y] != '.');

        cout << player->get_name() << " (Computer) played (" << x << "," << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

void TicTacToe5x5_UI::display_final_result(TicTacToe5x5_Board* board, Player<char>* p1, Player<char>* p2) {
    int p1_count = board->count_3_in_row(p1->get_symbol());
    int p2_count = board->count_3_in_row(p2->get_symbol());

    cout << "\nGame Over!\n";
    cout << p1->get_name() << " has " << p1_count << " sets of 3-in-row.\n";
    cout << p2->get_name() << " has " << p2_count << " sets of 3-in-row.\n";

    if (p1_count > p2_count) cout << p1->get_name() << " wins!\n";
    else if (p2_count > p1_count) cout << p2->get_name() << " wins!\n";
    else cout << "It's a tie!\n";
}
