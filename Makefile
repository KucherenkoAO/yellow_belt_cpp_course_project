CC = g++
CFLAGS = --std=c++17 -Iheaders -Wall
OBJ_DIR = obj
SRC_DIR = src

ALL_SRC = $(shell ls $(SRC_DIR))
ALL_OBJ = $(ALL_SRC:%.cpp=$(OBJ_DIR)/%.o)

PROG_NAME = database

$(PROG_NAME): $(ALL_OBJ)
	$(CC) $(ALL_OBJ) -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CC) $(CFLAGS) -g -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(PROG_NAME)
