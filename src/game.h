#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "ai.h"
#include <string>

class Game {
public:
    Game();
    void loop();

private:
    Board board;
    Cell current;

    bool againstAI;   // Whether to play against AI
    AI* aiPlayer;     // Pointer to AI object

    void switchPlayer();
    std::string playerName(Cell p) const;
    bool doUndo();

    static void trim(std::string& s);
    static bool equalsIgnoreCase(const std::string& a, const std::string& b);
    static bool isQuit(const std::string& s);
    static bool isUndo(const std::string& s);

    bool parseMove(const std::string& s, int& r, int& c) const;
    void printHelp() const;
};

#endif
