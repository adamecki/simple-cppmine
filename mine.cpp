// Simple console Minesweeper game

// So far I didn't implement a functionality which
// automatically uncovers nearly fields if they
// are empty, but I'll try to implement it later

// I am thinking about porting it to (Free)DOS but
// I'm not very confident so far with old C++ which
// (Free)DOS is compatible with (Watcom C++ 11.0 etc.)

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Variables specific for a field in the board

class Field {
    public:
        bool has_bomb = false;
        bool is_uncovered = false;
        int bombs_near = 0;
};

bool gameplay = true; // Will be switched to false if player steps on a mine, which will end a game (end process)

const int board_x = 8;
const int board_y = 8;

const int bombs_to_place = 10;
int bombs_placed = 0;

int uncovered_fields = 0;

Field board[board_y][board_x]; // Arrays like that always come with y first

void prepare_board() {
    cout << "Placing mines..." << endl;
    cout << bombs_to_place - bombs_placed << " mines left to place" << endl;

    while(bombs_placed < bombs_to_place) {
        srand(time(0) - rand()); // Set seed for the pseudorandom number generator
        int rx = rand() % 8;

        srand(time(0) + rand());
        int ry = rand() % 8;

        if(!board[ry][rx].has_bomb) {   // In order to prevent mine overriding, not the best solution but works
            board[ry][rx].has_bomb = true;
            bombs_placed++;

            cout << bombs_to_place - bombs_placed << " mines left to place" << endl;
        }

    }

    cout << "Mines placed" << endl << endl;

    cout << "Setting up information about nearest mines" << endl;

    for(int x = 0; x < board_x; x++) {
        for(int y = 0; y < board_y; y++) {
            for(int nx = -1; nx <= 1; nx++) {
                for(int ny = -1; ny <=1; ny++) {
                    if(x + nx >= 0 && x + nx <= 7 && y + ny >= 0 && y + ny <= 7) {  // Skip incorrect values
                        if(board[y + ny][x + nx].has_bomb) {
                            board[y][x].bombs_near++;
                        }
                    }
                }
            }
        }
    }

    cout << "Mines information has been set up - Starting game" << endl << endl;
}

void draw_board(string with_bombs = "") {
    cout << "   a   b   c   d   e   f   g   h" << endl;

    for(int x = 0; x < board_x; x++) {
        cout << x + 1 << " ";
        for(int y = 0; y < board_y; y++) {
            if(board[y][x].has_bomb && with_bombs == "WITH_BOMBS") {    // I could also add a bool but I wanted to make the code more readable
                cout << "[*] ";
            } else if(board[y][x].is_uncovered) {
                cout << "[" << board[y][x].bombs_near << "] ";
            } else {
                cout << "[ ] ";
            }
        }
        cout << endl << endl;
    } 
}

void game_over() {
    cout << "Game Over!" << endl << endl;

    draw_board("WITH_BOMBS");

    cout << endl << "You have uncovered " << uncovered_fields << " fields." << endl;
    gameplay = false;
}

void win() {
    cout << "Win!" << endl << endl;

    draw_board("WITH_BOMBS");

    cout << endl << "You have uncovered all fields without stepping on a mine!" << endl;
    gameplay = false;
}

void uncover_field(int x, int y) {
    if(board[y][x].has_bomb) {
        game_over();
    } else {
        if(!board[y][x].is_uncovered) {
            board[y][x].is_uncovered = true;
            uncovered_fields++;

            if(board[y][x].bombs_near == 0) {
                for(int nx = -1; nx <= 1; nx++) {
                    for(int ny = -1; ny <=1; ny++) {
                        if(x + nx >= 0 && x + nx <= 7 && y + ny >= 0 && y + ny <= 7) {  // Skip incorrect values
                            uncover_field(x + nx, y + ny);
                        }
                    }
                }

            }
        }
    }
}

int main() {
    prepare_board();
    cout << "Simple Minesweeper Game" << endl << endl;
    
    while(gameplay) {
        draw_board();

        char cx = '-';
        int x = -1;
        int y = -1;

        string choice;
        while(true) {
            cout << "Choose a field to uncover (e.g. a1): ";
            getline(cin, choice);
            if(isdigit(choice[1])) {
                cx = choice[1];
                y = cx - '0';
                y--;
                
                cx = choice[0];
                cx = tolower(cx);

                switch(cx) {    // Also not the best solution (will not work with bigger boards),
                                // but I didn't want user to input some Frankensteinish value like e.g. xy = '45'
                    case 'a':
                        x = 0;
                        break;
                    case 'b':
                        x = 1;
                        break;
                    case 'c':
                        x = 2;
                        break;
                    case 'd':
                        x = 3;
                        break;
                    case 'e':
                        x = 4;
                        break;
                    case 'f':
                        x = 5;
                        break;
                    case 'g':
                        x = 6;
                        break;
                    case 'h':
                        x = 7;
                        break;

                    default:
                        x = -1;
                        break;
                }

                if (0 <= x && x <= 7 && 0 <= y && y <= 7) {
                    break;
                }
            }
            cout << "Incorrect choice. Please try again." << endl;
        }
        cout << endl;

        uncover_field(y, x);

        if(uncovered_fields == (board_y * board_x) - bombs_placed) {
            win();
        }
    }

    return 0; 
}

