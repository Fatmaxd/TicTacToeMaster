#ifndef _wordTTT_H
#define _wordTTT_H

#include "BoardGames_Classes.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <unordered_set>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "colors.h"

using namespace std;

// Declare global variables as extern
extern bool is_file_open;
extern bool is_computer;

// Function declaration only
unordered_set<string> loud_file_in_set();


template <typename T>
class wordTTT_Board : public Board<T> {
public:
    wordTTT_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class wordTTT_Player : public Player<T> {
public:
    wordTTT_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class wordTTT_Random_Player : public RandomPlayer<T> {
public:
    wordTTT_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// Constructor for wordTTT_Board
template <typename T>
wordTTT_Board<T>::wordTTT_Board() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool wordTTT_Board<T>::update_board(int x, int y, T mark) {
    if (mark == 0 && this->board[x][y] != ' ') {
        this->n_moves--;
        return false;
    }
    if (this->board[x][y] != ' ') {
        if (is_computer) return false;
        cout << RED << "Invalid move. Cell already used" << RESET << endl;
        return false;
    }
    if (is_computer) cout << CYAN << "\nRandom computer: " << RESET << (x + 1) << " " << (y + 1) << endl;
    this->n_moves++;
    this->board[x][y] = toupper(mark);
    return true;
}

template <typename T>
void wordTTT_Board<T>::display_board() {
    cout << BLUE << "\n-=-=-=-=-=-=-" << RESET;
    for (int i = 0; i < this->rows; i++) {
        cout << BLUE << "\n| " << RESET;
        for (int j = 0; j < this->columns; j++) {
            cout << this->board[i][j] << BLUE << " | " << RESET;
        }
        cout << BLUE << "\n-=-=-=-=-=-=-" << RESET;
    }
    cout << endl;
}

template <typename T>
bool wordTTT_Board<T>::is_win() {
    unordered_set<string> dictionary = loud_file_in_set();
    string res = "";
    for (int i = 0; i < this->rows; i++) {
        res = string(1, this->board[i][0]) + string(1, this->board[i][1]) + string(1, this->board[i][2]);
        if (dictionary.find(res) != dictionary.end()) {
            cout << CYAN << "Word(" << RED << res << CYAN << ") FOUND! (row)" << RESET << endl;
            return true;
        }
    }
    return false;
}

template <typename T>
bool wordTTT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool wordTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Player Class
template <typename T>
wordTTT_Player<T>::wordTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void wordTTT_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << CYAN << this->getname() << "'s turn. Enter row, column, and character: " << RESET;
        cin >> x >> y >> this->symbol;
        if (x < 1 || x > 3 || y < 1 || y > 3) {
            cerr << RED << "Invalid input!" << RESET << endl;
            continue;
        }
        --x;
        --y;
        break;
    }
}

// Random Player Class
template <typename T>
wordTTT_Random_Player<T>::wordTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
    this->name = "Random Computer";
}

template <typename T>
void wordTTT_Random_Player<T>::getmove(int& x, int& y) {
    is_computer = true;
    x = rand() % 3;
    y = rand() % 3;
    this->symbol = 'A' + rand() % 26;
}
void playWordTTTGame();
#endif //_wordTTT_H
