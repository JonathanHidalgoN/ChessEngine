CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
#TODO: check how to remove test from here so when making test are not compile
SRC =src/board.c src/attacks.c src/random.c test/testBoard.c test/testAttacks.c main.c
BUILD_DIR = build
TARGET = $(BUILD_DIR)/chess_game

OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Generic rule to compile source files into object files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
