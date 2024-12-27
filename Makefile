CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Add debug flags if making debug
ifeq ($(MAKECMDGOALS),debug)
    CFLAGS += -g -O0
endif

SRC = src/board.c src/attacks.c src/random.c src/moveGeneration.c test/testBoard.c test/testAttacks.c test/testMoveGeneration.c test/utils.c main.c
BUILD_DIR = build
TARGET = $(BUILD_DIR)/chess_game
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

all: $(TARGET)
debug: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Generic rule to compile source files into object files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all debug clean
