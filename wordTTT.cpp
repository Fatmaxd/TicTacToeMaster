#include <iostream>
#include "BoardGames_Classes.h"
#include "wordTTT.h"

using namespace std;

// Define global variables
bool is_file_open = true;
bool is_computer = false;

// Define the loud_file_in_set function
unordered_set<string> loud_file_in_set() {
    ifstream file("dic.txt");
    unordered_set<string> words;
    if (!file.is_open()) {
        cerr << RED << "Error: Unable to open the file. Please try again.\n\n" << RESET;
        is_file_open = false;
        return words;
    }
    string word;
    while (file >> word) {
        words.insert(word);
    }
    file.close();
    return words;
}

void playWordTTTGame() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "                ------------------------------------\n"
        << YELLOW << "                -=Welcome to Word Tic-Tac-Toe Game=-\n" << RESET
        << "                ------------------------------------\n";

    Player<char>* players[2];
    wordTTT_Board<char>* B = new wordTTT_Board<char>();

    string player1Name, player2Name;
    char charactour;

    int choice;

    // Choose Player 1 type
    cout << CYAN << "1) Human         2) Random Computer\n"
        << "Choose Player one type: " << RESET;
    cin >> choice;
    if (choice == 1) {
        cout << CYAN << "Enter Player 1 name: " << RESET;
        cin >> player1Name;
        cout << CYAN << "Enter Player 1 symbol: " << RESET;
        cin >> charactour;
        players[0] = new wordTTT_Player<char>(player1Name, charactour);
    }
    else if (choice == 2) {
        cout << CYAN << "Enter Player 1 symbol: " << RESET;
        cin >> charactour;
        players[0] = new wordTTT_Random_Player<char>(charactour);
    }
    else {
        cerr << RED << "Invalid choice for Player 1.\n" << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "-------------------------------------------------\n\n" << RESET;
        return;
    }

    // Choose Player 2 type
    cout << CYAN << "1) Human         2) Random Computer\n"
        << "Choose Player two type: " << RESET;
    cin >> choice;
    if (choice == 1) {
        cout << CYAN << "Enter Player 2 name: " << RESET;
        cin >> player2Name;
        cout << CYAN << "Enter Player 2 symbol: " << RESET;
        cin >> charactour;
        players[1] = new wordTTT_Player<char>(player2Name, charactour);
    }
    else if (choice == 2) {
        cout << CYAN << "Enter Player 2 symbol: " << RESET;
        cin >> charactour;
        players[1] = new wordTTT_Random_Player<char>(charactour);
    }
    else {
        cerr << RED << "Invalid choice for Player 2.\n" << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "-------------------------------------------------\n\n" << RESET;
        return;
    }

    // Start the game
    GameManager<char> wordTTT_game(B, players);
    wordTTT_game.run();

    // Clean up
    delete B;
    delete players[0];
    delete players[1];
}
