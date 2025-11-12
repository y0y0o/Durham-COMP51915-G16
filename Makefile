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

# format code for local
lint:
	clang-format -i src/*.cpp src/*.h tests/*.cpp


# format check for CI
lint-check:
	clang-format --dry-run -Werror src/*.cpp src/*.h tests/*.cpp

clean:
	rm -f $(TARGET) test_board test_game

