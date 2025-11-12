#include "game.h"
#include <iostream>
#include <cctype>
#include <algorithm>

Game::Game(): board(15), current(Cell::Black) {}

void Game::loop() {
    printHelp();

    while (true) {
        board.reset();            // Start a new game each loop
        current = Cell::Black;    // Black always starts first
        bool gameOver = false;

        while (!gameOver) {
            board.print(std::cout);
            std::cout << playerName(current)
                      << "'s turn. Enter your move (e.g., H 8 / j10), "
                         "or 'u' to undo, 'q' to quit: ";

            std::string line;
            if (!std::getline(std::cin, line)) return;  // Exit program
            trim(line);
            if (line.empty()) continue;

            // --- Command handling ---
            if (isQuit(line)) {
                std::cout << "Game exited.\n";
                return;
            }
            if (isUndo(line)) {
                if (!doUndo()) std::cout << "No moves to undo.\n";
                continue;
            }
            if (equalsIgnoreCase(line, "help")) {
                printHelp();
                continue;
            }

            // --- Check move input format ---
            int r = -1, c = -1;
            if (!parseMove(line, r, c)) {
                std::cout << "Invalid input. Please enter a valid format.\n";
                continue;  // Ask again
            }

            // --- Place piece ---
            if (!board.place(r, c, current)) {
                std::cout << "Invalid input. Please enter a valid format.\n";
                continue;  // Already occupied or out of range
            }

            // --- Check victory or draw ---
            if (board.isWin(r, c)) {
                board.print(std::cout);
                std::cout << "[WIN] " << playerName(current) << " wins! Five in a row!\n";
                gameOver = true;
            }
            else if (board.full()) {
                board.print(std::cout);
                std::cout << "The board is full. It's a draw!\n";
                gameOver = true;
            }
            else {
                switchPlayer(); // Next turn
            }
        }

        // --- Ask if player wants a new game ---
        while (true) {
            std::cout << "\nDo you want to play again? (y/n): ";
            std::string ans;
            std::getline(std::cin, ans);
            trim(ans);
            if (ans.empty()) continue;

            char c = std::tolower(ans[0]);
            if (c == 'y') {
                std::cout << "\nStarting a new game! Black (X) goes first.\n";
                break;  // Restart outer while loop
            }
            else if (c == 'n') {
                std::cout << "Game over. Thanks for playing!\n";
                return; // Exit the whole program
            }
            else {
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
            }
        }
    }
}

// Switch current player
void Game::switchPlayer() {
    current = (current == Cell::Black) ? Cell::White : Cell::Black;
}

// Get player's name
std::string Game::playerName(Cell p) const {
    return (p == Cell::Black) ? "Black (X)" : "White (O)";
}

// Undo (two moves to keep turns balanced)
bool Game::doUndo() {
    bool ok1 = board.undo();
    bool ok2 = board.undo();
    if (ok1 && ok2) return true;
    if (ok1) switchPlayer();
    return ok1;
}

// Trim whitespace from both ends
void Game::trim(std::string& s) {
    auto notspace = [](int ch){ return !std::isspace(ch); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notspace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notspace).base(), s.end());
}

// Case-insensitive string comparison
bool Game::equalsIgnoreCase(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (std::tolower(a[i]) != std::tolower(b[i])) return false;
    return true;
}

// Check for quit command
bool Game::isQuit(const std::string& s) {
    static const std::vector<std::string> qs = {"q", "quit", "exit", "resign"};
    for (auto& t : qs) if (equalsIgnoreCase(s, t)) return true;
    return false;
}

// Check for undo command
bool Game::isUndo(const std::string& s) {
    static const std::vector<std::string> us = {"u", "undo", "back"};
    for (auto& t : us) if (equalsIgnoreCase(s, t)) return true;
    return false;
}

// Parse move input (supports formats like "H8", "h 8", "10 12")
bool Game::parseMove(const std::string& s, int& r, int& c) const {
    std::string A, B;
    for (char ch : s) {
        if (isalpha((unsigned char)ch)) A.push_back(ch);
        else if (isdigit((unsigned char)ch)) B.push_back(ch);
        else if (isspace((unsigned char)ch)) continue;
        else return false;
    }
    if (A.empty() && B.empty()) return false;

    auto toRC = [&](int row1, int col1)->bool {
        r = row1; c = col1;
        return (r >= 0 && r < board.size() && c >= 0 && c < board.size());
    };

    if (!A.empty() && !B.empty()) {
        c = toupper(A[0]) - 'A';
        int row = stoi(B);
        r = row - 1;
        return toRC(r, c);
    } 
    else if (A.empty() && !B.empty()) {
        if (B.size() >= 2) {
            int len = (int)B.size() / 2;
            int r1 = stoi(B.substr(0, len));
            int c1 = stoi(B.substr(len));
            r = r1 - 1; c = c1 - 1;
            return toRC(r, c);
        }
        return false;
    } 
    else if (!A.empty() && B.empty()) {
        c = toupper(A[0]) - 'A';
        r = board.size() / 2;
        return toRC(r, c);
    }
    return false;
}

// Print help information
void Game::printHelp() const {
    std::cout <<
    "================ Gomoku ================\n"
    "Board size: 15x15, Black (X) goes first.\n"
    "Examples of input: H 8, j10, or 8 8\n"
    "\nCommands:\n"
    "  u / undo    - Undo the last two moves (one round)\n"
    "  q / quit    - Quit the game\n"
    "  help        - Show this help message\n"
    "\nWinning rule: Get five in a row in any direction.\n"
    "If the board is full, it's a draw.\n"
    "========================================\n";
}
