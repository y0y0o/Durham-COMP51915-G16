CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

SRC = src/board.cpp src/game.cpp
MAIN = src/main.cpp
TESTS = tests/test_board.cpp tests/test_game.cpp

TARGET = gomoku

all: $(TARGET)

$(TARGET): $(SRC) $(MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(SRC) $(TESTS)
	$(CXX) $(CXXFLAGS) -o test_board $(SRC) tests/test_board.cpp
	./test_board
	$(CXX) $(CXXFLAGS) -o test_game $(SRC) tests/test_game.cpp
	./test_game

clean:
	rm -f $(TARGET) test_board test_game

