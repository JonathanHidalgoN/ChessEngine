CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/chess_piece.c main.c
BUILD_DIR = build
OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
TARGET = $(BUILD_DIR)/chess_game

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
