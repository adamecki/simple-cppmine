// Simple console Minesweeper game

// C++ file made for DOS systems
// should be compiled with Watcom C++ 11.0

#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

class Field {
        public:
                bool has_bomb;
                bool is_uncovered;
                int bombs_near;
};

bool gameplay = true; // Switching to false will end process
                      // Check out Windows/Linux C++ file for full comments

const int board_x = 8;
const int board_y = 8;

const int bombs_to_place = 10;
int bombs_placed = 0;

int uncovered_fields = 0;

Field board[board_y][board_x]; // Y first

void prepare_board() {
        // Watcom C++ 11.0 doesn't support
        // declaring default value in class constructor :(

        for(int x1 = 0; x1 < board_x; x1++) {
                for(int y1 = 0; y1 < board_y; y1++) {
                        board[y1][x1].has_bomb = false;
                        board[y1][x1].is_uncovered = false;
                        board[y1][x1].bombs_near = 0;
                }
        }

        while(bombs_placed < bombs_to_place) {
                srand(time(0) - rand()); // Seed for pseudorandom
                                         // number generator
                int rx = rand() % 8;

                srand(time(0) + rand());
                int ry = rand() % 8;
        
                if(!board[ry][rx].has_bomb) {
                        board[ry][rx].has_bomb = true;
                        bombs_placed++;                       
                }
        }

        for(int x2 = 0; x2 < board_x; x2++) {
                for(int y2 = 0; y2 < board_y; y2++) {
                        for(int nx = -1; nx <= 1; nx++) {
                                for(int ny = -1; ny <= 1; ny++) {
                                        if((x2 + nx >= 0) && (x2 + nx <= 7) && (y2 + ny >= 0) && (y2 + ny <= 7)) {
                                                if(board[y2 + ny][x2 + nx].has_bomb) {
                                                        board[y2][x2].bombs_near++;
                                                }
                                        }
                                }
                        }
                }
        }        
}

void draw_board(bool with_bombs) {
        cout << "   a   b   c   d   e   f   g   h" << endl;
        
        for(int x = 0; x < board_x; x++) {
                cout << x + 1 << " ";
                for(int y = 0; y < board_y; y++) {
                        if(board[y][x].has_bomb && with_bombs == true) {
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

        draw_board(true);

        cout << "You have uncovered " << uncovered_fields << " fields." << endl;
        gameplay = false;
}

void win() {
        cout << "Win!" << endl << endl;
        
        draw_board(true);

        cout << "You have uncovered all fields without stepping on a mine!" << endl;
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
                                        for(int ny = -1; ny <= 1; ny++) {
                                                if((x + nx >= 0) && (x + nx <= 7) && (y + ny >= 0) && (y + ny <= 7)) {
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
                draw_board(false);
                
                char cx = '-';
                int x = -1;
                int y = -1;

                char *choice;
                while(true) {
                        cout << "Choose a field to uncover (e.g. a1): ";
                        cin >> choice;
                       
                        cx = choice[1];
                        y = cx - '0';
                        y--;

                        cx = choice[0];
                        
                        // There is no tolower() function in Watcom C++ 11.0
                        // So this part must be a little bit "hard coded"

                        switch(cx) {
                                case 'a':
                                        x = 0;
                                        break;
                                case 'A':
                                        x = 0;
                                        break;
                                case 'b':
                                        x = 1;
                                        break;
                                case 'B':
                                        x = 1;
                                        break;
                                case 'c':
                                        x = 2;
                                        break;
                                case 'C':
                                        x = 2;
                                        break;
                                case 'd':
                                        x = 3;
                                        break;
                                case 'D':
                                        x = 3;
                                        break;
                                case 'e':
                                        x = 4;
                                        break;
                                case 'E':
                                        x = 4;
                                        break;
                                case 'f':
                                        x = 5;
                                        break;
                                case 'F':
                                        x = 5;
                                        break;
                                case 'g':
                                        x = 6;
                                        break;
                                case 'G':
                                        x = 6;
                                        break;
                                case 'h':
                                        x = 7;
                                        break;
                                case 'H':
                                        x = 7;
                                        break;

                                default:
                                        x = -1;
                                        break;
                        }

                        if(0 <= x && x <= 7 && 0 <= y && y <= 7) {
                                break;
                        }
        
                        cout << "Incorrect choice. Please try again." << endl;
                }
                      
                cout << endl;
        
                uncover_field(y, x);

                if(uncovered_fields == (board_y * board_x) - bombs_placed) {
                        win();
                }        
        }

        cout << endl;
        return 0;
}


