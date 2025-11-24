APP_NAME = burrito
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
INCLUDE_DIR = src/includes

CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -MMD -MP -I$(INCLUDE_DIR)
LDFLAGS = -lglfw -lGLEW -lGL -lm

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
DEPS = $(OBJECTS:.o=.d)

all: directories $(BIN_DIR)/$(APP_NAME)

$(BIN_DIR)/$(APP_NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

run: all
	./$(BIN_DIR)/$(APP_NAME)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

-include $(DEPS)

.PHONY: all clean run directories
