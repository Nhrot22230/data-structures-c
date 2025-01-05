# Variables
LIBS     :=
INCLUDE  := .
CFLAGS   := -Wall -Wextra
CC       := gcc
SRC_DIR  := src
BUILD_DIR := build
TEST_DIR := test

# Targets
.PHONY: all test run test_run clean

all: $(BUILD_DIR)/main

$(BUILD_DIR)/main: $(SRC_DIR)/*.c | $(BUILD_DIR)
	$(CC) $(LIBS) $(CFLAGS) -I$(INCLUDE) $^ -o $@

$(BUILD_DIR)/test: $(TEST_DIR)/*.c | $(BUILD_DIR)
	$(CC) $(LIBS) $(CFLAGS) -I$(INCLUDE) $^ -o $@

test: $(BUILD_DIR)/test

run: $(BUILD_DIR)/main
	./$<

test_run: $(BUILD_DIR)/test
	./$<

clean:
	rm -rf $(BUILD_DIR)

# Directory creation
$(BUILD_DIR):
	mkdir -p $@
