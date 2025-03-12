SRC_DIR = src
DIST_DIR = dist

SRC_C_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

OUT_C_FILES := $(SRC_C_FILES:$(SRC_DIR)/%.c=$(DIST_DIR)/%.x)
OUT_CPP_FILES := $(SRC_CPP_FILES:$(SRC_DIR)/%.cpp=$(DIST_DIR)/%.xp)

CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -std=c99
CXXFLAGS = -Wall -Wextra -std=c++17

all: $(OUT_C_FILES) $(OUT_CPP_FILES)

$(DIST_DIR)/%.x: $(SRC_DIR)/%.c
	@mkdir -p $(DIST_DIR)  # Ensure dist directory exists
	$(CC) $(CFLAGS) -o $@ $<

$(DIST_DIR)/%.x: $(SRC_DIR)/%.cpp
	@mkdir -p $(DIST_DIR)  # Ensure dist directory exists
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(DIST_DIR)

.PHONY: all clean