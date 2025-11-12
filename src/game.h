#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <string>

// The Game class handles player input, turns, and game flow.
class Game {
public:
    Game();
    void loop();   // Main game loop
    static bool equalsIgnoreCase(const std::string& a, const std::string& b);
    static bool isQuit(const std::string& s);           // Check quit command
    static bool isUndo(const std::string& s);           // Check undo command
    bool parseMove(const std::string& s, int& r, int& c) const;  // Parse user move input

private:
    Board board;
    Cell current;

    // Helper methods
    void switchPlayer();                                // Change turn
    std::string playerName(Cell p) const;               // Get name for current player
    bool doUndo();                                      // Undo one round (two moves)
    static void trim(std::string& s);                   // Trim whitespace
    void printHelp() const;                             // Show help text
};

#endif
