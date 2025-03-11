SRC_DIR = src
DIST_DIR = dist

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OUT_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(DIST_DIR)/%.x)

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: $(OUT_FILES)

$(DIST_DIR)/%.x: $(SRC_DIR)/%.c
	@mkdir -p $(DIST_DIR)  # Ensure dist directory exists
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(DIST_DIR)

.PHONY: all clean
