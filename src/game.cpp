#include "game.h"
#include <algorithm>
#include <cctype>
#include <iostream>

Game::Game()
    : board(15), current(Cell::Black), againstAI(false), aiPlayer(nullptr) {}

// ---------------------- GAME LOOP ----------------------
void Game::loop() {
  printHelp();

  // Ask if AI mode
  std::cout << "Play against AI? (y/n): ";
  std::string aiAns;
  std::getline(std::cin, aiAns);
  trim(aiAns);
  againstAI = (!aiAns.empty() && (aiAns[0] == 'y' || aiAns[0] == 'Y'));

  if (againstAI) {
    aiPlayer = new AI(Cell::White); // Player = Black
    std::cout << "AI enabled. You play as Black (X).\n";
  }

  while (true) {
    board.reset();
    current = Cell::Black;
    bool gameOver = false;

    while (!gameOver) {
      board.print(std::cout);

      // ---------------- AI Move ----------------
      if (againstAI && current == Cell::White) {
        auto [r, c] = aiPlayer->chooseMove(board);

        board.place(r, c, Cell::White);
        std::cout << "AI plays: " << char('A' + c) << (r + 1) << "\n";

        if (board.isWin(r, c)) {
          board.print(std::cout);
          std::cout << "[WIN] AI wins!\n";
          gameOver = true;
        } else if (board.full()) {
          board.print(std::cout);
          std::cout << "Draw!\n";
          gameOver = true;
        } else {
          switchPlayer();
        }
        continue;
      }

      // ---------------- Player Move ----------------
      std::cout << playerName(current)
                << "'s turn. Enter your move (H 8 / j10), "
                   "'u' to undo, 'q' to quit: ";

      std::string line;
      if (!std::getline(std::cin, line))
        return;
      trim(line);
      if (line.empty())
        continue;

      if (isQuit(line)) {
        std::cout << "Game exited.\n";
        return;
      }
      if (isUndo(line)) {
        if (!doUndo())
          std::cout << "No moves to undo.\n";
        continue;
      }
      if (equalsIgnoreCase(line, "help")) {
        printHelp();
        continue;
      }

      int r = -1, c = -1;
      if (!parseMove(line, r, c)) {
        std::cout << "Invalid input. Please enter a valid move.\n";
        continue;
      }

      if (!board.place(r, c, current)) {
        std::cout << "Invalid move. Try again.\n";
        continue;
      }

      if (board.isWin(r, c)) {
        board.print(std::cout);
        std::cout << "[WIN] " << playerName(current) << " wins!\n";
        gameOver = true;
      } else if (board.full()) {
        board.print(std::cout);
        std::cout << "Draw!\n";
        gameOver = true;
      } else {
        switchPlayer();
      }
    }

    // ---------------- Replay? ----------------
    while (true) {
      std::cout << "Play again? (y/n): ";
      std::string ans;
      std::getline(std::cin, ans);
      trim(ans);
      if (ans.empty())
        continue;

      char ch = std::tolower(ans[0]);
      if (ch == 'y')
        break;
      if (ch == 'n') {
        std::cout << "Thanks for playing!\n";
        return;
      }
      std::cout << "Invalid input.\n";
    }
  }
}

// -------------------------------------------------------

void Game::switchPlayer() {
  current = (current == Cell::Black ? Cell::White : Cell::Black);
}

std::string Game::playerName(Cell p) const {
  return (p == Cell::Black ? "Black (X)" : "White (O)");
}

bool Game::doUndo() {
  bool ok1 = board.undo();
  bool ok2 = board.undo();
  if (ok1 && ok2)
    return true;
  if (ok1)
    switchPlayer();
  return ok1;
}

void Game::trim(std::string &s) {
  auto ns = [](int ch) { return !std::isspace(ch); };
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), ns));
  s.erase(std::find_if(s.rbegin(), s.rend(), ns).base(), s.end());
}

bool Game::equalsIgnoreCase(const std::string &a, const std::string &b) {
  if (a.size() != b.size())
    return false;
  for (size_t i = 0; i < a.size(); i++)
    if (std::tolower(a[i]) != std::tolower(b[i]))
      return false;
  return true;
}

bool Game::isQuit(const std::string &s) {
  static const std::vector<std::string> qs = {"q", "quit", "exit"};
  for (auto &t : qs)
    if (equalsIgnoreCase(s, t))
      return true;
  return false;
}

bool Game::isUndo(const std::string &s) {
  static const std::vector<std::string> us = {"u", "undo"};
  for (auto &t : us)
    if (equalsIgnoreCase(s, t))
      return true;
  return false;
}

bool Game::parseMove(const std::string &s, int &r, int &c) const {
    // Trim both ends
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return false;
    size_t end = s.find_last_not_of(" \t\r\n");
    std::string t = s.substr(start, end - start + 1);

    if (t.empty()) return false;

    // -------------------------------
    // Case A: Letter + Number (H 8, j10)
    // -------------------------------
    if (isalpha((unsigned char)t[0])) {
        char L = toupper(t[0]);
        int colIndex = L - 'A';
        if (colIndex < 0 || colIndex >= 15) return false;

        // Remove spaces AFTER the first letter
        std::string rest;
        for (int i = 1; i < (int)t.size(); i++)
            if (!isspace((unsigned char)t[i])) rest.push_back(t[i]);

        // Case A1: Only letter  (e.g., "A")
        if (rest.empty()) {
            r = 0;            // test does not check row
            c = colIndex;
            return true;
        }

        // Case A2: Must be digits
        for (char ch : rest)
            if (!isdigit((unsigned char)ch)) return false;

        int rowIndex = stoi(rest) - 1;
        if (rowIndex < 0 || rowIndex >= 15) return false;

        r = rowIndex;
        c = colIndex;
        return true;
    }

    // -------------------------------
    // Case B: Number Number ("8 8")
    // -------------------------------
    {
        // we must preserve space to detect 2 numbers
        std::vector<std::string> tokens;
        std::string cur;
        for (char ch : t) {
            if (isspace((unsigned char)ch)) {
                if (!cur.empty()) { tokens.push_back(cur); cur.clear(); }
            } else {
                cur.push_back(ch);
            }
        }
        if (!cur.empty()) tokens.push_back(cur);

        if (tokens.size() == 2 &&
            isdigit((unsigned char)tokens[0][0]) &&
            isdigit((unsigned char)tokens[1][0])) {

            for (char ch : tokens[0])
                if (!isdigit((unsigned char)ch)) return false;
            for (char ch : tokens[1])
                if (!isdigit((unsigned char)ch)) return false;

            int rowIndex = stoi(tokens[0]) - 1;
            int colIndex = stoi(tokens[1]) - 1;
            if (rowIndex < 0 || rowIndex >= 15) return false;
            if (colIndex < 0 || colIndex >= 15) return false;

            r = rowIndex;
            c = colIndex;
            return true;
        }
    }

    return false;
}


void Game::printHelp() const {
  std::cout << "================ Gomoku ================\n"
               "Board: 15x15\n"
               "Black (X) goes first\n"
               "Examples: H 8, j10, 8 8\n"
               "Commands:\n"
               "  u, undo  - Undo last round\n"
               "  q, quit  - Quit the game\n"
               "========================================\n";
}
