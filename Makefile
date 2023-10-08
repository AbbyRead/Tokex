# Define directory names
src_dir := src
obj_dir := obj
bin_dir := bin

# Leaving CC as default for ease of use

# Define compiler flags
CFLAGS := -Wall -Wextra -I$(scr_dir)

# List of source files (all .c files in src/)
src_files := $(wildcard $(src_dir)/*.c)

# Generate object file names from source file names
obj_files := $(patsubst $(src_dir)/%.c,$(obj_dir)/%.o,$(src_files))

# List binary targets (one for each object file)
bin_targets := $(patsubst $(obj_dir)/%.o,$(bin_dir)/%,$(obj_files))

# Determine the newest binary
newest_binary := $(lastword $(shell find $(bin_dir) -type f -name '*'))

.PHONY all, clean, run

# Default target
all : $(bin_targets)

# Rule to compile .c files into .o files
$(obj_dir)/%.o: $(src_dir)/%.c | $(obj_dir)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link .o files into binaries
$(bin_dir)/%: $(obj_dir)/%.o | $(bin_dir)
	$(CC) $< -o $@

$(obj_dir):
	mkdir -p $(obj_dir)

$(bin_dir):
	mkdir -p $(bin_dir)

clean:
	rm -rf $(obj_dir) $(bin_dir)

run: all
	./$(newest_binary)

# Phony target to ensure 'all' is always run when requested
.PHONY: all

# Set the newest binary as the default target
.DEFAULT_GOAL := $(newest_binary)